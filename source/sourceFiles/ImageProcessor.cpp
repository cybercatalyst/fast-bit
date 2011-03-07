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
#include "headerFiles/ImageProcessor.h"

#include <QStack>
#include <QVector>

ImageProcessor *ImageProcessor::instance()
{
    static ImageProcessor imageProcessor;
    return &imageProcessor;
}

void ImageProcessor::normalizedRedValueDistribution(QImage image, QObject* renderer)
{
    int i;
    QVector<float> result;
    result.resize(256);

    for(i=0;i<result.size();i++)
        result[i]=0;

    if(!image.isNull())
    {

        int x, y;
        for(y=0;y<image.height();y++)
            for(x=0;x<image.width();x++)
                result[qRed(image.pixel(x, y))]++;

        float peak=0;
        for(i=0;i<result.size();i++)
            if(result[i]>peak)
                peak=result[i];

        if(peak>0)
            for(i=0;i<result.size();i++)
                result[i]/=peak;
    }

    dynamic_cast<HistogramOpenGLRenderer*>(renderer)->renderHistogram(result);
    dynamic_cast<HistogramOpenGLRenderer*>(renderer)->update();
}

void ImageProcessor::normalizedGreenValueDistribution(QImage image, QObject* renderer)
{
    int i;
    QVector<float> result;
    result.resize(256);

    for(i=0;i<result.size();i++)
        result[i]=0;

    if(!image.isNull())
    {
        int x, y;
        for(y=0;y<image.height();y++)
            for(x=0;x<image.width();x++)
                result[qGreen(image.pixel(x, y))]++;

        float peak=0;
        for(i=0;i<result.size();i++)
            if(result[i]>peak)
                peak=result[i];

        if(peak>0)
            for(i=0;i<result.size();i++)
                result[i]/=peak;
    }

    dynamic_cast<HistogramOpenGLRenderer*>(renderer)->renderHistogram(result);
    dynamic_cast<HistogramOpenGLRenderer*>(renderer)->update();
}

void ImageProcessor::normalizedBlueValueDistribution(QImage image, QObject* renderer)
{
    int i;
    QVector<float> result;
    result.resize(256);

    for(i=0;i<result.size();i++)
        result[i]=0;

    if(!image.isNull())
    {
        int x, y;
        for(y=0;y<image.height();y++)
            for(x=0;x<image.width();x++)
                result[qBlue(image.pixel(x, y))]++;

        float peak=0;
        for(i=0;i<result.size();i++)
            if(result[i]>peak)
                peak=result[i];

        if(peak>0)
            for(i=0;i<result.size();i++)
                result[i]/=peak;
    }

    dynamic_cast<HistogramOpenGLRenderer*>(renderer)->renderHistogram(result);
    dynamic_cast<HistogramOpenGLRenderer*>(renderer)->update();
}

void ImageProcessor::normalizedHueDistribution(QImage image, QObject* renderer)
{
    int i;
    QVector<float> result;
    result.resize(360);

    for(i=0;i<result.size();i++)
        result[i]=0;

    if(!image.isNull())
    {
        int x, y;
        for(y=0;y<image.height();y++)
            for(x=0;x<image.width();x++)
            {
                int hue = QColor(image.pixel(x, y)).hue();
                if(hue != -1)
                    result[hue]++;
            }
        float peak=0;
        for(i=0;i<result.size();i++)
            if(result[i]>peak)
                peak=result[i];

        if(peak>0)
            for(i=0;i<result.size();i++)
                result[i]/=peak;
    }

    dynamic_cast<HistogramOpenGLRenderer*>(renderer)->renderHistogram(result);
    dynamic_cast<HistogramOpenGLRenderer*>(renderer)->update();
}

void ImageProcessor::normalizedSaturationDistribution(QImage image, QObject* renderer)
{
    int i;
    QVector<float> result;
    result.resize(256);

    for(i=0;i<result.size();i++)
        result[i]=0;

    if(!image.isNull())
    {
        int x, y;
        for(y=0;y<image.height();y++)
            for(x=0;x<image.width();x++)
                result[QColor(image.pixel(x, y)).saturation()]++;

        float peak=0;
        for(i=0;i<result.size();i++)
            if(result[i]>peak)
                peak=result[i];

        if(peak>0)
            for(i=0;i<result.size();i++)
                result[i]/=peak;
    }

    dynamic_cast<HistogramOpenGLRenderer*>(renderer)->renderHistogram(result);
    dynamic_cast<HistogramOpenGLRenderer*>(renderer)->update();
}

