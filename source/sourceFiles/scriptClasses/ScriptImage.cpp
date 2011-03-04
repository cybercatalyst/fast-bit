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

#include "headerFiles/Main.h"
#include "headerFiles/MainWindow.h"
#include "headerFiles/scriptClasses/ScriptImage.h"
#include <QFileInfo>

ScriptImage::ScriptImage(QObject *parent)
    : QObject(parent)
    , image(QImage(640, 480, QImage::Format_RGB888))
    , imageName("unknown")
{
    connect(this,
            SIGNAL(show(QImage, QString)),
            Main::instance()->mainWindow(),
            SLOT(displayImage(QImage, QString)),
            Qt::BlockingQueuedConnection);

    setObjectName(QString("%1").arg((long)this));
}

ScriptImage::~ScriptImage()
{
}

unsigned int ScriptImage::pixel(int x, int y)
{
    return image.pixel(x, y);
}

void ScriptImage::setPixel(int x, int y, unsigned int color)
{
    image.setPixel(x, y, color);
}

void ScriptImage::resize(int width, int height)
{
    // TODO: implement
}

unsigned int ScriptImage::width()
{
    return image.width();
}

unsigned int ScriptImage::height()
{
    return image.height();
}

void ScriptImage::scale(int value)
{
    image = image.scaled(image.width() * value,
                         image.height() * value,
                         Qt::IgnoreAspectRatio,
                         Qt::FastTransformation);
}

bool ScriptImage::load(QString fileName)
{
    QFileInfo fileInfo(fileName);
    imageName = fileInfo.fileName();
    bool success = image.load(fileName);
    image = image.convertToFormat(QImage::Format_RGB888);
    return success;
}

void ScriptImage::display()
{
    emit show(image, imageName + "[" + objectName() + "]");
}

void ScriptImage::brightnessCorrection()
{

}

void ScriptImage::threshold(int value)
{
    // TODO: Methode auf zentrale Stelle mappen.
    int x, y, u;
    for(y=0;y<image.height();y++)
        for(x=0;x<image.width();x++)
        {
            QRgb pixelColor = image.pixel(x, y);
            int rgb[3] = {qRed(pixelColor), qGreen(pixelColor), qBlue(pixelColor)};

            for(u=0; u<3; u++)
                if(rgb[u] < value)
                    rgb[u] = 0;
                else
                    rgb[u] = 255;

            image.setPixel(x, y, qRgb(rgb[0], rgb[1], rgb[2]));
        }
}

void ScriptImage::laPlace()
{
    // TODO: Methode auf zentrale Stelle mappen.
    int op[3][3]={{0,-1,0}, {-1,4,-1}, {0,-1,0}};

    int weight = 8;
    int offset = 128;

    QImage result(image);
    int x, y, u, v;

    for(y=1;y<image.height()-1;y++)
        for(x=1;x<image.width()-1;x++)
        {
            int rgb[3]={0,0,0};
            for(u=-1;u<2;u++)
                for(v=-1;v<2;v++)
                {
                    QRgb color=image.pixel(x+u,y+v);
                    rgb[0]+=qRed(color)*op[u+1][v+1];
                    rgb[1]+=qGreen(color)*op[u+1][v+1];
                    rgb[2]+=qBlue(color)*op[u+1][v+1];
                }

            for(u=0;u<3;u++)
                rgb[u]=rgb[u]/weight+offset;

            result.setPixel(x, y, qRgb(rgb[0], rgb[1], rgb[2]));
        }
    image = result;
}

void ScriptImage::detectZeroCrossings()
{
    QImage result(image.width(), image.height(), image.format());

    result.fill(qRgb(0, 0, 0));
    const int zero = 128;
    int x, y;

    // Horizontal
    for(y=0;y<image.height();y++)
        for(x=1;x<image.width();x++)
        {
            QRgb color = result.pixel(x, y);
            int rgb[3] = {qRed(color), qGreen(color), qBlue(color)};
            QRgb thisColor = image.pixel(x, y);
            QRgb nextColor = image.pixel(x - 1, y);

            if((qRed(thisColor) > zero && qRed(nextColor) < zero)
             ||(qRed(thisColor) < zero && qRed(nextColor) > zero))
                rgb[0] = 255;

            if((qGreen(thisColor) > zero && qGreen(nextColor) < zero)
             ||(qGreen(thisColor) < zero && qGreen(nextColor) > zero))
                rgb[1] = 255;

            if((qBlue(thisColor) > zero && qBlue(nextColor) < zero)
             ||(qBlue(thisColor) < zero && qBlue(nextColor) > zero))
                rgb[2] = 255;

            result.setPixel(x, y, qRgb(rgb[0], rgb[1], rgb[2]));
        }

    // Vertical
    for(y=0;y<image.height()-1;y++)
        for(x=0;x<image.width();x++)
        {
            QRgb color = result.pixel(x, y);
            int rgb[3] = {qRed(color), qGreen(color), qBlue(color)};
            QRgb thisColor = image.pixel(x, y + 1);
            QRgb nextColor = image.pixel(x, y);

            if((qRed(thisColor) > zero && qRed(nextColor) < zero)
             ||(qRed(thisColor) < zero && qRed(nextColor) > zero))
                rgb[0] = 255;

            if((qGreen(thisColor) > zero && qGreen(nextColor) < zero)
             ||(qGreen(thisColor) < zero && qGreen(nextColor) > zero))
                rgb[1] = 255;

            if((qBlue(thisColor) > zero && qBlue(nextColor) < zero)
             ||(qBlue(thisColor) < zero && qBlue(nextColor) > zero))
                rgb[2] = 255;

            result.setPixel(x, y, qRgb(rgb[0], rgb[1], rgb[2]));
        }

    image = result;
}

