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

#ifndef GRAPH_H
#define GRAPH_H

#include <QDockWidget>
#include <QTabWidget>

#include "OpenGLRenderer.h"
#include "HistogramOpenGLRenderer.h"

class Graph : public QDockWidget
{
    Q_OBJECT

public:
    Graph(QWidget *parent = 0);
    ~Graph();

    /**
      * Adds a renderer object as a new graph tab.
      */
    void addRenderer(QString description, OpenGLRenderer *renderer);

    /**
      * Clear renderers.
      */
    void clearRenderers();

public slots:
    /**
      * Removes a specific renderer by index.
      */
    void clearRenderer(int index);

    /**
      * Updates the statistics according to the given image.
      */
    void updateStatistics(QImage image);

    /**
      * Changes the language.
      */
    void changeLanguage();

private:
    /**
      * Construct graph window.
      */
    void construct();

    /**
      * Central widget.
      */
    QTabWidget *centralWidget;

    HistogramOpenGLRenderer* renderers[6];
};
#endif // GRAPH_H
