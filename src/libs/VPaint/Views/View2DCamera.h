// Copyright (C) 2012-2016 The VPaint Developers.
// See the COPYRIGHT file at the top-level directory of this distribution
// and at https://github.com/dalboris/vpaint/blob/master/COPYRIGHT
//
// This file is part of VPaint, a vector graphics editor. It is subject to the
// license terms and conditions in the LICENSE.MIT file found in the top-level
// directory of this distribution and at http://opensource.org/licenses/MIT

#ifndef VIEW2DCAMERA_H
#define VIEW2DCAMERA_H

#include "Core/DataObject.h"
#include "Views/View2DCameraData.h"

#include <QMatrix4x4>

/// \class View2DCamera
/// \brief A class to represent a 2D camera object.
///
class View2DCamera: public DataObject<View2DCameraData>
{
private:
    Q_OBJECT
    Q_DISABLE_COPY(View2DCamera)

public:
    /// Constructs a View2DCamera.
    ///
    View2DCamera();

    /// Converts 2D camera data to 4x4 matrix
    ///
    QMatrix4x4 toMatrix() const;
};

#endif // VIEW2DCAMERA_H
