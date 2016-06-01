// Copyright (C) 2012-2016 The VPaint Developers.
// See the COPYRIGHT file at the top-level directory of this distribution
// and at https://github.com/dalboris/vpaint/blob/master/COPYRIGHT
//
// This file is part of VPaint, a vector graphics editor. It is subject to the
// license terms and conditions in the LICENSE.MIT file found in the top-level
// directory of this distribution and at http://opensource.org/licenses/MIT

#ifndef KEYEDGEGLRESOURCES_H
#define KEYEDGEGLRESOURCES_H

#include <glm/vec2.hpp>

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

/// \class EdgeGeometryGLVertex
/// \brief A struct that stores the per-vertex data to be consumed by the
/// vertex shader.
///
/// Here, the word "vertex" is used in the OpenGL sense, not in the VAC sense
/// (i.e., a "vertex" is the atomic element processed by the vertex shader).
///
/// Read documentation of EdgeGeometryGLSample before this documentation.
///
/// Each EdgeGeometryGpuVertex stores three vec2 member variables:
///   - centerline
///   - normal
///   - position
///
/// The first two (centerline and normal) are used to draw in "Topology mode",
/// i.e. to draw the edge as a fixed-width thick curve ignoring join style. The
/// fixed width is given as a uniform to the shader. The advantage of this
/// representation is that different views can share the same VBO data but
/// draw with different width. Also, no need to re-send any data to the GPU
/// to display the curve with a different width (for instance, when zooming
/// with fixed width in screen space).
///
/// The third one (position) is used to draw in "Normal mode", i.e. to draw the
/// edge as a variable-width thick curve, with join style applied. Computing
/// this on the GPU would be challenging, therefore it is done on the CPU.
///
struct EdgeGeometryGLVertex
{
    /// Position of the curve centerline.
    ///
    glm::vec2 centerline;

    /// Normal of the curve, pointing towards the final position.
    ///
    glm::vec2 normal;

    /// Final position, obtained by translating the centerline along the normal
    /// by the curve width, then applying a transformation to this position to
    /// satisfy join style. This transformation is not necessarily along the
    /// normal.
    ///
    glm::vec2 position;
};

/// \class EdgeGeometryGLSample
/// \brief A struct that stores a GPU-friendly representation of a curve sample
/// for rendering purposes.
///
/// Each curve sample is sent to the GPU as two vertices: one vertex
/// representing the "left side" of the thick curve, and the other vertex
/// representing the "right side". So if a curve has 10 samples, it is sent to
/// the GPU as 20 vertices, interpreted as a triangle strip.
///
/// Note that there is some redundancy in this data:
///   1. left.centerline ==   right.centerline
///   2. left.normal     == - right.normal
///
/// However, this is necessary because each vertex is processed separately and
/// in parallel in the GPU. It is a memory vs. speed tradeoff, where we favor
/// speed in this case.
///
struct EdgeGeometryGLSample
{
    EdgeGeometryGLVertex left;  ///< Vertex on the "left side" of the curve.
    EdgeGeometryGLVertex right; ///< Vertex on the "right side" of the curve.
};

/// \class KeyEdgeGLSharedResources
/// \brief A convenient struct that stores GL shared resources related to key edges
///
struct KeyEdgeGLSharedResources
{
    QOpenGLBuffer vbo;
    size_t numVertices;
};

/// \class KeyEdgeGLResources
/// \brief A convenient struct that stores GL resources related to key edges
///
struct KeyEdgeGLResources
{
    QOpenGLVertexArrayObject * vao; // Pointer because copy of QOpenGLVertexArrayObject is disabled
    size_t numVertices;

    KeyEdgeGLResources() : vao(nullptr), numVertices(0) {}
};

#endif // KEYEDGEGLRESOURCES_H