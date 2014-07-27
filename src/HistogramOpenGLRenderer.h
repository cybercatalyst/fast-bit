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

#ifndef HISTOGRAM_OPENGL_RENDERER_H
#define HISTOGRAM_OPENGL_RENDERER_H

#include <QVector>
#include "OpenGLRenderer.h"

/**
  * \class HistogramOpenGLRenderer
  * \brief Class for rendering histograms on OpenGL surfaces.
  *
  * This class renders a histogram based on a QVector of values. It automatically fits
  * the width, but assumes that the values height is always between -1 and 1.
  *
  */
class HistogramOpenGLRenderer : public OpenGLRenderer
{
public:
    HistogramOpenGLRenderer(QWidget *parent = 0);
    ~HistogramOpenGLRenderer();

    /**
      * Tells the renderer to render the value set.
      */
    void renderHistogram(QVector<float> values);

    /**
      * Returns a copy of the current value set.
      */
    QVector<float> values();

    /**
      * Sets the primary color.
      */
    void setPrimaryColor(float red, float green, float blue);

    /**
      * Sets the secondary color.
      */
    void setSecondaryColor(float red, float green, float blue);

    /**
      * Marks the renderer as updating.
      */
    void markAsUpdating();

protected:
    /**
      * Reimplemented from QGLWidget. Repaints the OpenGL window.
      */
    void paintGL();

private:
    /**
      * Primary color.
      */
    float primaryColor[3];

    /**
      * Secondary color.
      */
    float secondaryColor[3];

    /**
      * The current image;
      */
    QVector<float> currentValues;

    bool updating;
};

#endif // HISTOGRAM_OPENGL_RENDERER_H
