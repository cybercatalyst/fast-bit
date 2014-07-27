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

#ifndef SCRIPT_VECTOR_IMAGE_H
#define SCRIPT_VECTOR_IMAGE_H

#include <QList>
#include <QObject>

// This namespace is needed to avoid collision with WinAPI identifiers, such as Rectangle.
namespace FastBit
{
    struct Point
    {
        double x;
        double y;
    };

    class Element
    {
    public:
        virtual ~Element() { }
        enum Type
        {
            Unknown,
            Line,
            Rectangle,
            Polygon
        };

        virtual Type type() { return Unknown; }
    };

    class Line : public Element
    {
    public:
        double points[4];
        double strokeWidth;
        unsigned int color;
        Element::Type type() { return Element::Line; }
    };

    class Rectangle : public Element
    {
    public:
        double root[2];
        double size[2];
        unsigned int color;
        Element::Type type() { return Element::Rectangle; }
    };

    class Polygon : public Element
    {
    public:
        QList<FastBit::Point> points;
        unsigned int color;
        Element::Type type() { return Element::Polygon; }
    };
}

class ScriptVectorImage : public QObject
{
    Q_OBJECT
public:
    ScriptVectorImage(QObject *parent = 0);
    ~ScriptVectorImage();

public slots:
    void resize(double width, double height);
    double width();
    double height();
    unsigned int backgroundColor();
    void setBackgroundColor(unsigned int color);
    void addLine(double x1, double y1, double x2, double y2, double strokeWidth, unsigned int color);
    void addRectangle(double x1, double y1, double width, double height, unsigned int color);
    void addPolygon(unsigned int color);
    void polygon(double x, double y);
    void finishPolygon();
    void optimize();
    bool saveAsSvg(QString fileName);

private:
    struct
    {
        QList<FastBit::Element*> elements;
        FastBit::Polygon* currentPolygon;
        double width;
        double height;
        unsigned int backgroundColor;
    } m;
};

#endif // SCRIPT_VECTOR_IMAGE_H
