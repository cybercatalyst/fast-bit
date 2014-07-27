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

#include "OpenGLRenderer.h"

OpenGLRenderer::OpenGLRenderer(QWidget *parent)
    : QGLWidget(parent)
{
    setAutoBufferSwap(true);
    scroll[0]=0;
    scroll[1]=0;
    zoom=0.9;
}

OpenGLRenderer::~OpenGLRenderer()
{
}

void OpenGLRenderer::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    //glEnable(GL_POINT_SMOOTH);
    //glEnable(GL_LINE_SMOOTH);
}

void OpenGLRenderer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRenderer::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, 5.0, 15.0);
    glMatrixMode(GL_MODELVIEW);
}

void OpenGLRenderer::mousePressEvent(QMouseEvent *event)
{
    switch(event->button())
    {
        case Qt::LeftButton:
            dragMode=Scroll;
            break;

        case Qt::RightButton:
            dragMode=Zoom;
            break;
    }

    lastMousePosition=event->pos();
}

void OpenGLRenderer::mouseMoveEvent(QMouseEvent *event)
{
    if(event->type()==QMouseEvent::MouseMove)
    {
        switch(dragMode)
        {
            case Zoom:
                zoom+=(float)(lastMousePosition.x()-event->pos().x())*0.01;
                zoom+=(float)(lastMousePosition.y()-event->pos().y())*0.01;

                if(zoom<0.01)
                    zoom=0.01;
                break;

            case Scroll:
                scroll[0]+=(float)(lastMousePosition.x()-event->pos().x())*0.005;
                scroll[1]+=(float)(lastMousePosition.y()-event->pos().y())*0.005;
                break;
        }

        lastMousePosition=event->pos();
        event->accept();
        update();
    }
}

float OpenGLRenderer::currentZoom()
{
    return zoom;
}

QVector<float> OpenGLRenderer::currentScrollPosition()
{
    QVector<float> position(2);
    position[0] = scroll[0];
    position[1] = scroll[1];
    return position;
}

void OpenGLRenderer::setCurrentZoom(float value)
{
    zoom = value;
}

void OpenGLRenderer::setCurrentScrollPosition(QVector<float> value)
{
    if(value.size()!=2)
        return;
    scroll[0] = value[0];
    scroll[1] = value[1];
}
