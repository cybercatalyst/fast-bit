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

#include "ImageOpenGLRenderer.h"

ImageOpenGLRenderer::ImageOpenGLRenderer(QWidget *parent)
    : OpenGLRenderer(parent)
{
    setAutoBufferSwap(true);
    currentImage = QImage();
    zoom=0.9;

    animationTimer.setInterval(updateAnimationsInterval*1000);
    animationTimer.start();
    connect(&animationTimer, SIGNAL(timeout()), this, SLOT(updateAnimations()));
}

ImageOpenGLRenderer::~ImageOpenGLRenderer()
{
}

QStack<QImage> ImageOpenGLRenderer::history()
{
    QStack<QImage> imageHistory;
    foreach(Texture t, _history)
        imageHistory.push(t.image);
    return imageHistory;
}

void ImageOpenGLRenderer::popFromHistory()
{
    if(_history.size())
    {
        //deleteTexture(texture);

        Texture tex = _history.pop();
        currentImage = tex.image;
        texture = tex.id;
    }

    Animation shiftAnimation;
    shiftAnimation.type = Animation::ShiftOut;
    shiftAnimation.progressType = Animation::LinearThenParabolic;
    shiftAnimation.progress = 0;
    shiftAnimation.durationSeconds = 0.3;
    animations.push(shiftAnimation);

    if(!_history.size())
        emit historyEmpty();

    updateGL();
}

void ImageOpenGLRenderer::pushToHistory(QImage image)
{
    Texture texture;
    texture.image=image;
    texture.id=bindTexture(image);
    _history.push(texture);

    Animation shiftAnimation;
    shiftAnimation.type = Animation::ShiftIn;
    shiftAnimation.progressType = Animation::LinearThenParabolic;
    shiftAnimation.progress = 0;
    shiftAnimation.durationSeconds = 0.3;
    animations.push(shiftAnimation);
}

void ImageOpenGLRenderer::renderImage(QImage image)
{
    makeCurrent();
    if(!currentImage.isNull())
        pushToHistory(currentImage);
    currentImage=image;
    texture=bindTexture(currentImage);
    imageRatio=(float)image.width()/(float)image.height();
    updateGL();
}

QImage ImageOpenGLRenderer::image()
{
    return currentImage;
}

void ImageOpenGLRenderer::setTitle(QString title)
{
    imageTitle=title;
}

QString ImageOpenGLRenderer::title()
{
    return imageTitle;
}

void ImageOpenGLRenderer::updateAnimations()
{
    int iter;
    for(iter=0;iter<animations.size();)
    {
        switch(animations[iter].progressType)
        {
            case Animation::Linear:
                animations[iter].progress
                        +=updateAnimationsInterval/animations[iter].durationSeconds;
            break;

            case Animation::Parabolic:
                animations[iter].progress
                        +=updateAnimationsInterval/animations[iter].durationSeconds
                          *(1.0-animations[iter].progress);
            break;

            case Animation::LinearThenParabolic:
                if(animations[iter].progress < 0.66)
                {
                    animations[iter].progress
                            +=updateAnimationsInterval/animations[iter].durationSeconds;
                }
                else
                {
                    animations[iter].progress
                            +=updateAnimationsInterval/animations[iter].durationSeconds
                              *(1.0-animations[iter].progress);
                }
            break;
        }

        if(animations[iter].progress>=1.0)
        {
            animations.remove(iter);
        }
        else
            iter++;
    }
    updateGL();
}