void ImageProcessor::normalizedValueDistribution(QImage image, QObject* renderer)
{
    int i;
    QVector<float> result;
    result.resize(256);

    for(i=0;i<result.size();i++)
        result[i]=0;

    if(!image.isNull())
    {
        int x, y;
        for(y=0;y<image.height();y++)
            for(x=0;x<image.width();x++)
                result[QColor(image.pixel(x, y)).value()]++;

        float peak=0;
        for(i=0;i<result.size();i++)
            if(result[i]>peak)
                peak=result[i];

        if(peak>0)
            for(i=0;i<result.size();i++)
                result[i]/=peak;
    }

    dynamic_cast<HistogramOpenGLRenderer*>(renderer)->renderHistogram(result);
    dynamic_cast<HistogramOpenGLRenderer*>(renderer)->update();
}

void ImageProcessor::Utility::quantify(QVector<float>& values)
{
    int size = values.size();
    if(!size)
        return;

    int iter;
    float possibleColors = 255.0;
    float minimalQuantificationStep = 1.0 / possibleColors;
    float quantificationStage;
    float lastQuantificationStage = 0.0;
    QStack<int> classMembers;

    for(quantificationStage=0.0;quantificationStage<1.0;quantificationStage+=minimalQuantificationStep)
    {
        classMembers.clear();
        for(iter=0;iter<size;iter++)
        {
            if(values[iter] >= lastQuantificationStage
             &&values[iter] <  quantificationStage)
                classMembers.push(iter);
        }

        if(classMembers.size() >= 15)
        {
            float arithmeticAverage = 0.0;
            foreach(int index, classMembers)
                arithmeticAverage += values[index];
            arithmeticAverage /= (float)classMembers.size();

            foreach(int index, classMembers)
                values[index] = arithmeticAverage;
            lastQuantificationStage = quantificationStage;
        }
    }

    if(classMembers.size())
    {
        float arithmeticAverage = 0.0;
        foreach(int index, classMembers)
            arithmeticAverage += values[index];
        arithmeticAverage /= (float)classMembers.size();

        foreach(int index, classMembers)
            values[index] = arithmeticAverage;
    }
}

void ImageProcessor::Utility::smooth(QVector<float>& values)
{
    int size = values.size();
    if(size < 3)
        return;

    int iter;
    for(iter = 1; iter < size - 1; iter++)
        values[iter] = (values[iter - 1] + values[iter] + values[iter + 1]) / 3;
}

float ImageProcessor::Utility::wobbliness(QVector<float> values)
{
    QVector<float> smoothValues = values;
    smooth(smoothValues);
    int iter;
    float wobbliness = 0.0;
    for(iter = 0; iter < values.size(); iter++)
        wobbliness += qAbs(smoothValues[iter] - values[iter]);

    return wobbliness / (float) values.size();
}

void ImageProcessor::Utility::differentiate(QVector<float> &values)
{
    QVector<float> result;
    int iter;

    result.push_back(0.0);
    for(iter = 1; iter < values.size() - 1; iter++)
        result.push_back(values[iter - 1] - values[iter + 1]);

    result.push_back(0.0);
    values = result;
}

QVector<int> ImageProcessor::Utility::findMinima(QVector<float> values)
{
    QVector<int> indices;
    int iter;

    differentiate(values);
    for(iter = 1; iter < values.size(); iter++)
        if(values.at(iter - 1) > 0 && values.at(iter) <= 0)
            indices.push_back(iter);

    return indices;
}


QVector<int> ImageProcessor::Utility::findMaxima(QVector<float> values)
{
    QVector<int> indices;
    int iter;

    differentiate(values);
    for(iter = 1; iter < values.size(); iter++)
        if(values.at(iter - 1) < 0 && values.at(iter) >= 0)
            indices.push_back(iter);

    return indices;
}

