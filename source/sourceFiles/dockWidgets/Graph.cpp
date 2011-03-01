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

#include "headerFiles/ImageProcessor.h"
#include "headerFiles/Main.h"
#include "headerFiles/dockWidgets/Graph.h"
#include "headerFiles/renderers/HistogramOpenGLRenderer.h"
#include "headerFiles/renderers/OpenGLRenderer.h"

#define RED             0
#define GREEN           1
#define BLUE            2
#define HUE             3
#define SATURATION      4
#define VALUE           5

Graph::Graph(QWidget *parent)
    : QDockWidget(parent)
{
    setWindowTitle(Main::instance()->translate("Graph", "Graph"));
    setObjectName("graph");
    construct();

    connect(Main::instance(), SIGNAL(languageChanged()), this, SLOT(changeLanguage()));
}

Graph::~Graph()
{
}

void Graph::addRenderer(QString description, OpenGLRenderer *renderer)
{
    centralWidget->addTab(renderer, description);
    centralWidget->setCurrentWidget(renderer);
}

void Graph::clearRenderers()
{
    while(centralWidget->count())
        clearRenderer(centralWidget->count()-1);
}

void Graph::clearRenderer(int index)
{
    if(index>centralWidget->count()-1)
        return;

    delete centralWidget->widget(index);
}

void Graph::updateStatistics(QImage image)
{
    const char* methods[] = { "normalizedRedValueDistribution",
                              "normalizedGreenValueDistribution",
                              "normalizedBlueValueDistribution",
                              "normalizedHueDistribution",
                              "normalizedSaturationDistribution",
                              "normalizedValueDistribution" };
    int i;
    for(i=0; i<6; i++)
        renderers[i]->markAsUpdating();

    int active = centralWidget->currentIndex();
    QMetaObject::invokeMethod(ImageProcessor::instance(), methods[active],
                              Qt::QueuedConnection,
                              Q_ARG(QImage, image),
                              Q_ARG(QObject*, renderers[active]));

    for(i=0; i<6; i++)
    {
        if(i != active)
        QMetaObject::invokeMethod(ImageProcessor::instance(), methods[i],
                                  Qt::QueuedConnection,
                                  Q_ARG(QImage, image),
                                  Q_ARG(QObject*, renderers[i]));
    }
}

void Graph::changeLanguage()
{
    setWindowTitle(Main::instance()->translate("Graph", "Graph"));
    centralWidget->setTabText(0, Main::instance()->translate("Graph", "Red"));
    centralWidget->setTabText(1, Main::instance()->translate("Graph", "Green"));
    centralWidget->setTabText(2, Main::instance()->translate("Graph", "Blue"));
    centralWidget->setTabText(3, Main::instance()->translate("Graph", "Hue"));
    centralWidget->setTabText(4, Main::instance()->translate("Graph", "Saturation"));
    centralWidget->setTabText(5, Main::instance()->translate("Graph", "Value"));
}

void Graph::construct()
{
    int i;
    centralWidget=new QTabWidget(this);
    centralWidget->setTabsClosable(false);
    setWidget(centralWidget);

    connect(centralWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(clearRenderer(int)));

    for(i=0; i<6; i++)
        renderers[i] = new HistogramOpenGLRenderer(this);

    renderers[RED]->setPrimaryColor(1.0, 0.0, 0.0);
    renderers[RED]->setSecondaryColor(1.0, 1.0, 1.0);
    renderers[GREEN]->setPrimaryColor(0.0, 1.0, 0.0);
    renderers[GREEN]->setSecondaryColor(1.0, 1.0, 1.0);
    renderers[BLUE]->setPrimaryColor(0.0, 0.0, 1.0);
    renderers[BLUE]->setSecondaryColor(1.0, 1.0, 1.0);
    renderers[HUE]->setPrimaryColor(0.3, 0.4, 0.5);
    renderers[HUE]->setSecondaryColor(1.0, 1.0, 1.0);
    renderers[SATURATION]->setPrimaryColor(0.5, 0.5, 0.5);
    renderers[SATURATION]->setSecondaryColor(1.0, 1.0, 1.0);
    renderers[VALUE]->setPrimaryColor(0.5, 0.4, 0.3);
    renderers[VALUE]->setSecondaryColor(1.0, 1.0, 1.0);

    addRenderer(Main::instance()->translate("MainWindow", "Red"), renderers[RED]);
    addRenderer(Main::instance()->translate("MainWindow", "Green"), renderers[GREEN]);
    addRenderer(Main::instance()->translate("MainWindow", "Blue"), renderers[BLUE]);
    addRenderer(Main::instance()->translate("MainWindow", "Hue"), renderers[HUE]);
    addRenderer(Main::instance()->translate("MainWindow", "Saturation"), renderers[SATURATION]);
    addRenderer(Main::instance()->translate("MainWindow", "Value"), renderers[VALUE]);
    centralWidget->setCurrentIndex(0);
}
