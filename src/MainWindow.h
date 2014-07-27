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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMap>
#include <QString>
#include <QFileDialog>
#include <QTime>
#include <QTabWidget>
#include <QFileInfo>
#include <QImageReader>
#include <QInputDialog>
#include <QHash>
#include <QMetaObject>

#include "Main.h"
#include "Console.h"
#include "Graph.h"
#include "Script.h"
#include "HistogramOpenGLRenderer.h"
#include "ImageOpenGLRenderer.h"
#include "ImageProcessor.h"
#include "OpenGLRenderer.h"
#include "PluginManager.h"

/**
  * \class MainWindow
  * \brief View Class for the main window.
  *
  * This class represents the main window.
  *
  */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    /**
      * Handles the given image as a result.
      */
    void handleImage(QImage image);

    /**
      * Displays the image in a new renderer.
      */
    void displayImage(QImage image, QString title);

    /**
      * Updates the graph window.
      */
    void updateGraphWindow();

    /**
      * Saves the dock widgets window states.
      */
    void saveWindowStates();

private slots:
    /**
      * Shows an open file dialog.
      */
    void openFileDialog();

    /**
      * Shows a save file dialog.
      */
    void saveFileDialog();

    /**
      * Shows a save as file dialog.
      */
    void saveAsFileDialog();

    /**
      * Shows a save history dialog.
      */
    void saveHistoryDialog();

    /**
      * Pushes the current image to the history stack.
      */
    void pushHistory();

    /**
      * Pops the last entry of the history if it is not empty.
      */
    void popHistory();

    /**
      * Adjusts brightness automatically.
      */
    void autoBrightness();

    /**
      * Calculates the red channel.
      */
    void calculateRedChannel();

    /**
      * Calculates the green channel.
      */
    void calculateGreenChannel();

    /**
      * Calculates the blue channel.
      */
    void calculateBlueChannel();

    /**
      * Copies the current image.
      */
    void copyImage();

    /**
      * Performs a gray value splay.
      */
    void grayValueSplay();

    /**
      * Inverts the current image.
      */
    void invertImage();

    /**
      * Performs a single threshold operation.
      */
    void threshold();

    /**
      * Performs an erosion operation.
      */
    void erode();

    /**
      * Removes a certain color.
      */
    void removeColor();

    /**
      * Runs a symmetric differentiation filter.
      */
    void symmetricDifferentiationFilter();

    /**
      * Runs a prewitt filter.
      */
    void prewittFilter();

    /**
      * Runs a sobel filter.
      */
    void sobelFilter();

    /**
      * Runs a LaPlace filter.
      */
    void laPlaceFilter();

    /**
      * Runs a Kirsch compass filter.
      */
    void kirschCompassFilter();

    /**
      * Converts a differentiation image to absolute values.
      */
    void makeAbsolute();

    /**
      * Detects zero corssings.
      */
    void detectZeroCrossings();

    /**
      * Adds another image.
      */
    void addImage();

    /**
      * Subtracts another image.
      */
    void subtractImage();

    /**
      * Multiplicates with another image.
      */
    void multiplicateImage();

    /**
      * Divides by another image.
      */
    void divideImage();

    /**
      * Performs a brightness operation.
      */
    void brightness();

    /**
      * Rotates the current image.
      */
    void rotateImage();

    /**
      * Fills up horizontal gaps.
      */
    void fillUpHorizontalGaps();

    /**
      * Fills up horizontal gaps.
      */
    void fillUpVerticalGaps();

    /**
      * General improvement of the image.
      */
    void lively();

    /**
      * Converts the current image to grayscale.
      */
    void convertToGrayscale();

    /**
      * Converts the current image to a vector image.
      */
    void convertToVectorImage();

    /**
      * Converts the current image to an image with reduced color spectrum.
      */
    void convertToReducedColors();

    /**
      * Displays information about the programm and developers
      */
    void infoAbout();

    /**
      * Loads the specified file.
      */
    void loadFile(QString fileName);

    /**
      * Tries to load the specified file as RAW.
      */
    QImage loadRawFile(QString fileName);

    /**
      * Saves to the specified file.
      */
    void saveFile(QString fileName);

    /**
      * Saves history to the specified file.
      */
    void saveHistory(QString directoryName);

    /**
      * Closes the specified document.
      */
    void closeDocument(int index);

    /**
      * Get open documents in the correct tab order.
      * \return list of open documents.
      */
    QStringList getOpenDocuments();

    /**
      * Asks the user to choose an image.
      * \return index of image.
      */
    int askUserForImage();

    /**
      * Sets the language to English.
      */
    void setLanguageToEnglish();

    /**
      * Sets the language to French.
      */
    void setLanguageToFrench();

    /**
      * Sets the language to German.
      */
    void setLanguageToGerman();

    /**
      * Sets the language to German.
      */
    void setLanguageToPolish();

    /**
      * Sets the language to German.
      */
    void setLanguageToTurkish();

    /**
      * Displays information on how to contribute your language.
      */
    void contributeLanguageInformation();

    /**
      * Changes the language.
      */
    void changeLanguage();

    /**
      * Enables or disables image processing menus.
      */
    void enableOrDisableImageProcessingMenus();

    /**
      * Shows up the plugin manager.
      */
    void showPluginManager();

private:
    /**
      * Constructs the main window.
      */
    void construct();

    /**
      * Console dock widget.
      */
    Console *console;

    /**
      * Graph dock widget.
      */
    Graph *graph;

    /**
      * Script dock widget.
      */
    Script *script;

    /**
      * Central widget for main window.
      */
    QTabWidget *documents;

    /**
      * QString to QMenu*-map for main window.
      */
    QMap<QString, QMenu*> menu;

    /**
      * QString to QAction*-map for main window.
      */
    QMap<QString, QAction*> action;

    /**
      * Image information for the image that is being processed right now.
      */
    struct
    {
        QString description;
        ImageOpenGLRenderer* renderer;
        QTime time;
    } imageInformation;
};

#endif // MAINWINDOW_H