void ImageProcessor::autoBrightness(QObject *sender, QImage image)
{
    const QString methodName = "ImageProcessor::autoBrightness";

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Performing automatic brightness adjustment."));

    int u;
    int brightnessCorrection[3] = {0, 0, 0};
    float maxWobbliness = 0.001;

    QVector<float> distribution[3] = { QVector<float>(256), QVector<float>(256), QVector<float>(256) };

    int x, y;
    for(y=0;y<image.height();y++)
        for(x=0;x<image.width();x++)
        {
            distribution[0][qRed(image.pixel(x, y))]++;
            distribution[1][qGreen(image.pixel(x, y))]++;
            distribution[2][qBlue(image.pixel(x, y))]++;
        }

    float peak[3] = {0.0f, 0.0f, 0.0f};
    for(x=0; x<distribution[0].size(); x++)
    {
        for(y=0; y < 3; y++)
        if(distribution[y][x] > peak[y])
            peak[y] = distribution[y][x];
    }

    for(x=0; x<distribution[0].size(); x++)
    {
        for(y=0; y < 3; y++)
            if(peak[y] != 0.0f)
                distribution[y][x] /= peak[y];
    }

    for(u=0;u<3;u++)
    {
        float idealBrightness = 0.0;

        while(Utility::wobbliness(distribution[u]) > maxWobbliness)
            Utility::smooth(distribution[u]);

        QVector<int> maxima = Utility::findMaxima(distribution[u]);

        foreach(int maximum, maxima)
            idealBrightness += maximum;

        idealBrightness /= maxima.size();
        brightnessCorrection[u] = 128 - (int)idealBrightness;
    }

    emit status(QString(Main::instance().translate("ImageProcessor", "Brightness error is (R)%1/(G)%2,/(B)%3"))
                .arg(brightnessCorrection[0])
                .arg(brightnessCorrection[1])
                .arg(brightnessCorrection[2]));

    int result = ( brightnessCorrection[0]
                 + brightnessCorrection[1]
                 + brightnessCorrection[2]) / 3;

    emit status(QString(Main::instance().translate("ImageProcessor", "Modifying brightness by %1.")).arg(result));

    for(y=0;y<image.height();y++)
        for(x=0;x<image.width();x++)
        {
            int r=qRed(image.pixel(x, y)) + result;
            int g=qGreen(image.pixel(x, y)) + result;
            int b=qBlue(image.pixel(x, y)) + result;

            clipColor(r);
            clipColor(g);
            clipColor(b);

            image.setPixel(x, y, qRgb(r, g, b));
        }


    QMetaObject::invokeMethod(sender, "handleImage",
                              Qt::QueuedConnection,
                              Q_ARG(QImage, image));

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Done."));
}

void ImageProcessor::redFilter(QObject *sender, QImage image)
{
    const QString methodName = "ImageProcessor::redFilter";

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Performing red filter."));

    int x, y;
    for(y=0;y<image.height();y++)
        for(x=0;x<image.width();x++)
            image.setPixel(x, y, qRgb(qRed(image.pixel(x, y)), 0, 0));

    QMetaObject::invokeMethod(sender, "handleImage",
                              Qt::QueuedConnection,
                              Q_ARG(QImage, image));

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Done."));
}

void ImageProcessor::greenFilter(QObject *sender, QImage image)
{
    const QString methodName = "ImageProcessor::greenFilter";

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Performing green filter."));

    int x, y;
    for(y=0;y<image.height();y++)
        for(x=0;x<image.width();x++)
            image.setPixel(x, y, qRgb(0, qGreen(image.pixel(x, y)), 0));

    QMetaObject::invokeMethod(sender, "handleImage",
                              Qt::QueuedConnection,
                              Q_ARG(QImage, image));

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Done."));
}

void ImageProcessor::grayValueSplay(QObject *sender, QImage image)
{
    /**
      * Source: Klaus D. Tönnies: Grundlagen der Bildverarbeitung
      * ISBN 3-8273-7155-4
      * Page 156 - 159
      */
    const QString methodName = "ImageProcessor::grayValueSplay";

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Performing gray value splay."));

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

    QMetaObject::invokeMethod(sender, "handleImage",
                              Qt::QueuedConnection,
                              Q_ARG(QImage, image));

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Done."));
}

void ImageProcessor::blueFilter(QObject *sender, QImage image)
{
    const QString methodName = "ImageProcessor::blueFilter";

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Performing blue filter."));

    int x, y;
    for(y=0;y<image.height();y++)
        for(x=0;x<image.width();x++)
            image.setPixel(x, y, qRgb(0, 0, qBlue(image.pixel(x, y))));

    QMetaObject::invokeMethod(sender, "handleImage",
                              Qt::QueuedConnection,
                              Q_ARG(QImage, image));

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Done."));
}

void ImageProcessor::invert(QObject *sender, QImage image)
{
    const QString methodName = "ImageProcessor::invert";

    image.invertPixels();

    QMetaObject::invokeMethod(sender, "handleImage",
                              Qt::QueuedConnection,
                              Q_ARG(QImage, image));

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Done."));
}

