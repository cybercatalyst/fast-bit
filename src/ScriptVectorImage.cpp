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
#include "MainWindow.h"
#include "ScriptVectorImage.h"

#include <QFile>

ScriptVectorImage::ScriptVectorImage(QObject *parent)
    : QObject(parent)
{
    setObjectName(QString("%1").arg((long)this));
}

ScriptVectorImage::~ScriptVectorImage()
{
    foreach(FastBit::Element* element, m.elements)
        delete element;
}

void ScriptVectorImage::resize(double width, double height)
{
    m.width = width;
    m.height = height;
}

double ScriptVectorImage::width()
{
    return m.width;
}

double ScriptVectorImage::height()
{
    return m.height;
}

unsigned int ScriptVectorImage::backgroundColor()
{
    return m.backgroundColor;
}

void ScriptVectorImage::setBackgroundColor(unsigned int color)
{
    m.backgroundColor = color;
}

void ScriptVectorImage::addLine(double x1, double y1, double x2, double y2, double strokeWidth, unsigned int color)
{
    FastBit::Line* newLine = new FastBit::Line();
    newLine->points[0] = x1;
    newLine->points[1] = y1;
    newLine->points[2] = x2;
    newLine->points[3] = y2;
    newLine->strokeWidth = strokeWidth;
    newLine->color = color;
    m.elements.append(newLine);
}

void ScriptVectorImage::addRectangle(double x1, double y1, double width, double height, unsigned int color)
{
    FastBit::Rectangle* newRectangle = new FastBit::Rectangle();
    newRectangle->root[0] = x1;
    newRectangle->root[1] = y1;
    newRectangle->size[0] = width;
    newRectangle->size[1] = height;
    newRectangle->color = color;
    m.elements.append(newRectangle);
}

void ScriptVectorImage::addPolygon(unsigned int color)
{
    m.currentPolygon = new FastBit::Polygon();
    m.currentPolygon->color = color;
}

void ScriptVectorImage::polygon(double x, double y)
{
    FastBit::Point p;
    p.x = x;
    p.y = y;
    m.currentPolygon->points.append(p);
}

void ScriptVectorImage::finishPolygon()
{
    m.elements.append(m.currentPolygon);
}

bool ScriptVectorImage::saveAsSvg(QString fileName)
{
    QFile file(fileName);
    file.open(QFile::WriteOnly);

    if(!file.isOpen())
        return false;

    // Write header.
    file.write("<?xml version=\"1.0\" standalone=\"no\" ?>\n"
               "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 20010904//EN\" \n"
               "\"http://www.w3.org/TR/2001/REC-SVG-20010904/DTD/svg10.dtd\">\n");

    // Write svg opening tag.
    file.write(QString("<svg width=\"%1\" height=\"%2\" xmlns=\"http://www.w3.org/2000/svg\" \n"
                       "xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n")
               .arg(m.width)
               .arg(m.height)
               .toLocal8Bit());

    // Write background rect.
    file.write(QString("<rect x=\"%1\" y=\"%2\" width=\"%3\" height=\"%4\" "
                       "fill=\"rgb(%5,%6,%7)\" opacity=\"%8\" stroke=\"none\" />\n")
               .arg(0)
               .arg(0)
               .arg(m.width + 1)
               .arg(m.height + 1)
               .arg(qRed(m.backgroundColor))
               .arg(qGreen(m.backgroundColor))
               .arg(qBlue(m.backgroundColor))
               .arg((double)qAlpha(m.backgroundColor) / 255.0)
               .toLocal8Bit());

    // Define pointers to each class, this avoids compiler warnings.
    FastBit::Line* line;
    FastBit::Rectangle* rectangle;
    FastBit::Polygon* polygon;

    // Write each element.
    foreach(FastBit::Element* element, m.elements)
    {
        switch(element->type())
        {
        case FastBit::Element::Line:
            line = dynamic_cast<FastBit::Line*>(element);
            file.write(QString("<line x1=\"%1\" y1=\"%2\" x2=\"%3\" y2=\"%4\" "
                               "style=\"stroke:rgb(%5,%6,%7); opacity:%8; stroke-width:%9;\" />\n")
                       .arg(line->points[0])
                       .arg(line->points[1])
                       .arg(line->points[2])
                       .arg(line->points[3])
                       .arg(qRed(line->color))
                       .arg(qGreen(line->color))
                       .arg(qBlue(line->color))
                       .arg((double)qAlpha(line->color) / 255.0)
                       .arg(line->strokeWidth)
                       .toLocal8Bit());
            break;
        case FastBit::Element::Rectangle:
            rectangle = dynamic_cast<FastBit::Rectangle*>(element);
            file.write(QString("<rect x=\"%1\" y=\"%2\" width=\"%3\" height=\"%4\" "
                               "fill=\"rgb(%5,%6,%7)\" opacity=\"%8\" stroke=\"none\" />\n")
                       .arg(rectangle->root[0])
                       .arg(rectangle->root[1])
                       .arg(rectangle->size[0])
                       .arg(rectangle->size[1])
                       .arg(qRed(rectangle->color))
                       .arg(qGreen(rectangle->color))
                       .arg(qBlue(rectangle->color))
                       .arg((double)qAlpha(rectangle->color) / 255.0)
                       .toLocal8Bit());
            break;
        case FastBit::Element::Polygon:
            polygon = dynamic_cast<FastBit::Polygon*>(element);
            file.write("<polygon points=\"");
            foreach(FastBit::Point point, polygon->points)
            {
                file.write(QString("%1,%2 ")
                           .arg(point.x)
                           .arg(point.y)
                           .toLocal8Bit());
            }
            file.write(QString("\" style=\"fill:rgb(%1,%2,%3); opacity:%4 stroke:none; "
                               "stroke-width:0\" />\n")
                            .arg(qRed(polygon->color))
                            .arg(qGreen(polygon->color))
                            .arg(qBlue(polygon->color))
                            .arg((double)qAlpha(polygon->color) / 255.0)
                            .toLocal8Bit());
            break;
        case FastBit::Element::Unknown:
            // Avoids compiler warnings.
            break;
        }
    }

    // Write svg closing tag.
    file.write("</svg>");

    // Close file.
    file.close();
    return true;
}