void ScriptImage::convertToGray()
{
    int x, y;
    for(y=0;y<image.height();y++)
        for(x=0;x<image.width();x++)
        {
            QColor pixelColor = image.pixel(x, y);
            int color=(qRed(pixelColor.rgb())
                      +qGreen(pixelColor.rgb())
                      +qBlue(pixelColor.rgb()))/3;
            image.setPixel(x, y, qRgb(color, color, color));
        }
}

void ScriptImage::grayValueSplay()
{
    /**
      * Source: Klaus D. Tönnies: Grundlagen der Bildverarbeitung
      * ISBN 3-8273-7155-4
      * Page 156 - 159
      */
    int smallestGrayValue[3] = {255, 255, 255};
    int largestGrayValue[3] = {0, 0, 0};

    // Determine highest and lowest gray values in the image.
    int x, y, u;
    for(y=0;y<image.height();y++)
        for(x=0;x<image.width();x++)
        {
            QRgb pixelColor = image.pixel(x, y);
            int rgb[3] = {qRed(pixelColor), qGreen(pixelColor), qBlue(pixelColor)};
            for(u=0;u<3;u++)
            {
                smallestGrayValue[u] = rgb[u] < smallestGrayValue[u] ? rgb[u] : smallestGrayValue[u];
                largestGrayValue[u] = rgb[u] > largestGrayValue[u] ? rgb[u] : largestGrayValue[u];
            }
         }

    // Calculate a transfer funtion for each of the three color components.
    QVector<int> transferFunction[3] = { QVector<int>(256), QVector<int>(256), QVector<int>(256)};
    for(x=0;x<255;x++)
        for(u=0;u<3;u++)
            transferFunction[u][x] = (x - smallestGrayValue[u])*255
                                     / (largestGrayValue[u] - smallestGrayValue[u]);

    // Apply transfer functions.
    for(y=0;y<image.height();y++)
        for(x=0;x<image.width();x++)
        {
            QRgb pixelColor = image.pixel(x, y);
            int rgb[3] = {qRed(pixelColor), qGreen(pixelColor), qBlue(pixelColor)};

            for(u=0;u<3;u++)
                // This check prevents artifacts.
                if(largestGrayValue[u] != 255)
                    rgb[u]=transferFunction[u][rgb[u]];

            image.setPixel(x, y, qRgb(rgb[0], rgb[1], rgb[2]));
        }
}

void ScriptImage::dilatation()
{
    int x, y, u, v;
    int blackPixelCount;
    QImage result(image.width(), image.height(), image.format());
    result.fill(qRgb(255,255,255));

    for(y=1;y<image.height()-1;y++)
        for(x=1;x<image.width()-1;x++)
        {
            int rgb[3] = {qRed(image.pixel(x, y)),
                          qGreen(image.pixel(x, y)),
                          qBlue(image.pixel(x, y)) };

            // Red Channel
            blackPixelCount=0;
            for(u=-1;u<2;u++)
                for(v=-1;v<2;v++)
                {
                    if(qRed(image.pixel(x+u, y+v))<128)
                        blackPixelCount++;
                }

            if(blackPixelCount>0)
                rgb[0] = 0;

            // Green Channel
            blackPixelCount=0;
            for(u=-1;u<2;u++)
                for(v=-1;v<2;v++)
                {
                    if(qGreen(image.pixel(x+u, y+v))<128)
                        blackPixelCount++;
                }

            if(blackPixelCount>0)
                rgb[1] = 0;

            // Blue Channel
            blackPixelCount=0;
            for(u=-1;u<2;u++)
                for(v=-1;v<2;v++)
                {
                    if(qBlue(image.pixel(x+u, y+v))<128)
                        blackPixelCount++;
                }

            if(blackPixelCount>0)
                rgb[2] = 0;

            result.setPixel(x, y, qRgb(rgb[0], rgb[1], rgb[2]));
        }
    image = result;
}