void ImageProcessor::threshold(QObject *sender, QImage image, int thr)
{
    const QString methodName = "ImageProcessor::threshold";

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Performing threshold operation."));
    int x, y, u;
    for(y=0;y<image.height();y++)
        for(x=0;x<image.width();x++)
        {
            QRgb pixelColor = image.pixel(x, y);
            int rgb[3] = {qRed(pixelColor), qGreen(pixelColor), qBlue(pixelColor)};

            for(u=0; u<3; u++)
                if(rgb[u] < thr)
                    rgb[u] = 0;
                else
                    rgb[u] = 255;

            image.setPixel(x, y, qRgb(rgb[0], rgb[1], rgb[2]));
        }

    QMetaObject::invokeMethod(sender, "handleImage",
                              Qt::QueuedConnection,
                              Q_ARG(QImage, image));

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Done."));
}

void ImageProcessor::brightness(QObject *sender, QImage image, int bgt)
{
    const QString methodName = "ImageProcessor::brightness";

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Applying brightness."));
    int x, y;
    for(y=0;y<image.height();y++)
        for(x=0;x<image.width();x++)
        {
            int r=qRed(image.pixel(x, y))+bgt;
            int g=qGreen(image.pixel(x, y))+bgt;
            int b=qBlue(image.pixel(x, y))+bgt;

            clipColor(r);
            clipColor(g);
            clipColor(b);

            image.setPixel(x, y, qRgb(r, g, b));
        }

    QMetaObject::invokeMethod(sender, "handleImage",
                              Qt::QueuedConnection,
                              Q_ARG(QImage, image));

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Done."));
}

void ImageProcessor::symmetricDifferentiationFilter(QObject *sender, QImage image)
{
    const QString methodName = "ImageProcessor::symmetricDifferentiationFilter";
    QImage images[2] = { image, image };
    QImage result(image);
    int x, y, u;
    int op[3]={-1, 0, 1};

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Generating horizontal differentiation image."));
    for(y=0;y<image.height();y++)
        for(x=1;x<image.width()-1;x++)
        {
            int rgb[3]={0,0,0};
            for(u=-1;u<2;u++)
            {
                QRgb color=image.pixel(x+u,y);
                rgb[0]+=qRed(color)*op[u+1];
                rgb[1]+=qGreen(color)*op[u+1];
                rgb[2]+=qBlue(color)*op[u+1];
            }

            for(u=0;u<3;u++)
                rgb[u]=rgb[u]/2+128;

            images[0].setPixel(x, y, qRgb(rgb[0], rgb[1], rgb[2]));
        }

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Generating vertical differentiation image."));
    for(y=1;y<image.height()-1;y++)
        for(x=0;x<image.width();x++)
        {
            int rgb[3]={0,0,0};
            for(u=-1;u<2;u++)
            {
                QRgb color=image.pixel(x,y+u);
                rgb[0]+=qRed(color)*op[u+1];
                rgb[1]+=qGreen(color)*op[u+1];
                rgb[2]+=qBlue(color)*op[u+1];
            }

            for(u=0;u<3;u++)
                rgb[u]=rgb[u]/2+128;

            images[1].setPixel(x, y, qRgb(rgb[0], rgb[1], rgb[2]));
        }

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Combining differentiation images."));
    for(y=0;y<image.height();y++)
        for(x=0;x<image.width();x++)
        {
            int rgb[3] = {128, 128, 128};
            for(u=0;u<2;u++)
            {
                QRgb pixelColor=images[u].pixel(x, y);
                if(abs(qRed(pixelColor)-128)>abs(rgb[0]-128))
                    rgb[0]=qRed(pixelColor);

                if(abs(qGreen(pixelColor)-128)>abs(rgb[1]-128))
                    rgb[1]=qGreen(pixelColor);

                if(abs(qBlue(pixelColor)-128)>abs(rgb[2]-128))
                    rgb[2]=qBlue(pixelColor);
            }
            result.setPixel(x, y, qRgb(rgb[0], rgb[1], rgb[2]));
        }

    QMetaObject::invokeMethod(sender, "handleImage",
                              Qt::QueuedConnection,
                              Q_ARG(QImage, result));

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Done."));
}