void ImageOpenGLRenderer::paintGL()
{
    float imageScale;
    float marginWidth, marginHeight;
    // The viewport is wider than the image is.
    if(viewportRatio>imageRatio)
    {
        marginHeight=0.0;
        imageScale=(float)height()/(float)currentImage.height();

        // Increase marginWidth, so the ratio of the image remains.
        marginWidth=abs((float)width()-(float)currentImage.width()*imageScale)/(float)width();
    }
    // The image is wider than the viewport.
    else
    {
        marginWidth=0.0;
        imageScale=(float)width()/(float)currentImage.width();

        // Increase marginHeight, so the ratio of the image remains.
        marginHeight=abs((float)height()-(float)currentImage.height()*imageScale)/(float)height();
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f,-6.0f);

    glBindTexture(GL_TEXTURE_2D, texture);
    glColor4d(1.0, 1.0, 1.0, 1.0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glBegin(GL_QUADS);
        glTexCoord2d(0.0,0.0); glVertex2d((-1.0+marginWidth-scroll[0])*zoom, (-1.0+marginHeight+scroll[1])*zoom);
        glTexCoord2d(1.0,0.0); glVertex2d((1.0-marginWidth-scroll[0])*zoom, (-1.0+marginHeight+scroll[1])*zoom);
        glTexCoord2d(1.0,1.0); glVertex2d((1.0-marginWidth-scroll[0])*zoom, (1.0-marginHeight+scroll[1])*zoom);
        glTexCoord2d(0.0,1.0); glVertex2d((-1.0+marginWidth-scroll[0])*zoom, (1.0-marginHeight+scroll[1])*zoom);
    glEnd();

    // Render image history
    double size[2];
    int howManyImages=4;

    // Do not scale with the viewport.
    double pixelSize[2] = { 300.0, 500.0 };
    size[0] = pixelSize[0]/(double)width()*2.0;
    size[1] = pixelSize[1]/(double)height()*2.0;
    double totalViewportRatio = (double)width()/(double)height();

    // If there's any images in the history, draw them.
    if(_history.size())
    {
        // We only want the last images, calulcate their indices.
        int startIndex = _history.size()-howManyImages;
        int endIndex = _history.size()-1;
        int i = startIndex < 0 ? 0 : startIndex;

        // Loop through all running animations and compile
        // shift animation effects to a single offset.
        double shiftAnimationsOffset=0.0;
        foreach(Animation a, animations)
            if(a.type == Animation::ShiftIn)
                shiftAnimationsOffset+= (1.0-a.progress)*0.5;
            else
            if(a.type == Animation::ShiftOut)
                    shiftAnimationsOffset+= (a.progress)*0.5 - 0.5;

        // Draw the single images.
        for(;i<=endIndex;i++)
        {
            // Determine relative index in chain.
            int relativeIndex=i-startIndex;

            // Decide to shrink every image a little bit, so a margin always resides.
            double marginScaling = 0.8;

            // Determine the image offset dependent on the relative index.
            double imageOrderOffset = (double)(relativeIndex*0.5) - 0.5;
            double imageSize[2];
            double ySizePerImage=size[1]/(double)howManyImages;

            // Calculation viewport and image ratio. We are operating in pixel space,
            // hence we need to use pixels here.
            double viewportRatio = pixelSize[0]/pixelSize[1]/(double)howManyImages;
            double imageRatio = (double)_history[i].image.width()/(double)_history[i].image.height();

            // Adjust image
            if(imageRatio > viewportRatio) // image wider then viewport
            {
                imageSize[0] = size[0];
                imageSize[1] = imageSize[0] * totalViewportRatio / imageRatio;
            }
            else // viewport wider than image
            {
                imageSize[1] = ySizePerImage;
                imageSize[0] = imageSize[1] / totalViewportRatio * imageRatio;
            }

            // Basically, these is the maximum image size that fits into the viewport.
            // Give it a little margin.
            imageSize[0] *= marginScaling;
            imageSize[1] *= marginScaling;

            // Calculate the final anchors for the image.

            double y1 = -1.0+(ySizePerImage-imageSize[1])/2
                            +imageOrderOffset
                            +shiftAnimationsOffset;

            double y2 = -1.0+(ySizePerImage-imageSize[1])/2
                            +imageSize[1]
                            +imageOrderOffset
                            +shiftAnimationsOffset;

            double x1 = -1.0+(size[0]-imageSize[0])/2-y1*y1/24.0;
            double x2 = -1.0+(size[0]-imageSize[0])/2+imageSize[0]-y1*y1/24.0;


            // Bind the image as a texture and draw. Add a little bit alpha magic.
            glBindTexture(GL_TEXTURE_2D, _history[i].id);
            glBegin(GL_QUADS);
                glColor4d(1.0, 1.0, 1.0, 1.0-y1*2.0);
                glTexCoord2d(0.0, 0.0); glVertex2d(x1, y1);

                glColor4d(1.0, 1.0, 1.0, 0.8-y1*2.0);
                glTexCoord2d(1.0, 0.0); glVertex2d(x2, y1);

                glColor4d(1.0, 1.0, 1.0, 0.7-y2/2.0);
                glTexCoord2d(1.0, 1.0); glVertex2d(x2, y2);

                glColor4d(1.0, 1.0, 1.0, 0.8-y2/2.0);
                glTexCoord2d(0.0, 1.0); glVertex2d(x1, y2);
            glEnd();
        }
    }

    glColor4d(1.0, 1.0, 1.0, 0.8);
    renderText(-0.9, -0.9, 0.0, QString("Image size: %1 x %2")
               .arg(currentImage.width())
               .arg(currentImage.height()));
}

void ImageOpenGLRenderer::resizeGL(int w, int h)
{
    OpenGLRenderer::resizeGL(w, h);
    viewportRatio=(float)w/(float)h;
    updateGL();
}