void ScriptVectorImage::optimize()
{
    // Durchlaufe jedes graphische Element.
    foreach(FastBit::Element* element, m.elements)
    {
        // Pruefe, ob das betreffende Element ein Polygon ist.
        if(element->type() == FastBit::Element::Polygon)
        {
            // Falls ja, dann ueberfuehre es zu einem Polygon.
            FastBit::Polygon* polygon = dynamic_cast<FastBit::Polygon*>(element);

            // Glaettet das Polygon.
            for(int v = 0; v < 15; v++)
            for(int u = 0; u < polygon->points.size() + 3; u++)
            {
                int i[5] = { (u + 0) % polygon->points.size(),
                             (u + 1) % polygon->points.size(),
                             (u + 2) % polygon->points.size(),
                             (u + 3) % polygon->points.size(),
                             (u + 4) % polygon->points.size() };

                FastBit::Point p;
                p.x = ( polygon->points[i[0]].x
                      + polygon->points[i[1]].x
                      + polygon->points[i[2]].x
                      + polygon->points[i[3]].x
                      + polygon->points[i[4]].x ) / 5;

                p.y = ( polygon->points[i[0]].y
                      + polygon->points[i[1]].y
                      + polygon->points[i[2]].y
                      + polygon->points[i[3]].y
                      + polygon->points[i[4]].y ) / 5;

                polygon->points[i[2]] = p;
            }

            // Lege eine Liste fuer die jeweiligen Indizes an.
            int i[3] = { 0, 1, 2 };

            // Durchlaufe alle Punkte, die zu dem Polygon gehoeren.
            for(; i[2] < polygon->points.size();)
            {
                FastBit::Point vectors[2];
                vectors[0].x = polygon->points.at(i[1]).x - polygon->points.at(i[0]).x;
                vectors[0].y = polygon->points.at(i[1]).y - polygon->points.at(i[0]).y;

                vectors[1].x = polygon->points.at(i[2]).x - polygon->points.at(i[0]).x;
                vectors[1].y = polygon->points.at(i[2]).y - polygon->points.at(i[0]).y;

                double length[2]
                    = { sqrt(vectors[0].x * vectors[0].x + vectors[0].y * vectors[0].y),
                        sqrt(vectors[1].x * vectors[1].x + vectors[1].y * vectors[1].y) };

                if(vectors[0].x * vectors[1].x + vectors[0].y * vectors[1].y
                   == length[0] * length[1])
                {
                    // Die beiden Vektoren sind parallel und zeigen in die gleiche Richtung.
                    // Finde heraus, welcher von beiden der laengere ist, der andere ist dann
                    // obsolet.

                    int dominant = length[0] > length[1] ? 0 : 1;

                    // Entferne den kuerzeren.
                    polygon->points.removeAt(i[1] + !dominant);

                    // Durch das Entfernen eines Punktes rutschen alle weiteren Punkte um
                    // eine Stelle nach links. Pruefe daher, ob der vorderste Index
                    // immernoch gueltig ist.
                    if(i[2] >= polygon->points.size())
                        break;
                }
                else
                {
                    // Die beiden Vektoren sind nicht parallel oder zeigen nicht in die
                    // gleiche Richtung. Wir bewegen daher das Indexfenster um eine Stelle
                    // nach rechts.
                    i[2]++;
                    i[1] = i[2] - 1;
                    i[0] = i[1] - 1;
                }
            }
        }
    }
}