void ImageProcessor::prewittFilter(QObject *sender, QImage image)
{
    const QString methodName = "ImageProcessor::prewittFilter";
    int x, y, u;
    int opHorizontal[3][3]={{-1,-1,-1}, {0,0,0}, {1,1,1}};
    int opVertical[3][3]={{-1,0,1}, {-1,0,1}, {-1,0,1}};
    QImage images[2] = { image, image };
    QImage result(image);

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Generating horizontal differentiation image."));
    runOperator(images[0], opHorizontal, 6, 128);

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Generating vertical differentiation image."));
    runOperator(images[1], opVertical, 6, 128);

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Combining differentiation images."));
    for(y=0;y<image.height();y++)
        for(x=0;x<image.width();x++)
        {
            int rgb[3] = {128, 128, 128};
            for(u=0;u<2;u++)
            {
                QRgb pixelColor=images[u].pixel(x, y);
                if(abs(qRed(pixelColor)-128)>abs(rgb[0]-128))
                    rgb[0]=qRed(pixelColor);

                if(abs(qGreen(pixelColor)-128)>abs(rgb[1]-128))
                    rgb[1]=qGreen(pixelColor);

                if(abs(qBlue(pixelColor)-128)>abs(rgb[2]-128))
                    rgb[2]=qBlue(pixelColor);
            }
            result.setPixel(x, y, qRgb(rgb[0], rgb[1], rgb[2]));
        }

    QMetaObject::invokeMethod(sender, "handleImage",
                              Qt::QueuedConnection,
                              Q_ARG(QImage, result));

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Done."));
}

void ImageProcessor::sobelFilter(QObject *sender, QImage image)
{
    const QString methodName = "ImageProcessor::sobelFilter";
    int x, y, u;
    int opHorizontal[3][3]={{-1,-2,-1}, {0,0,0}, {1,2,1}};
    int opVertical[3][3]={{-1,0,1}, {-2,0,2}, {-1,0,1}};
    QImage images[2] = { image, image };
    QImage result(image);

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Generating horizontal differentiation image."));
    runOperator(images[0], opHorizontal, 8, 128);

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Generating vertical differentiation image."));
    runOperator(images[1], opVertical, 8, 128);

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Combining differentiation images."));
    for(y=0;y<image.height();y++)
        for(x=0;x<image.width();x++)
        {
            int rgb[3] = {128, 128, 128};
            for(u=0;u<2;u++)
            {
                QRgb pixelColor=images[u].pixel(x, y);
                if(abs(qRed(pixelColor)-128)>abs(rgb[0]-128))
                    rgb[0]=qRed(pixelColor);

                if(abs(qGreen(pixelColor)-128)>abs(rgb[1]-128))
                    rgb[1]=qGreen(pixelColor);

                if(abs(qBlue(pixelColor)-128)>abs(rgb[2]-128))
                    rgb[2]=qBlue(pixelColor);
            }
            result.setPixel(x, y, qRgb(rgb[0], rgb[1], rgb[2]));
        }

    QMetaObject::invokeMethod(sender, "handleImage",
                              Qt::QueuedConnection,
                              Q_ARG(QImage, result));

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Done."));
}

void ImageProcessor::laPlaceFilter(QObject *sender, QImage image)
{
    const QString methodName = "ImageProcessor::laPlaceFilter";
    int op[3][3]={{0,-1,0}, {-1,4,-1}, {0,-1,0}};

    runOperator(image, op, 8, 128);

    QMetaObject::invokeMethod(sender, "handleImage",
                              Qt::QueuedConnection,
                              Q_ARG(QImage, image));

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Done."));
}

void ImageProcessor::kirschCompassFilter(QObject* sender, QImage image)
{
    const QString methodName = "ImageProcessor::kirschCompassFilter";
    int x, y, u;
    QImage images[8];
    QImage result(image);

    int op[8][3][3]=
    {{{ 5, 5, 5 },
      {-3, 0,-3 },
      {-3,-3,-3 }},

     {{ 5, 5,-3 },
      { 5, 0,-3 },
      {-3,-3,-3 }},

     {{ 5,-3,-3 },
      { 5, 0,-3 },
      { 5,-3,-3 }},

     {{-3,-3,-3 },
      { 5, 0,-3 },
      { 5, 5,-3 }},

     {{-3,-3,-3 },
      {-3, 0,-3 },
      { 5, 5, 5 }},

     {{-3,-3,-3 },
      {-3, 0, 5 },
      {-3, 5, 5 }},

     {{-3,-3, 5 },
      {-3, 0, 5 },
      {-3,-3, 5 }},

     {{-3, 5, 5 },
      {-3, 0, 5 },
      {-3,-3,-3 }}};

    for(u=0;u<8;u++)
    {
        images[u]=image;
        emit status(methodName + QString(Main::instance().translate("ImageProcessor", ": Generating differentiation image for direction %1.")).arg(u+1));
        runOperator(images[u], op[u], 30, 128);
    }

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Combining differentiation images."));
    for(y=0;y<image.height();y++)
        for(x=0;x<image.width();x++)
        {
            int rgb[3] = {0, 0, 0};
            for(u=0;u<8;u++)
            {
                QRgb pixelColor=images[u].pixel(x, y);
                if(qRed(pixelColor)>rgb[0])
                    rgb[0]=qRed(pixelColor);

                if(qGreen(pixelColor)>rgb[1])
                    rgb[1]=qGreen(pixelColor);

                if(qBlue(pixelColor)>rgb[2])
                    rgb[2]=qBlue(pixelColor);
            }
            result.setPixel(x, y, qRgb(rgb[0], rgb[1], rgb[2]));
        }

    QMetaObject::invokeMethod(sender, "handleImage",
                              Qt::QueuedConnection,
                              Q_ARG(QImage, result));

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Done."));
}

