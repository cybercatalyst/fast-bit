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

#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

#include <QObject>
#include <QThread>
#include <QVector>
#include <QImage>
#include <QColor>
#include <QRgb>
#include <QMatrix>
#include <QHash>
#include "HistogramOpenGLRenderer.h"

/**
  * \class ImageProcessor
  * \brief Class for processing images in software.
  *
  * This class represents a software processor for images. It is a singleton and can be retrieved
  * via the static method ImageProcessor* ImageProcessor::instance().
  */
class ImageProcessor : public QObject
{
    Q_OBJECT

public:
    struct Utility
    {
        /**
          * Quantifies a set of values.
          */
        static void quantify(QVector<float>& values);

        /**
          * Smoothes a set of values.
          */
        static void smooth(QVector<float>& values);

        /**
          * Determines the wobbliness of a set of values.
          */
        static float wobbliness(QVector<float> values);

        /**
          * Numeric differentiation.
          */
        static void differentiate(QVector<float>& values);

        /**
          * Find minima.
          */
        static QVector<int> findMinima(QVector<float> values);

        /**
          * Find maxima.
          */
        static QVector<int> findMaxima(QVector<float> values);
    };

public slots:
    static ImageProcessor *instance();

    /**
      * Calculates the normalized red value distribution of an image.
      */
    void normalizedRedValueDistribution(QImage image, QObject* renderer);

    /**
      * Calculates the normalized green value distribution of an image.
      */

    void normalizedGreenValueDistribution(QImage image, QObject* renderer);

    /**
      * Calculates the normalized blue value distribution of an image.
      */
    void normalizedBlueValueDistribution(QImage image, QObject* renderer);

    /**
      * Calculates the normalized hue distribution of an image.
      */
    void normalizedHueDistribution(QImage image, QObject* renderer);

    /**
      * Calculates the normalized saturation distribution of an image.
      */

    void normalizedSaturationDistribution(QImage image, QObject* renderer);

    /**
      * Calculates the normalized value distribution of an image.
      */
    void normalizedValueDistribution(QImage image, QObject* renderer);

    /**
      * Adjusts the brightness of the image automatically.
      */
    void autoBrightness(QObject *sender, QImage image);

    /**
      * Calculates the red channel of the image.
      */
    void redFilter(QObject *sender, QImage image);

    /**
      * Calculates the green channel of the image.
      */
    void greenFilter(QObject *sender, QImage image);

    /**
      * Calculates the blue channel of the image.
      */
    void blueFilter(QObject *sender, QImage image);

    /**
      * Performs a gray value splay.
      */
    void grayValueSplay(QObject *sender, QImage image);

    /**
      * Inverts the image.
      */
    void invert(QObject *sender, QImage image);

    /**
      * Performs a threshold operation. The supplied image will be interpreted as grey valued.
      */
    void threshold(QObject *sender, QImage image, int thr);

    /**
      * Increases the brightness by bgt steps. This will clip if necessary.
      */
    void brightness(QObject *sender, QImage image, int bgt);

    /**
      * Runs a symmetric differentiation filter.
      */
    void symmetricDifferentiationFilter(QObject *sender, QImage image);

    /**
      * Runs a prewitt filter.
      */
    void prewittFilter(QObject *sender, QImage image);

    /**
      * Runs a sobel filter.
      */
    void sobelFilter(QObject *sender, QImage image);

    /**
      * Runs a Laplace filter.
      */
    void laPlaceFilter(QObject *sender, QImage image);

    /**
      * Runs a Kirsch compass filter.
      */
    void kirschCompassFilter(QObject *sender, QImage image);

    /**
      * Converts a differentiation image to absolute values.
      */
    void makeAbsolute(QObject *sender, QImage image);

    /**
      * Performs an erosion on any pixels greater than 128 in value.
      * The supplied image will be interpreted as grey valued.
      */
    void erode(QObject *sender, QImage image);

    /**
      * Converts the image to a grey value image.
      */
    void convertToGray(QObject *sender, QImage image);

    /**
      * Adds two images.
      */
    void add(QObject *sender, QImage firstImage, QImage secondImage);

    /**
      * Subtracts the second image from the first.
      */
    void subtract(QObject *sender, QImage firstImage, QImage secondImage);

    /**
      * Multiplicates two images.
      */
    void multiplicate(QObject *sender, QImage firstImage, QImage secondImage);

    /**
      * Divides the first image by the second.
      */
    void divide(QObject *sender, QImage firstImage, QImage secondImage);

    /**
      * Rotates the image.
      */
    void rotate(QObject *sender, QImage image, double degrees);

    /**
      * Fills up horizontal gaps, ie. whenever a combination of a light, a dark and a light
      * pixel is found, the center pixel is set to light.
      */
    void fillUpHorizontalGaps(QObject *sender, QImage image, int loops);

    /**
      * Fills up vertical gaps, ie. whenever a combination of a light, a dark and a light
      * pixel is found, the center pixel is set to light.
      */
    void fillUpVerticalGaps(QObject *sender, QImage image, int loops);

    /**
      * Reduces colors.
      */
    void reduceColors(QObject *sender, QImage image, int stepping);

    /**
      * Removes a certain color.
      */
    void removeColorByValue(QObject *sender, QImage image, int colorValue);

    /**
      * Detects zero crossing between pixels.
      */
    void detectZeroCrossings(QObject *sender, QImage image);

signals:
    /**
      * This signal is emitted, whenever there is a new status message.
      */
    void status(QString message);

private:
    void runOperator(QImage& image, int op[3][3], int weight, int offset);
    void clipColor(int& color);

    ImageProcessor();
    ~ImageProcessor();

    static ImageProcessor singleton;
};

#endif // IMAGE_PROCESSOR_H
