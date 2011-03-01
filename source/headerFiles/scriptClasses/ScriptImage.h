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

#ifndef SCRIPT_IMAGE_H
#define SCRIPT_IMAGE_H

#include <QImage>
#include <QObject>

class ScriptImage : public QObject
{
    Q_OBJECT
public:
    ScriptImage(QObject *parent = 0);
    ~ScriptImage();

public slots:
    unsigned int pixel(int x, int y);
    void setPixel(int x, int y, unsigned int color);
    void resize(int width, int height);
    unsigned int width();
    unsigned int height();
    void scale(int value);
    bool load(QString fileName);
    void display();

    void brightnessCorrection();
    void threshold(int value);
    void laPlace();
    void detectZeroCrossings();
    void convertToGray();
    void grayValueSplay();
    void dilatation();

signals:
    void show(QImage image, QString title);

private:
    QImage image;
    QString imageName;
};

#endif // SCRIPT_IMAGE_H