void ImageProcessor::makeAbsolute(QObject *sender, QImage image)
{
    const QString methodName = "ImageProcessor::makeAbsolute";
    int x, y;

    for(y=0;y<image.height();y++)
        for(x=0;x<image.width();x++)
        {
            QRgb color = image.pixel(x, y);
            image.setPixel(x, y, qRgb(
                    abs(qRed(color) - 128),
                    abs(qGreen(color) - 128),
                    abs(qBlue(color) - 128)));
        }

    QMetaObject::invokeMethod(sender, "handleImage",
                              Qt::QueuedConnection,
                              Q_ARG(QImage, image));

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Done."));
}

void ImageProcessor::erode(QObject *sender, QImage image)
{
    const QString methodName = "ImageProcessor::erode";
    int x, y, u, v;
    int blackPixelCount;

    QImage erosionImage(image.width(), image.height(), image.format());
    erosionImage.fill(qRgb(0,0,0));

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Performing erosion."));
    for(y=1;y<image.height()-1;y++)
        for(x=1;x<image.width()-1;x++)
        {
            int rgb[3] = {0,0,0};

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
            else
                rgb[0] = qRed(image.pixel(x, y));

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
            else
                rgb[1] = qGreen(image.pixel(x, y));

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
            else
                rgb[2] = qBlue(image.pixel(x, y));

            erosionImage.setPixel(x, y, qRgb(rgb[0], rgb[1], rgb[2]));
        }

    QMetaObject::invokeMethod(sender, "handleImage",
                              Qt::QueuedConnection,
                              Q_ARG(QImage, erosionImage));

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Done."));
}

void ImageProcessor::convertToGray(QObject *sender, QImage image)
{
    const QString methodName = "ImageProcessor::convertToGray";
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

    QMetaObject::invokeMethod(sender, "handleImage",
                              Qt::QueuedConnection,
                              Q_ARG(QImage, image));

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Done."));
}

void ImageProcessor::add(QObject *sender, QImage firstImage, QImage secondImage)
{
    const QString methodName = "ImageProcessor::add";
    int width = firstImage.width() < secondImage.width() ? firstImage.width() : secondImage.width();
    int height = firstImage.height() < secondImage.height() ? firstImage.height() : secondImage.height();
    int x, y;

    for(y=0;y<height;y++)
        for(x=0;x<width;x++)
        {
            int r = qRed(firstImage.pixel(x, y)) + qRed(secondImage.pixel(x, y));
            int g = qGreen(firstImage.pixel(x, y)) + qGreen(secondImage.pixel(x, y));
            int b = qBlue(firstImage.pixel(x, y)) + qBlue(secondImage.pixel(x, y));

            clipColor(r);
            clipColor(g);
            clipColor(b);

            firstImage.setPixel(x, y, QColor(r, g, b).rgb());
        }

    QMetaObject::invokeMethod(sender, "handleImage",
                              Qt::QueuedConnection,
                              Q_ARG(QImage, firstImage));

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Done."));
}

void ImageProcessor::subtract(QObject *sender, QImage firstImage, QImage secondImage)
{
    const QString methodName = "ImageProcessor::subtract";
    int width = firstImage.width() < secondImage.width() ? firstImage.width() : secondImage.width();
    int height = firstImage.height() < secondImage.height() ? firstImage.height() : secondImage.height();
    int x, y;

    for(y=0;y<height;y++)
        for(x=0;x<width;x++)
        {
            int r = qRed(firstImage.pixel(x, y)) - qRed(secondImage.pixel(x, y));
            int g = qGreen(firstImage.pixel(x, y)) - qGreen(secondImage.pixel(x, y));
            int b = qBlue(firstImage.pixel(x, y)) - qBlue(secondImage.pixel(x, y));

            clipColor(r);
            clipColor(g);
            clipColor(b);

            firstImage.setPixel(x, y, QColor(r, g, b).rgb());
        }

    QMetaObject::invokeMethod(sender, "handleImage",
                              Qt::QueuedConnection,
                              Q_ARG(QImage, firstImage));

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Done."));
}

