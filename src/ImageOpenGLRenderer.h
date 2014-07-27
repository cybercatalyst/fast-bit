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

#ifndef IMAGE_OPENGL_RENDERER_H
#define IMAGE_OPENGL_RENDERER_H

#include <QImage>
#include <QStack>
#include <QTimer>
#include "headerFiles/renderers/OpenGLRenderer.h"

#include <math.h>

/**
  * \class ImageOpenGLRenderer
  * \brief Class for rendering QImages on OpenGL surfaces.
  *
  * This class renders the given QImage onto an textured OpenGL Quad. It keeps care
  * to fit margins to keep the aspect ratio of the image as needed. By default it
  * leaves a small margin around the picture for asthetic reasons.
  *
  */
class ImageOpenGLRenderer : public OpenGLRenderer
{
    Q_OBJECT

public:
    ImageOpenGLRenderer(QWidget *parent = 0);
    ~ImageOpenGLRenderer();

    /**
      * Provides the history in chronologic order.
      */
    QStack<QImage> history();

    /**
      * Pops the last image from history.
      */
    void popFromHistory();

    /**
      * Pushes image to history.
      */
    void pushToHistory(QImage image);

    /**
      * Tells the renderer to render the image.
      */
    void renderImage(QImage image);

    /**
      * Returns a reference of the current image.
      */
    QImage image();

    /**
      * Sets the title.
      */
    void setTitle(QString title);

    /**
      * Returns the title.
      */
    QString title();

protected slots:
    /**
      * Updates animations.
      */
    void updateAnimations();

signals:
    void historyEmpty();

protected:
    /**
      * Reimplemented from QGLWidget. Repaints the OpenGL window.
      */
    void paintGL();

    /**
      * Reimplemented from QGLWidget. Resizes the OpenGL window.
      */
    void resizeGL(int w, int h);

private:
    const static double updateAnimationsInterval = 0.02;
    struct Texture
    {
        QImage image;
        GLuint id;
    };

    struct Animation
    {
        enum Type
        {
            ShiftIn,
            ShiftOut,
            BlendIn
        };

        enum ProgressType
        {
            Linear,
            Parabolic,
            LinearThenParabolic
        };

        double progress;
        double durationSeconds;
        Type type;
        ProgressType progressType;
    };

    /**
      * Animation timer;
      */
    QTimer animationTimer;

    /**
      * The current image;
      */
    QImage currentImage;

    /**
      * The title.
      */
    QString imageTitle;

    /**
      * The corresponding OpenGL texture.
      */
    GLuint texture;

    /**
      * The image ratio.
      */
    float imageRatio;

    /**
      * The viewport ratio.
      */
    float viewportRatio;

    /**
      * History stack.
      */
    QStack<Texture> _history;

    /**
      * Animations list.
      */
    QStack<Animation> animations;
};

#endif // IMAGE_OPENGL_RENDERER_H
