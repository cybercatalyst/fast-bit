/* fast-bit image processing tool
 * Copyright (C) 2010 - 2011 Jacob Dawid
 * jacob.dawid@googlemail.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#include <QDockWidget>
#include <QGLWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QVector>

/**
  * \class OpenGLRenderer
  * \brief Base class for rendering 2d images on OpenGL surfaces.
  *
  * This class serves as a base class for other OpenGL renderer classes. It implements
  * basic functions like painting or resizing the window. Other classes may reimplement
  * these to provide different functionality. By default, this renderer displays a plain
  * black surface.
  */
class OpenGLRenderer : public QGLWidget
{
public:
    OpenGLRenderer(QWidget *parent = 0);
    virtual ~OpenGLRenderer();

    enum DragMode
    {
        Zoom,
        Scroll
    };

    /**
      * Returns the current zoom level.
      */
    float currentZoom();

    /**
      * Returns the current scroll position.
      */
    QVector<float> currentScrollPosition();

    /**
      * Sets the current zoom level.
      */
    void setCurrentZoom(float value);

    /**
      * Sets the current scroll position.
      */
    void setCurrentScrollPosition(QVector<float> value);

protected:
    /**
      * Reimplemented from QGLWidget. Initializes the OpenGL window.
      */
    virtual void initializeGL();

    /**
      * Reimplemented from QGLWidget. Repaints the OpenGL window.
      */
    virtual void paintGL();

    /**
      * Reimplemented from QGLWidget. Resizes the OpenGL window.
      */
    virtual void resizeGL(int w, int h);

    /**
      * Registers mouse button presses.
      */
    void mousePressEvent(QMouseEvent *event);

    /**
      * Registers mouse move events.
      */
    void mouseMoveEvent(QMouseEvent *event);

    /**
      * Zoom factor.
      */
    float zoom;

    /**
      * Scroll position.
      */
    float scroll[2];

    /**
      * Current drag mode;
      */
    DragMode dragMode;

    /**
      * Mouse position since the last mouse move event.
      */
    QPoint lastMousePosition;
};

#endif // OPENGL_RENDERER_H