void ImageProcessor::multiplicate(QObject *sender, QImage firstImage, QImage secondImage)
{
    const QString methodName = "ImageProcessor::multiplicate";
    int width = firstImage.width() < secondImage.width() ? firstImage.width() : secondImage.width();
    int height = firstImage.height() < secondImage.height() ? firstImage.height() : secondImage.height();
    int x, y;

    for(y=0;y<height;y++)
        for(x=0;x<width;x++)
        {
            int r = qRed(firstImage.pixel(x, y)) * qRed(secondImage.pixel(x, y));
            int g = qGreen(firstImage.pixel(x, y)) * qGreen(secondImage.pixel(x, y));
            int b = qBlue(firstImage.pixel(x, y)) * qBlue(secondImage.pixel(x, y));

            clipColor(r);
            clipColor(g);
            clipColor(b);

            firstImage.setPixel(x, y, qRgb(r, g, b));
        }

    QMetaObject::invokeMethod(sender, "handleImage",
                              Qt::QueuedConnection,
                              Q_ARG(QImage, firstImage));

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Done."));
}

void ImageProcessor::divide(QObject *sender, QImage firstImage, QImage secondImage)
{
    const QString methodName = "ImageProcessor::divide";
    int width = firstImage.width() < secondImage.width() ? firstImage.width() : secondImage.width();
    int height = firstImage.height() < secondImage.height() ? firstImage.height() : secondImage.height();
    int x, y;

    for(y=0;y<height;y++)
        for(x=0;x<width;x++)
        {
            int r2 = qRed(secondImage.pixel(x, y));
            int g2 = qGreen(secondImage.pixel(x, y));
            int b2 = qBlue(secondImage.pixel(x, y));
            int r = 255, g = 255, b = 255;

            if(r2!=0)
                r = qRed(firstImage.pixel(x, y)) / r2;

            if(g2!=0)
                g = qGreen(firstImage.pixel(x, y)) / g2;

            if(b2!=0)
                b = qBlue(firstImage.pixel(x, y)) / b2;

            clipColor(r);
            clipColor(g);
            clipColor(b);

            firstImage.setPixel(x, y, QColor(r, g, b).rgb());
        }

    QMetaObject::invokeMethod(sender, "handleImage",
                              Qt::QueuedConnection,
                              Q_ARG(QImage, firstImage));

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Done."));
}

void ImageProcessor::rotate(QObject *sender, QImage image, double degrees)
{
    const QString methodName = "ImageProcessor::rotate";
    QMatrix rotationMatrix;
    rotationMatrix.rotate(degrees);
    QImage rotatedImage = image.transformed(rotationMatrix);

    QMetaObject::invokeMethod(sender, "handleImage",
                              Qt::QueuedConnection,
                              Q_ARG(QImage, rotatedImage));

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Done."));
}


void ImageProcessor::fillUpHorizontalGaps(QObject *sender, QImage image, int loops)
{
    const QString methodName = "ImageProcessor::FillUpHorizontalGaps";
    int y, x, r, g, b, l, left, middle, right;

    for(l=0;l<loops;l++)
        for(y=0;y<image.height();y++)
            for(x=1;x<image.width()-1;x++)
            {
                QRgb leftPixel = image.pixel(x-1, y),
                     middlePixel = image.pixel(x, y),
                     rightPixel = image.pixel(x+1, y);

                // Red channel
                left = qRed(leftPixel);
                middle = qRed(middlePixel);
                right = qRed(rightPixel);

                if(middle<left&&middle<right)
                    r = (left+right)/2;
                else
                    r = middle;

                // Green channel
                left = qGreen(leftPixel);
                middle = qGreen(middlePixel);
                right = qGreen(rightPixel);

                if(middle<left&&middle<right)
                    g = (left+right)/2;
                else
                    g = middle;

                // Blue channel
                left = qBlue(leftPixel);
                middle = qBlue(middlePixel);
                right = qBlue(rightPixel);

                if(middle<left&&middle<right)
                    b = (left+right)/2;
                else
                    b = middle;

                // Set resulting pixel
                image.setPixel(x, y, qRgb(r, g, b));
            }

    QMetaObject::invokeMethod(sender, "handleImage",
                              Qt::QueuedConnection,
                              Q_ARG(QImage, image));

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Done."));
}

