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

#include "Main.h"
#include "HistogramOpenGLRenderer.h"
#include <math.h>

HistogramOpenGLRenderer::HistogramOpenGLRenderer(QWidget *parent)
    : OpenGLRenderer(parent)
{
    setAutoBufferSwap(true);
    zoom=0.9;

    setMinimumWidth(400);

    this->setPrimaryColor(1.0, 0.0, 0.0);
    this->setSecondaryColor(0.0, 0.0, 1.0);
    updating = false;
}

HistogramOpenGLRenderer::~HistogramOpenGLRenderer()
{
}

void HistogramOpenGLRenderer::renderHistogram(QVector<float> values)
{
    currentValues=values;
    updating = false;
}

QVector<float> HistogramOpenGLRenderer::values()
{
    return currentValues;
}

void HistogramOpenGLRenderer::setPrimaryColor(float red, float green, float blue)
{
    primaryColor[0] = red;
    primaryColor[1] = green;
    primaryColor[2] = blue;
}

void HistogramOpenGLRenderer::setSecondaryColor(float red, float green, float blue)
{
    secondaryColor[0] = red;
    secondaryColor[1] = green;
    secondaryColor[2] = blue;
}

void HistogramOpenGLRenderer::markAsUpdating()
{
    updating = true;
    update();
}

void HistogramOpenGLRenderer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -6.0f);
    glBegin(GL_LINES);

        // Draw finest grid
        float step=0.2/10.0;
        for(int i=-50;i<=50;i++)
        {
            glColor4f(0.2, 0.2, 0.2, -0.8 + 0.2*zoom);
            glVertex2f((step*(float)i-scroll[0])*zoom, (-1.0+scroll[1])*zoom);
            glVertex2f((step*(float)i-scroll[0])*zoom, (1.0+scroll[1])*zoom);

            glVertex2f((-1.0-scroll[0])*zoom, (step*(float)i+scroll[1])*zoom);
            glVertex2f((1.0-scroll[0])*zoom, (step*(float)i+scroll[1])*zoom);

            glColor4f(0.6, 0.6, 0.6, -0.8 + 0.2*zoom);
            glVertex2f((step*(float)i-scroll[0])*zoom, (-0.01+scroll[1])*zoom);
            glVertex2f((step*(float)i-scroll[0])*zoom, (0.01+scroll[1])*zoom);

            glVertex2f((-0.01-scroll[0])*zoom, (step*(float)i+scroll[1])*zoom);
            glVertex2f((0.01-scroll[0])*zoom, (step*(float)i+scroll[1])*zoom);
        }

        // Draw medium grid
        step=2.0/10.0;
        for(int i=-5;i<=5;i++)
        {
            glColor4f(0.4, 0.4, 0.4, 0.2*zoom*zoom);
            glVertex2f((step*(float)i-scroll[0])*zoom, (-1.0+scroll[1])*zoom);
            glVertex2f((step*(float)i-scroll[0])*zoom, (1.0+scroll[1])*zoom);

            glVertex2f((-1.0-scroll[0])*zoom, (step*(float)i+scroll[1])*zoom);
            glVertex2f((1.0-scroll[0])*zoom, (step*(float)i+scroll[1])*zoom);

            glColor4f(0.8, 0.8, 0.8, 0.2*zoom*zoom);
            glVertex2f((step*(float)i-scroll[0])*zoom, (-0.01+scroll[1])*zoom);
            glVertex2f((step*(float)i-scroll[0])*zoom, (0.01+scroll[1])*zoom);

            glVertex2f((-0.01-scroll[0])*zoom, (step*(float)i+scroll[1])*zoom);
            glVertex2f((0.01-scroll[0])*zoom, (step*(float)i+scroll[1])*zoom);
        }

        // Draw axes
        glColor4f(0.5, 0.5, 0.5, 2.0-sqrt(zoom));
        glVertex2f(-scroll[0]*zoom, (-1.0+scroll[1])*zoom);
        glVertex2f(-scroll[0]*zoom, (1.0+scroll[1])*zoom);
        glVertex2f((-1.0-scroll[0])*zoom, scroll[1]*zoom);
        glVertex2f((1.0-scroll[0])*zoom, scroll[1]*zoom);
    glEnd();

    // If there's anything to draw..
    if(currentValues.size())
    {
        float step=(2.0/(float)currentValues.size());

        // Draw inner side.
        glBegin(GL_TRIANGLE_STRIP);
            for(int i=0;i<currentValues.size();i++)
            {
                glColor4f(currentValues[i]*primaryColor[0]+(1.0-currentValues[i])*secondaryColor[0],
                          currentValues[i]*primaryColor[1]+(1.0-currentValues[i])*secondaryColor[1],
                          currentValues[i]*primaryColor[2]+(1.0-currentValues[i])*secondaryColor[2],
                          0.2*sqrt(sqrt(zoom)));

                glVertex2f((step*(float)i-1.0-scroll[0])*zoom, (currentValues[i]+scroll[1])*zoom);

                glColor4f(secondaryColor[0], secondaryColor[1], secondaryColor[2], 0.4*sqrt(sqrt(zoom)));
                glVertex2f((step*(float)i-1.0-scroll[0])*zoom, scroll[1]*zoom);
            }
        glEnd();

        // Draw the graph to have it a sharp edge.
        glBegin(GL_LINE_STRIP);
            for(int i=0;i<currentValues.size();i++)
            {

                glColor3f(currentValues[i]*primaryColor[0]+(1.0-currentValues[i])*secondaryColor[0],
                          currentValues[i]*primaryColor[1]+(1.0-currentValues[i])*secondaryColor[1],
                          currentValues[i]*primaryColor[2]+(1.0-currentValues[i])*secondaryColor[2]);

                glVertex2f((step*(float)i-1.0-scroll[0])*zoom, (currentValues[i]+scroll[1])*zoom);
            }
        glEnd();
    }

    if(updating)
    {
        glColor3d(1.0, 1.0, 1.0);
        renderText(-0.9, -0.9, 0.0, Main::instance().translate("HistogramOpenGLRenderer", "Updating, please wait.."));
    }
}