void ImageProcessor::fillUpVerticalGaps(QObject *sender, QImage image, int loops)
{
    const QString methodName = "ImageProcessor::fillUpVerticalGaps";
    int y, x, r, g, b, l, up, middle, down;

    for(l=0;l<loops;l++)
        for(y=1;y<image.height()-1;y++)
            for(x=0;x<image.width();x++)
            {
                QRgb upPixel = image.pixel(x, y-1),
                     middlePixel = image.pixel(x, y),
                     downPixel = image.pixel(x, y+1);

                // Red channel
                up = qRed(upPixel);
                middle = qRed(middlePixel);
                down = qRed(downPixel);

                if(middle<up&&middle<down)
                    r = (up+down)/2;
                else
                    r = middle;

                // Green channel
                up = qGreen(upPixel);
                middle = qGreen(middlePixel);
                down = qGreen(downPixel);

                if(middle<up&&middle<down)
                    g = (up+down)/2;
                else
                    g = middle;

                // Blue channel
                up = qBlue(upPixel);
                middle = qBlue(middlePixel);
                down = qBlue(downPixel);

                if(middle<up&&middle<down)
                    b = (up+down)/2;
                else
                    b = middle;

                // Set resulting pixel
                image.setPixel(x, y, qRgb(r, g, b));
            }

    QMetaObject::invokeMethod(sender, "handleImage",
                              Qt::QueuedConnection,
                              Q_ARG(QImage, image));

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Done."));
}


void ImageProcessor::reduceColors(QObject *sender, QImage image, int stepping)
{
    const QString methodName = "ImageProcessor::reduceColors";
    int x, y, u;

    for(y=0;y<image.height();y++)
        for(x=0;x<image.width();x++)
        {
            unsigned int color = image.pixel(x, y);
            int rgb[3] = {qRed(color), qGreen(color), qBlue(color)};
            for(u=0;u<3;u++)
            rgb[u] = (int)rgb[u]/stepping*stepping+stepping/2;

            image.setPixel(x, y, qRgb(rgb[0], rgb[1], rgb[2]));
        }

    QMetaObject::invokeMethod(sender, "handleImage",
                              Qt::QueuedConnection,
                              Q_ARG(QImage, image));

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Done."));
}

void ImageProcessor::removeColorByValue(QObject *sender, QImage image, int colorValue)
{
    const QString methodName = "ImageProcessor::removeColorByValue";
    int x, y, u;

    for(y=0;y<image.height();y++)
        for(x=0;x<image.width();x++)
        {
            unsigned int color = image.pixel(x, y);
            int rgb[3] = {qRed(color), qGreen(color), qBlue(color)};
            for(u=0;u<3;u++)
                rgb[u] = (rgb[u] == colorValue) ? 0 : rgb[u];

            image.setPixel(x, y, qRgb(rgb[0], rgb[1], rgb[2]));
        }

    QMetaObject::invokeMethod(sender, "handleImage",
                              Qt::QueuedConnection,
                              Q_ARG(QImage, image));

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Done."));
}

void ImageProcessor::detectZeroCrossings(QObject *sender, QImage image)
{
    /**
      * Source: Klaus D. Tönnies: Grundlagen der Bildverarbeitung
      * ISBN 3-8273-7155-4
      * Page 182 - 183
      */

    const QString methodName = "ImageProcessor::detectZeroCrossings";
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

    QMetaObject::invokeMethod(sender, "handleImage",
                              Qt::QueuedConnection,
                              Q_ARG(QImage, result));

    emit status(methodName + Main::instance().translate("ImageProcessor", ": Done."));
}

void ImageProcessor::runOperator(QImage& image, int op[3][3], int weight, int offset)
{
    const QString methodName = "ImageProcessor::runOperator";
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
    image=result;
    emit status(methodName + Main::instance().translate("ImageProcessor", ": Done."));
}

void ImageProcessor::clipColor(int &color)
{
    color = color < 0 ? 0 : color;
    color = color > 255 ? 255 : color;
}

ImageProcessor::ImageProcessor()
    : QObject()
{
    //processingThread = new QThread();
    //processingThread->start();
    //moveToThread(processingThread);
}

ImageProcessor::~ImageProcessor()
{
    //processingThread->quit();
    //delete processingThread;
}
