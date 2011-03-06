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

#include "headerFiles/MainWindow.h"
#include "headerFiles/ChainProcessor.h"
#include "headerFiles/PluginManagerDialog.h"
#include <QMessageBox>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("fast-bit");
    setObjectName("mainWindow");
    Main::instance().setMainWindow(this);

    construct();
    changeLanguage();
    showMaximized();
}

MainWindow::~MainWindow()
{
}

void MainWindow::openFileDialog()
{
    QString fileName =
    QFileDialog::getOpenFileName(this,
                                 Main::instance().translate("MainWindow", "Open File"),
                                 "examples/");
    if(fileName.size())
        loadFile(fileName);
}

void MainWindow::saveFileDialog()
{
    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    if(!renderer)
    {
        console->print(Main::instance().translate("MainWindow", "Error: No image available."));
        return;
    }

    QString fileName =
    QFileDialog::getSaveFileName(this,
                                 Main::instance().translate("MainWindow", "Save File"),
                                 "examples/"+renderer->title());
    if(fileName.size())
        saveFile(fileName);
}

void MainWindow::saveAsFileDialog()
{
    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    if(!renderer)
    {
        console->print(Main::instance().translate("MainWindow", "Error: No image available."));
        return;
    }

    QString fileName =
    QFileDialog::getSaveFileName(this,
                                 Main::instance().translate("MainWindow", "Save File"),
                                 "examples/"+renderer->title());
    if(fileName.size())
        saveFile(fileName);
}

void MainWindow::saveHistoryDialog()
{
    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    if(!renderer)
    {
        console->print(Main::instance().translate("MainWindow", "Error: No image available."));
        return;
    }

    QString directoryName =
    QFileDialog::getExistingDirectory(this,
                                 Main::instance().translate("MainWindow", "Save History"),
                                 "examples/"+renderer->title());
    if(directoryName.size())
        saveHistory(directoryName);
}

void MainWindow::pushHistory()
{
    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    if(!renderer)
        return;

    renderer->pushToHistory(renderer->image());
    updateGraphWindow();
}

void MainWindow::popHistory()
{
    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    if(!renderer)
        return;

    renderer->popFromHistory();
    updateGraphWindow();
}

void MainWindow::autoBrightness()
{
    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    if(!renderer)
        return;

    imageInformation.description = Main::instance().translate("MainWindow", "Auto Brightness");
    imageInformation.renderer=renderer;
    imageInformation.time.restart();

    QMetaObject::invokeMethod(ImageProcessor::instance(), "autoBrightness",
                              Qt::QueuedConnection, Q_ARG(QObject*, this),
                              Q_ARG(QImage, renderer->image()));
}

void MainWindow::calculateRedChannel()
{
    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    if(!renderer)
        return;

    imageInformation.description = Main::instance().translate("MainWindow", "Red Channel");
    imageInformation.renderer=renderer;
    imageInformation.time.restart();

    QMetaObject::invokeMethod(ImageProcessor::instance(), "redFilter",
                              Qt::QueuedConnection, Q_ARG(QObject*, this),
                              Q_ARG(QImage, renderer->image()));
}

void MainWindow::calculateGreenChannel()
{
    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    if(!renderer)
        return;

    imageInformation.description = Main::instance().translate("MainWindow", "Green Channel");
    imageInformation.renderer=renderer;
    imageInformation.time.restart();

    QMetaObject::invokeMethod(ImageProcessor::instance(), "greenFilter",
                              Qt::QueuedConnection, Q_ARG(QObject*, this),
                              Q_ARG(QImage, renderer->image()));
}

void MainWindow::calculateBlueChannel()
{
    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    if(!renderer)
        return;

    imageInformation.description = Main::instance().translate("MainWindow", "Blue Channel");
    imageInformation.renderer=renderer;
    imageInformation.time.restart();

    QMetaObject::invokeMethod(ImageProcessor::instance(), "blueFilter",
                              Qt::QueuedConnection, Q_ARG(QObject*, this),
                              Q_ARG(QImage, renderer->image()));
}

void MainWindow::copyImage()
{
    ImageOpenGLRenderer *activeRenderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    if(!activeRenderer)
        return;

    ImageOpenGLRenderer *newRenderer=new ImageOpenGLRenderer(this);
    newRenderer->renderImage(activeRenderer->image());
    newRenderer->setTitle("Copy."+activeRenderer->title());

    newRenderer->setCurrentZoom(activeRenderer->currentZoom());
    newRenderer->setCurrentScrollPosition(activeRenderer->currentScrollPosition());

    documents->addTab(newRenderer, newRenderer->title());
    documents->setCurrentWidget(newRenderer);
}

void MainWindow::grayValueSplay()
{
    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    if(!renderer)
        return;

    imageInformation.description = Main::instance().translate("MainWindow", "Gray Value Splay");
    imageInformation.renderer=renderer;
    imageInformation.time.restart();

    QMetaObject::invokeMethod(ImageProcessor::instance(), "grayValueSplay",
                              Qt::QueuedConnection, Q_ARG(QObject*, this),
                              Q_ARG(QImage, renderer->image()));
}

void MainWindow::invertImage()
{
    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    if(!renderer)
        return;

    imageInformation.description = Main::instance().translate("MainWindow", "Invert Image");
    imageInformation.renderer=renderer;
    imageInformation.time.restart();

    QMetaObject::invokeMethod(ImageProcessor::instance(), "invert",
                              Qt::QueuedConnection, Q_ARG(QObject*, this),
                              Q_ARG(QImage, renderer->image()));
}

void MainWindow::threshold()
{
    bool ok;
    int thr=QInputDialog::getInt(this,
                                 Main::instance().translate("MainWindow", "Threshold"),
                                 Main::instance().translate("MainWindow", "Enter threshold value from 0 to +255:"), 128, 0, 255, 1, &ok);
    if(!ok)
        return;

    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    if(!renderer)
        return;

    imageInformation.description = Main::instance().translate("MainWindow", "Threshold");
    imageInformation.renderer=renderer;
    imageInformation.time.restart();

    QMetaObject::invokeMethod(ImageProcessor::instance(), "threshold",
                              Qt::QueuedConnection, Q_ARG(QObject*, this),
                              Q_ARG(QImage, renderer->image()), Q_ARG(int, thr));
}

void MainWindow::erode()
{
    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    if(!renderer)
        return;

    imageInformation.description = Main::instance().translate("MainWindow", "Erosion");
    imageInformation.renderer=renderer;
    imageInformation.time.restart();

    QMetaObject::invokeMethod(ImageProcessor::instance(), "erode",
                              Qt::QueuedConnection, Q_ARG(QObject*, this),
                              Q_ARG(QImage, renderer->image()));
}

void MainWindow::removeColor()
{
    bool ok;
    int value = QInputDialog::getInt(this,
                                     Main::instance().translate("MainWindow", "Color Value"),
                                     Main::instance().translate("MainWindow", "Choose which color to remove:"), 128, 1, 255, 1, &ok);
    if(!ok)
        return;

    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    if(!renderer)
        return;

    imageInformation.description = Main::instance().translate("MainWindow", "Remove Color");
    imageInformation.renderer=renderer;
    imageInformation.time.restart();

    QMetaObject::invokeMethod(ImageProcessor::instance(), "removeColorByValue",
                              Qt::QueuedConnection, Q_ARG(QObject*, this),
                              Q_ARG(QImage, renderer->image()), Q_ARG(int, value));
}

void MainWindow::symmetricDifferentiationFilter()
{
    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    if(!renderer)
        return;

    imageInformation.description = Main::instance().translate("MainWindow", "Symmetric Differentation Filter");
    imageInformation.renderer=renderer;
    imageInformation.time.restart();

    QMetaObject::invokeMethod(ImageProcessor::instance(), "symmetricDifferentiationFilter",
                              Qt::QueuedConnection, Q_ARG(QObject*, this),
                              Q_ARG(QImage, renderer->image()));
}

void MainWindow::prewittFilter()
{
    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    if(!renderer)
        return;

    imageInformation.description = Main::instance().translate("MainWindow", "Prewitt Filter");
    imageInformation.renderer=renderer;
    imageInformation.time.restart();

    QMetaObject::invokeMethod(ImageProcessor::instance(), "prewittFilter",
                              Qt::QueuedConnection, Q_ARG(QObject*, this),
                              Q_ARG(QImage, renderer->image()));
}

void MainWindow::sobelFilter()
{
    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    if(!renderer)
        return;

    imageInformation.description = Main::instance().translate("MainWindow", "Sobel Filter");
    imageInformation.renderer=renderer;
    imageInformation.time.restart();

    QMetaObject::invokeMethod(ImageProcessor::instance(), "sobelFilter",
                              Qt::QueuedConnection, Q_ARG(QObject*, this),
                              Q_ARG(QImage, renderer->image()));
}

void MainWindow::laPlaceFilter()
{
    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    if(!renderer)
        return;

    imageInformation.description = Main::instance().translate("MainWindow", "LaPlace Filter");
    imageInformation.renderer=renderer;
    imageInformation.time.restart();

    QMetaObject::invokeMethod(ImageProcessor::instance(), "laPlaceFilter",
                              Qt::QueuedConnection, Q_ARG(QObject*, this),
                              Q_ARG(QImage, renderer->image()));
}

void MainWindow::kirschCompassFilter()
{
    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    if(!renderer)
        return;

    imageInformation.description = Main::instance().translate("MainWindow", "Kirsch Compass Filter");
    imageInformation.renderer=renderer;
    imageInformation.time.restart();

    QMetaObject::invokeMethod(ImageProcessor::instance(), "kirschCompassFilter",
                              Qt::QueuedConnection, Q_ARG(QObject*, this),
                              Q_ARG(QImage, renderer->image()));
}

void MainWindow::makeAbsolute()
{
    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    if(!renderer)
        return;

    imageInformation.description = Main::instance().translate("MainWindow", "Make Absolute");
    imageInformation.renderer=renderer;
    imageInformation.time.restart();

    QMetaObject::invokeMethod(ImageProcessor::instance(), "makeAbsolute",
                              Qt::QueuedConnection, Q_ARG(QObject*, this),
                              Q_ARG(QImage, renderer->image()));
}

void MainWindow::detectZeroCrossings()
{
    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    if(!renderer)
        return;

    imageInformation.description = Main::instance().translate("MainWindow", "Detect Zero Crossings");
    imageInformation.renderer=renderer;
    imageInformation.time.restart();

    QMetaObject::invokeMethod(ImageProcessor::instance(), "detectZeroCrossings",
                              Qt::QueuedConnection, Q_ARG(QObject*, this),
                              Q_ARG(QImage, renderer->image()));
}

void MainWindow::addImage()
{
    int index = askUserForImage();
    if(index == -1)
        return;

    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    ImageOpenGLRenderer *secondRenderer=dynamic_cast<ImageOpenGLRenderer*>(documents->widget(index));
    if(!renderer||!secondRenderer)
        return;

    imageInformation.description = Main::instance().translate("MainWindow", "Addition");
    imageInformation.renderer=renderer;
    imageInformation.time.restart();

    QMetaObject::invokeMethod(ImageProcessor::instance(), "add",
                              Qt::QueuedConnection, Q_ARG(QObject*, this),
                              Q_ARG(QImage, renderer->image()),
                              Q_ARG(QImage, secondRenderer->image()));
}

void MainWindow::subtractImage()
{
    int index = askUserForImage();
    if(index == -1)
        return;

    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    ImageOpenGLRenderer *secondRenderer=dynamic_cast<ImageOpenGLRenderer*>(documents->widget(index));
    if(!renderer||!secondRenderer)
        return;

    imageInformation.description = Main::instance().translate("MainWindow", "Subtraction");
    imageInformation.renderer=renderer;
    imageInformation.time.restart();

    QMetaObject::invokeMethod(ImageProcessor::instance(), "subtract",
                              Qt::QueuedConnection, Q_ARG(QObject*, this),
                              Q_ARG(QImage, renderer->image()),
                              Q_ARG(QImage, secondRenderer->image()));
}

void MainWindow::multiplicateImage()
{
    int index = askUserForImage();
    if(index == -1)
        return;

    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    ImageOpenGLRenderer *secondRenderer=dynamic_cast<ImageOpenGLRenderer*>(documents->widget(index));
    if(!renderer||!secondRenderer)
        return;

    imageInformation.description = Main::instance().translate("MainWindow", "Multiplication");
    imageInformation.renderer=renderer;
    imageInformation.time.restart();

    QMetaObject::invokeMethod(ImageProcessor::instance(), "multiplicate",
                              Qt::QueuedConnection, Q_ARG(QObject*, this),
                              Q_ARG(QImage, renderer->image()),
                              Q_ARG(QImage, secondRenderer->image()));
}

void MainWindow::divideImage()
{
    int index = askUserForImage();
    if(index == -1)
        return;

    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    ImageOpenGLRenderer *secondRenderer=dynamic_cast<ImageOpenGLRenderer*>(documents->widget(index));
    if(!renderer||!secondRenderer)
        return;

    imageInformation.description = Main::instance().translate("MainWindow", "Division");
    imageInformation.renderer=renderer;
    imageInformation.time.restart();

    QMetaObject::invokeMethod(ImageProcessor::instance(), "divide",
                              Qt::QueuedConnection, Q_ARG(QObject*, this),
                              Q_ARG(QImage, renderer->image()),
                              Q_ARG(QImage, secondRenderer->image()));
}

void MainWindow::brightness()
{
    bool ok;
    int bgt=QInputDialog::getInt(this,
                                 Main::instance().translate("MainWindow", "Brightness"),
                                 Main::instance().translate("MainWindow", "Enter brightness value from -255 to +255:"),
                                 32, -255, 255, 1, &ok);
    if(!ok)
        return;

    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    if(!renderer)
        return;

    imageInformation.description = Main::instance().translate("MainWindow", "Brightness");
    imageInformation.renderer=renderer;
    imageInformation.time.restart();

    QMetaObject::invokeMethod(ImageProcessor::instance(), "brightness",
                              Qt::QueuedConnection, Q_ARG(QObject*, this),
                              Q_ARG(QImage, renderer->image()),
                              Q_ARG(int, bgt));
}

void MainWindow::rotateImage()
{
    bool ok;
    int angle=
    QInputDialog::getInt(this,
                         Main::instance().translate("MainWindow", "Angle"),
                         Main::instance().translate("MainWindow", "Enter a rotation angle from -360 to +360 degrees:"),
                         0, -360, 360, 1, &ok);
    if(!ok)
        return;

    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    if(!renderer)
        return;

    imageInformation.description = Main::instance().translate("MainWindow", "Rotation");
    imageInformation.renderer=renderer;
    imageInformation.time.restart();

    QMetaObject::invokeMethod(ImageProcessor::instance(), "rotate",
                              Qt::QueuedConnection, Q_ARG(QObject*, this),
                              Q_ARG(QImage, renderer->image()),
                              Q_ARG(double, (double)angle));
}

void MainWindow::fillUpHorizontalGaps()
{
    bool ok;
    int totalLoops = QInputDialog::getInt(this,
                                          Main::instance().translate("MainWindow", "Strength"),
                                          Main::instance().translate("MainWindow", "Enter loop runs:"),
                                          1, 1, 32768, 1, &ok);
    if(!ok)
        return;

    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    if(!renderer)
        return;

    imageInformation.description = QString(Main::instance().translate("MainWindow", "Fill Up Horizontal Gaps (%1x)")).arg(totalLoops);
    imageInformation.renderer=renderer;
    imageInformation.time.restart();

    QMetaObject::invokeMethod(ImageProcessor::instance(), "fillUpHorizontalGaps",
                              Qt::QueuedConnection, Q_ARG(QObject*, this),
                              Q_ARG(QImage, renderer->image()),
                              Q_ARG(int, totalLoops));
}

void MainWindow::fillUpVerticalGaps()
{
    bool ok;
    int totalLoops = QInputDialog::getInt(this,
                                          Main::instance().translate("MainWindow", "Strength"),
                                          Main::instance().translate("MainWindow", "Enter loop runs:"),
                                          1, 1, 32768, 1, &ok);
    if(!ok)
        return;

    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    if(!renderer)
        return;

    imageInformation.description = QString(Main::instance().translate("MainWindow", "Fill Up Vertical Gaps (%1x)")).arg(totalLoops);
    imageInformation.renderer=renderer;
    imageInformation.time.restart();

    QMetaObject::invokeMethod(ImageProcessor::instance(), "fillUpVerticalGaps",
                              Qt::QueuedConnection, Q_ARG(QObject*, this),
                              Q_ARG(QImage, renderer->image()),
                              Q_ARG(int, totalLoops));
}

void MainWindow::lively()
{
    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    if(!renderer)
        return;

    imageInformation.description = Main::instance().translate("MainWindow", "Lively");
    imageInformation.renderer=renderer;
    imageInformation.time.restart();

    ChainProcessor* chainProcessor = new ChainProcessor(this);
    chainProcessor->addTask("autoBrightness");
    chainProcessor->addTask("grayValueSplay");

    connect(chainProcessor, SIGNAL(status(QString)), console, SLOT(print(QString)));

    QMetaObject::invokeMethod(chainProcessor, "handleImage",
                              Qt::QueuedConnection, Q_ARG(QImage, renderer->image()));
}

void MainWindow::convertToGrayscale()
{
    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    if(!renderer)
        return;

    imageInformation.description = Main::instance().translate("MainWindow", "Grayscale");
    imageInformation.renderer=renderer;
    imageInformation.time.restart();

    QMetaObject::invokeMethod(ImageProcessor::instance(), "convertToGray",
                              Qt::QueuedConnection, Q_ARG(QObject*, this),
                              Q_ARG(QImage, renderer->image()));
}

void MainWindow::convertToVectorImage()
{
    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    if(!renderer)
        return;

    imageInformation.description = Main::instance().translate("MainWindow", "Convert to Vector Image");
    imageInformation.renderer=renderer;
    imageInformation.time.restart();

    ChainProcessor* chainProcessor = new ChainProcessor(this);
    chainProcessor->addTask("convertToGray");
    chainProcessor->addTask("detectZeroCrossings");

    connect(chainProcessor, SIGNAL(status(QString)), console, SLOT(print(QString)));

    QMetaObject::invokeMethod(chainProcessor, "handleImage",
                              Qt::QueuedConnection, Q_ARG(QImage, renderer->image()));
}

void MainWindow::convertToReducedColors()
{
    bool ok;
    int stepping = QInputDialog::getInt(this,
                                        Main::instance().translate("MainWindow", "Color stepping"),
                                        Main::instance().translate("MainWindow", "Enter color stepping:"),
                                        16, 1, 255, 1, &ok);
    if(!ok)
        return;

    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    if(!renderer)
        return;

    imageInformation.description = Main::instance().translate("MainWindow", "Reduced Colors");
    imageInformation.renderer=renderer;
    imageInformation.time.restart();

    QMetaObject::invokeMethod(ImageProcessor::instance(), "reduceColors",
                              Qt::QueuedConnection, Q_ARG(QObject*, this),
                              Q_ARG(QImage, renderer->image()),
                              Q_ARG(int, stepping));
}

void MainWindow::infoAbout()
{
    QMessageBox::information(this,
                             Main::instance().translate("MainWindow", "About"),
                             Main::instance().translate("MainWindow", "This is fast-bit in alpha stage. \nDevelopers:\nJacob Dawid\nHamza Üstün"));
}

void MainWindow::saveFile(QString fileName)
{
    console->print(Main::instance().translate("MainWindow", "Saving file: ")+fileName+".");
    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    renderer->image().save(fileName);
}

void MainWindow::saveHistory(QString directoryName)
{
    console->print(Main::instance().translate("MainWindow", "Saving history:"));
    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());
    QStack<QImage> history = renderer->history();
    QString baseName = renderer->title();

    int iter;
    for(iter=0;iter<history.size();iter++)
    {
        QFileInfo fileInfo(directoryName);

        QString compositeFileName = QString("%1%2_%3")
                                    .arg(fileInfo.absolutePath()+"/")
                                    .arg(iter)
                                    .arg(baseName);

        console->print("-> "+ compositeFileName);
        history[iter].save(compositeFileName);
    }
}

void MainWindow::loadFile(QString fileName)
{
    console->print(Main::instance().translate("MainWindow", "Loading file: ")+fileName+".");

    ImageOpenGLRenderer *newRenderer=new ImageOpenGLRenderer(this);
    QImage image(fileName);

    if(image.isNull())
    {
        image = loadRawFile(fileName);
        if(image.isNull())
        {
            QMessageBox::warning(this,
                                 Main::instance().translate("MainWindow", "Error"),
                                 Main::instance().translate("MainWindow", "The requested file could not be opened."));
            return;
        }
    }

    newRenderer->renderImage(image);

    QFileInfo fileInfo(fileName);
    QString tabTitle = fileInfo.fileName();

    documents->addTab(newRenderer, tabTitle);
    documents->setCurrentWidget(newRenderer);
    newRenderer->setTitle(fileInfo.fileName());
    enableOrDisableImageProcessingMenus();
}

QImage MainWindow::loadRawFile(QString fileName)
{
    // TODO: Test code
    /*
    LibRaw libRaw;
    libRaw.open_file(fileName.toStdString().c_str());
    libRaw.unpack();
    unsigned short width = libRaw.imgdata.sizes.iwidth,
                   height = libRaw.imgdata.sizes.iheight;

    QImage image(width, height, QImage::Format_RGB888);

    for(int i = 0; i < width * height; i++)
    {
        image.setPixel(i%width, i/width,
        qRgb(
        libRaw.imgdata.image[i][0],
        libRaw.imgdata.image[i][1],
        libRaw.imgdata.image[i][2] ));
    }

    libRaw.recycle();
    return image;
    */
    return QImage();
}

void MainWindow::closeDocument(int index)
{
    delete documents->widget(index);
    enableOrDisableImageProcessingMenus();
}

QStringList MainWindow::getOpenDocuments()
{
    QStringList list;
    int num = 0;
    int documentCount = documents->count();
    while(num < documentCount)
    {
        list.append(dynamic_cast<ImageOpenGLRenderer*>(documents->widget(num))->title());
        num++;
    }
    return list;
}

int MainWindow::askUserForImage()
{
    bool ok;
    int index;
    QStringList openDocuments = getOpenDocuments();
    for(index=0;index<openDocuments.size();index++)
        openDocuments[index]=QString("%1: %2").arg(index).arg(openDocuments[index]);

    QString imageName = QInputDialog::getItem(this,
                          Main::instance().translate("MainWindow", "Choose image"),
                          Main::instance().translate("MainWindow", "Choose image to perform the operation with:"),
                          openDocuments, 0, false, &ok);

    if(ok&&openDocuments.contains(imageName))
    {
        for(index=0;index<openDocuments.size();index++)
            if(openDocuments[index]==imageName)
                return index;
    }
    return -1;
}

void MainWindow::setLanguageToEnglish()
{
    Main::instance().setLanguage("english");
}

void MainWindow::setLanguageToFrench()
{
    Main::instance().setLanguage("french");
}

void MainWindow::setLanguageToGerman()
{
    Main::instance().setLanguage("german");
}

void MainWindow::setLanguageToPolish()
{
    Main::instance().setLanguage("polish");
}

void MainWindow::setLanguageToTurkish()
{
    Main::instance().setLanguage("turkish");
}

void MainWindow::contributeLanguageInformation()
{
    QMessageBox::information(this, "Contribute Language",
                             "Adding another language to this program has been made very simple"
                             " by using the QtLinguist translation tool. If you consider contributing"
                             " in your language, feel free to drop a mail at:\n\n"
                             " jacob.dawid@googlemail.com\n\n"
                             " Thank you!");
}

void MainWindow::enableOrDisableImageProcessingMenus()
{
    if(documents->count()==0)
    {
        menu["History"]->setEnabled(false);
        menu["General"]->setEnabled(false);
        menu["Improvement"]->setEnabled(false);
        menu["Arithmetic"]->setEnabled(false);
        menu["Convert"]->setEnabled(false);
        menu["Find Edges"]->setEnabled(false);
    }
    else if(documents->count() > 0)
    {
        menu["History"]->setEnabled(true);
        menu["General"]->setEnabled(true);
        menu["Improvement"]->setEnabled(true);
        menu["Arithmetic"]->setEnabled(true);
        menu["Convert"]->setEnabled(true);
        menu["Find Edges"]->setEnabled(true);
    }
}

void MainWindow::showPluginManager()
{
    PluginManagerDialog pluginManagerDialog;
    pluginManagerDialog.exec();
    return;
}

void MainWindow::changeLanguage()
{
    menu["File"]->setTitle(Main::instance().translate("MainWindow", "File"));
    action["Open"]->setText(Main::instance().translate("MainWindow", "Open"));
    action["Save"]->setText(Main::instance().translate("MainWindow", "Save"));
    action["Save As"]->setText(Main::instance().translate("MainWindow", "Save As"));
    action["Save History"]->setText(Main::instance().translate("MainWindow", "Save History"));

    menu["History"]->setTitle(Main::instance().translate("MainWindow", "History"));
    action["Push"]->setText(Main::instance().translate("MainWindow", "Push"));
    action["Pop"]->setText(Main::instance().translate("MainWindow", "Pop"));

    menu["General"]->setTitle(Main::instance().translate("MainWindow", "General"));
    action["Red Channel"]->setText(Main::instance().translate("MainWindow", "Red Channel"));
    action["Green Channel"]->setText(Main::instance().translate("MainWindow", "Green Channel"));
    action["Blue Channel"]->setText(Main::instance().translate("MainWindow", "Blue Channel"));
    action["Copy Image"]->setText(Main::instance().translate("MainWindow", "Copy Image"));
    action["Invert Image"]->setText(Main::instance().translate("MainWindow", "Invert Image"));
    action["Threshold"]->setText(Main::instance().translate("MainWindow", "Threshold"));
    action["Erosion"]->setText(Main::instance().translate("MainWindow", "Erosion"));
    action["Rotate Image"]->setText(Main::instance().translate("MainWindow", "Rotate Image"));
    action["Remove Color"]->setText(Main::instance().translate("MainWindow", "Remove Color"));

    menu["Improvement"]->setTitle(Main::instance().translate("MainWindow", "Improvement"));
    action["Brightness"]->setText(Main::instance().translate("MainWindow", "Brightness"));
    action["Auto Brightness"]->setText(Main::instance().translate("MainWindow", "Auto Brightness"));
    action["Gray Value Splay"]->setText(Main::instance().translate("MainWindow", "Gray Value Splay"));
    action["Fill Up Horizontal Gaps"]->setText(Main::instance().translate("MainWindow", "Fill Up Horizontal Gaps"));
    action["Fill Up Vertical Gaps"]->setText(Main::instance().translate("MainWindow", "Fill Up Vertical Gaps"));
    action["Lively"]->setText(Main::instance().translate("MainWindow", "Lively"));

    menu["Arithmetic"]->setTitle(Main::instance().translate("MainWindow", "Arithmetic"));
    action["Add Image"]->setText(Main::instance().translate("MainWindow", "Add Image"));
    action["Subtract Image"]->setText(Main::instance().translate("MainWindow", "Subtract Image"));
    action["Multiplicate Image"]->setText(Main::instance().translate("MainWindow", "Multiplicate Image"));
    action["Divide Image"]->setText(Main::instance().translate("MainWindow", "Divide Image"));

    menu["Find Edges"]->setTitle(Main::instance().translate("MainWindow", "Find Edges"));
    action["Symmetric Differentiation Filter"]->setText(Main::instance().translate("MainWindow", "Symmetric Differentiation"));
    action["Prewitt Filter"]->setText(Main::instance().translate("MainWindow", "Prewitt"));
    action["Sobel Filter"]->setText(Main::instance().translate("MainWindow", "Sobel"));
    action["LaPlace Filter"]->setText(Main::instance().translate("MainWindow", "LaPlace"));
    action["Kirsch Compass Filter"]->setText(Main::instance().translate("MainWindow", "Kirsch (Compass)"));
    action["Make Absolute"]->setText(Main::instance().translate("MainWindow", "Make Absolute"));
    action["Detect Zero Crossings"]->setText(Main::instance().translate("MainWindow", "Detect Zero Crossings"));

    menu["Convert"]->setTitle(Main::instance().translate("MainWindow", "Convert"));
    action["to Grayscale"]->setText(Main::instance().translate("MainWindow", "to Grayscale"));
    action["to Reduced Colors"]->setText(Main::instance().translate("MainWindow", "to Reduced Colors"));
    action["to Vector Image"]->setText(Main::instance().translate("MainWindow", "to Vector Image"));

    menu["Plugins"]->setTitle(Main::instance().translate("MainWindow", "Plugins"));
    action["Manage Plugins"]->setText(Main::instance().translate("MainWindow", "Manage Plugins"));

    menu["Info"]->setTitle(Main::instance().translate("MainWindow", "Info"));
    action["About"]->setText(Main::instance().translate("MainWindow", "About"));

    menu["Language"]->setTitle(Main::instance().translate("MainWindow", "Language"));
    action["English"]->setText(Main::instance().translate("MainWindow", "English"));
    action["French"]->setText(Main::instance().translate("MainWindow", "French"));
    action["German"]->setText(Main::instance().translate("MainWindow", "German"));
}

void MainWindow::handleImage(QImage image)
{
    imageInformation.renderer->renderImage(image);
    console->print(QString(Main::instance().translate("MainWindow", "Performed \'%1\' in %2 ms")).arg(imageInformation.description).arg(imageInformation.time.elapsed()));
    enableOrDisableImageProcessingMenus();
    updateGraphWindow();
}

void MainWindow::displayImage(QImage image, QString title)
{
    ImageOpenGLRenderer *newRenderer=new ImageOpenGLRenderer(this);
    newRenderer->renderImage(image);
    documents->addTab(newRenderer, title);
    documents->setCurrentWidget(newRenderer);
    enableOrDisableImageProcessingMenus();
}

void MainWindow::construct()
{
    menu["File"]=menuBar()->addMenu(Main::instance().translate("MainWindow", "File"));
    action["Open"]=menu["File"]->addAction(Main::instance().translate("MainWindow", "Open"));
    action["Save"]=menu["File"]->addAction(Main::instance().translate("MainWindow", "Save"));
    action["Save As"]=menu["File"]->addAction(Main::instance().translate("MainWindow", "Save As"));
    action["Save History"]=menu["File"]->addAction(Main::instance().translate("MainWindow", "Save History"));

    menu["History"]=menuBar()->addMenu(Main::instance().translate("MainWindow", "History"));
    action["Push"]=menu["History"]->addAction(Main::instance().translate("MainWindow", "Push"));
    action["Push"]->setIcon(QIcon("media/icons/126293-simple-black-square-icon-alphanumeric-plus-sign-simple.png"));
    action["Pop"]=menu["History"]->addAction(Main::instance().translate("MainWindow", "Pop"));
    action["Pop"]->setIcon(QIcon("media/icons/126265-simple-black-square-icon-alphanumeric-minus-sign-simple.png"));
    menu["History"]->setEnabled(false);

    menu["General"]=menuBar()->addMenu(Main::instance().translate("MainWindow", "General"));
    action["Red Channel"]=menu["General"]->addAction(Main::instance().translate("MainWindow", "Red Channel"));
    action["Red Channel"]->setIcon(QIcon("media/icons/126172-simple-black-square-icon-alphanumeric-bracket-curley.png"));
    action["Green Channel"]=menu["General"]->addAction(Main::instance().translate("MainWindow", "Green Channel"));
    action["Green Channel"]->setIcon(QIcon("media/icons/126172-simple-black-square-icon-alphanumeric-bracket-curley.png"));
    action["Blue Channel"]=menu["General"]->addAction(Main::instance().translate("MainWindow", "Blue Channel"));
    action["Blue Channel"]->setIcon(QIcon("media/icons/126172-simple-black-square-icon-alphanumeric-bracket-curley.png"));
    menu["General"]->addSeparator();
    action["Copy Image"]=menu["General"]->addAction(Main::instance().translate("MainWindow", "Copy Image"));
    action["Copy Image"]->setIcon(QIcon("media/icons/126172-simple-black-square-icon-alphanumeric-bracket-curley.png"));
    action["Invert Image"]=menu["General"]->addAction(Main::instance().translate("MainWindow", "Invert Image"));
    action["Invert Image"]->setIcon(QIcon("media/icons/126172-simple-black-square-icon-alphanumeric-bracket-curley.png"));
    action["Threshold"]=menu["General"]->addAction(Main::instance().translate("MainWindow", "Threshold"));
    action["Threshold"]->setIcon(QIcon("media/icons/126172-simple-black-square-icon-alphanumeric-bracket-curley.png"));
    action["Erosion"]=menu["General"]->addAction(Main::instance().translate("MainWindow", "Erosion"));
    action["Erosion"]->setIcon(QIcon("media/icons/126172-simple-black-square-icon-alphanumeric-bracket-curley.png"));
    menu["General"]->addSeparator();
    action["Rotate Image"]=menu["General"]->addAction(Main::instance().translate("MainWindow", "Rotate Image"));
    action["Rotate Image"]->setIcon(QIcon("media/icons/126172-simple-black-square-icon-alphanumeric-bracket-curley.png"));
    action["Remove Color"]=menu["General"]->addAction(Main::instance().translate("MainWindow", "Remove Color"));
    action["Remove Color"]->setIcon(QIcon("media/icons/126172-simple-black-square-icon-alphanumeric-bracket-curley.png"));
    menu["General"]->setEnabled(false);

    menu["Improvement"]=menuBar()->addMenu(Main::instance().translate("MainWindow", "Improvement"));
    action["Brightness"]=menu["Improvement"]->addAction(Main::instance().translate("MainWindow", "Brightness"));
    action["Brightness"]->setIcon(QIcon("media/icons/126172-simple-black-square-icon-alphanumeric-bracket-curley.png"));
    action["Auto Brightness"]=menu["Improvement"]->addAction(Main::instance().translate("MainWindow", "Auto Brightness"));
    action["Auto Brightness"]->setIcon(QIcon("media/icons/126172-simple-black-square-icon-alphanumeric-bracket-curley.png"));
    action["Gray Value Splay"]=menu["Improvement"]->addAction(Main::instance().translate("MainWindow", "Gray Value Splay"));
    action["Gray Value Splay"]->setIcon(QIcon("media/icons/126172-simple-black-square-icon-alphanumeric-bracket-curley.png"));
    action["Fill Up Horizontal Gaps"]=menu["Improvement"]->addAction(Main::instance().translate("MainWindow", "Fill Up Horizontal Gaps"));
    action["Fill Up Horizontal Gaps"]->setIcon(QIcon("media/icons/126172-simple-black-square-icon-alphanumeric-bracket-curley.png"));
    action["Fill Up Vertical Gaps"]=menu["Improvement"]->addAction(Main::instance().translate("MainWindow", "Fill Up Vertical Gaps"));
    action["Fill Up Vertical Gaps"]->setIcon(QIcon("media/icons/126172-simple-black-square-icon-alphanumeric-bracket-curley.png"));
    menu["Improvement"]->addSeparator();
    action["Lively"]=menu["Improvement"]->addAction(Main::instance().translate("MainWindow", "Lively"));
    action["Lively"]->setIcon(QIcon("media/icons/126172-simple-black-square-icon-alphanumeric-bracket-curley.png"));
    menu["Improvement"]->setEnabled(false);

    menu["Arithmetic"]=menuBar()->addMenu(Main::instance().translate("MainWindow", "Arithmetic"));
    action["Add Image"]=menu["Arithmetic"]->addAction(Main::instance().translate("MainWindow", "Add Image"));
    action["Add Image"]->setIcon(QIcon("media/icons/126172-simple-black-square-icon-alphanumeric-bracket-curley.png"));
    action["Subtract Image"]=menu["Arithmetic"]->addAction(Main::instance().translate("MainWindow", "Subtract Image"));
    action["Subtract Image"]->setIcon(QIcon("media/icons/126172-simple-black-square-icon-alphanumeric-bracket-curley.png"));
    action["Multiplicate Image"]=menu["Arithmetic"]->addAction(Main::instance().translate("MainWindow", "Multiplicate Image"));
    action["Multiplicate Image"]->setIcon(QIcon("media/icons/126172-simple-black-square-icon-alphanumeric-bracket-curley.png"));
    action["Divide Image"]=menu["Arithmetic"]->addAction(Main::instance().translate("MainWindow", "Divide Image"));
    action["Divide Image"]->setIcon(QIcon("media/icons/126172-simple-black-square-icon-alphanumeric-bracket-curley.png"));
    menu["Arithmetic"]->setEnabled(false);

    menu["Find Edges"]=menuBar()->addMenu(Main::instance().translate("MainWindow", "Find Edges"));
    action["Symmetric Differentiation Filter"]=menu["Find Edges"]->addAction(Main::instance().translate("MainWindow", "Symmetric Differentiation"));
    action["Symmetric Differentiation Filter"]->setIcon(QIcon("media/icons/126172-simple-black-square-icon-alphanumeric-bracket-curley.png"));
    action["Prewitt Filter"]=menu["Find Edges"]->addAction(Main::instance().translate("MainWindow", "Prewitt"));
    action["Prewitt Filter"]->setIcon(QIcon("media/icons/126172-simple-black-square-icon-alphanumeric-bracket-curley.png"));
    action["Sobel Filter"]=menu["Find Edges"]->addAction(Main::instance().translate("MainWindow", "Sobel"));
    action["Sobel Filter"]->setIcon(QIcon("media/icons/126172-simple-black-square-icon-alphanumeric-bracket-curley.png"));
    action["LaPlace Filter"]=menu["Find Edges"]->addAction(Main::instance().translate("MainWindow", "LaPlace"));
    action["LaPlace Filter"]->setIcon(QIcon("media/icons/126172-simple-black-square-icon-alphanumeric-bracket-curley.png"));
    action["Kirsch Compass Filter"]=menu["Find Edges"]->addAction(Main::instance().translate("MainWindow", "Kirsch (Compass)"));
    action["Kirsch Compass Filter"]->setIcon(QIcon("media/icons/126172-simple-black-square-icon-alphanumeric-bracket-curley.png"));
    menu["Find Edges"]->addSeparator();
    action["Make Absolute"]=menu["Find Edges"]->addAction(Main::instance().translate("MainWindow", "Make Absolute"));
    action["Make Absolute"]->setIcon(QIcon("media/icons/126172-simple-black-square-icon-alphanumeric-bracket-curley.png"));
    action["Detect Zero Crossings"]=menu["Find Edges"]->addAction(Main::instance().translate("MainWindow", "Detect Zero Crossings"));
    action["Detect Zero Crossings"]->setIcon(QIcon("media/icons/126172-simple-black-square-icon-alphanumeric-bracket-curley.png"));
    menu["Find Edges"]->setEnabled(false);

    menu["Convert"]=menuBar()->addMenu(Main::instance().translate("MainWindow", "Convert"));
    action["to Grayscale"]=menu["Convert"]->addAction(Main::instance().translate("MainWindow", "to Grayscale"));
    action["to Grayscale"]->setIcon(QIcon("media/icons/126172-simple-black-square-icon-alphanumeric-bracket-curley.png"));
    action["to Reduced Colors"]=menu["Convert"]->addAction(Main::instance().translate("MainWindow", "to Reduced Colors"));
    action["to Reduced Colors"]->setIcon(QIcon("media/icons/126172-simple-black-square-icon-alphanumeric-bracket-curley.png"));
    action["to Vector Image"]=menu["Convert"]->addAction(Main::instance().translate("MainWindow", "to Vector Image"));
    action["to Vector Image"]->setIcon(QIcon("media/icons/126172-simple-black-square-icon-alphanumeric-bracket-curley.png"));
    menu["Convert"]->setEnabled(false);

    menu["Plugins"]=menuBar()->addMenu(Main::instance().translate("MainWindow", "Plugins"));
    action["Manage Plugins"]=menu["Plugins"]->addAction(Main::instance().translate("MainWindow", "Manage Plugins"));
    menu["Plugins"]->addSeparator();

    menu["Language"]=menuBar()->addMenu(Main::instance().translate("MainWindow", "Language"));
    action["English"]=menu["Language"]->addAction(Main::instance().translate("MainWindow", "English"));
    action["English"]->setIcon(QIcon("media/icons/126304-simple-black-square-icon-alphanumeric-quote-open2.png"));
    action["French"]=menu["Language"]->addAction(Main::instance().translate("MainWindow", "French"));
    action["French"]->setIcon(QIcon("media/icons/126304-simple-black-square-icon-alphanumeric-quote-open2.png"));
    action["German"]=menu["Language"]->addAction(Main::instance().translate("MainWindow", "German"));
    action["German"]->setIcon(QIcon("media/icons/126304-simple-black-square-icon-alphanumeric-quote-open2.png"));
    action["Polish"]=menu["Language"]->addAction(Main::instance().translate("MainWindow", "Polish"));
    action["Polish"]->setIcon(QIcon("media/icons/126304-simple-black-square-icon-alphanumeric-quote-open2.png"));
    action["Turkish"]=menu["Language"]->addAction(Main::instance().translate("MainWindow", "Turkish"));
    action["Turkish"]->setIcon(QIcon("media/icons/126304-simple-black-square-icon-alphanumeric-quote-open2.png"));
    menu["Language"]->addSeparator();
    action["Contribute Language"]=menu["Language"]->addAction(Main::instance().translate("MainWindow", "Contribute"));
    action["Contribute Language"]->setIcon(QIcon("media/icons/126293-simple-black-square-icon-alphanumeric-plus-sign-simple.png"));

    menu["Info"]=menuBar()->addMenu(Main::instance().translate("MainWindow", "Info"));
    action["About"]=menu["Info"]->addAction(Main::instance().translate("MainWindow", "About"));
    action["About"]->setIcon(QIcon("media/icons/126198-simple-black-square-icon-alphanumeric-information2-ps.png"));

    console=new Console(this);
    graph=new Graph(this);
    script=new Script(this);

    documents=new QTabWidget(this);
    documents->setTabsClosable(true);
    setCentralWidget(documents);

    connect(documents, SIGNAL(tabCloseRequested(int)), this, SLOT(closeDocument(int)));

    connect(action["Open"], SIGNAL(triggered()), this, SLOT(openFileDialog()));
    connect(action["Save"], SIGNAL(triggered()), this, SLOT(saveFileDialog()));
    connect(action["Save As"], SIGNAL(triggered()), this, SLOT(saveAsFileDialog()));
    connect(action["Save History"], SIGNAL(triggered()), this, SLOT(saveHistoryDialog()));

    connect(action["Push"], SIGNAL(triggered()), this, SLOT(pushHistory()));
    connect(action["Pop"], SIGNAL(triggered()), this, SLOT(popHistory()));

    connect(action["Red Channel"], SIGNAL(triggered()), this, SLOT(calculateRedChannel()));
    connect(action["Green Channel"], SIGNAL(triggered()), this, SLOT(calculateGreenChannel()));
    connect(action["Blue Channel"], SIGNAL(triggered()), this, SLOT(calculateBlueChannel()));

    connect(action["Copy Image"], SIGNAL(triggered()), this, SLOT(copyImage()));
    connect(action["Invert Image"], SIGNAL(triggered()), this, SLOT(invertImage()));
    connect(action["Threshold"], SIGNAL(triggered()), this, SLOT(threshold()));
    connect(action["Erosion"], SIGNAL(triggered()), this, SLOT(erode()));
    connect(action["Rotate Image"], SIGNAL(triggered()), this, SLOT(rotateImage()));
    connect(action["Remove Color"], SIGNAL(triggered()), this, SLOT(removeColor()));

    connect(action["Brightness"], SIGNAL(triggered()), this, SLOT(brightness()));
    connect(action["Auto Brightness"], SIGNAL(triggered()), this, SLOT(autoBrightness()));
    connect(action["Gray Value Splay"], SIGNAL(triggered()), this, SLOT(grayValueSplay()));
    connect(action["Fill Up Horizontal Gaps"], SIGNAL(triggered()), this, SLOT(fillUpHorizontalGaps()));
    connect(action["Fill Up Vertical Gaps"], SIGNAL(triggered()), this, SLOT(fillUpVerticalGaps()));
    connect(action["Lively"], SIGNAL(triggered()), this, SLOT(lively()));

    connect(action["Add Image"], SIGNAL(triggered()), this, SLOT(addImage()));
    connect(action["Subtract Image"], SIGNAL(triggered()), this, SLOT(subtractImage()));
    connect(action["Multiplicate Image"], SIGNAL(triggered()), this, SLOT(multiplicateImage()));
    connect(action["Divide Image"], SIGNAL(triggered()), this, SLOT(divideImage()));

    connect(action["Symmetric Differentiation Filter"], SIGNAL(triggered()), this, SLOT(symmetricDifferentiationFilter()));
    connect(action["Prewitt Filter"], SIGNAL(triggered()), this, SLOT(prewittFilter()));
    connect(action["Sobel Filter"], SIGNAL(triggered()), this, SLOT(sobelFilter()));
    connect(action["LaPlace Filter"], SIGNAL(triggered()), this, SLOT(laPlaceFilter()));
    connect(action["Kirsch Compass Filter"], SIGNAL(triggered()), this, SLOT(kirschCompassFilter()));
    connect(action["Make Absolute"], SIGNAL(triggered()), this, SLOT(makeAbsolute()));
    connect(action["Detect Zero Crossings"], SIGNAL(triggered()), this, SLOT(detectZeroCrossings()));

    connect(action["to Grayscale"], SIGNAL(triggered()), this, SLOT(convertToGrayscale()));
    connect(action["to Vector Image"], SIGNAL(triggered()), this, SLOT(convertToVectorImage()));
    connect(action["to Reduced Colors"], SIGNAL(triggered()), this, SLOT(convertToReducedColors()));

    connect(action["Manage Plugins"], SIGNAL(triggered()), this, SLOT(showPluginManager()));

    connect(action["About"], SIGNAL(triggered()), this, SLOT(infoAbout()));

    connect(action["English"], SIGNAL(triggered()), this, SLOT(setLanguageToEnglish()));
    connect(action["French"], SIGNAL(triggered()), this, SLOT(setLanguageToFrench()));
    connect(action["German"], SIGNAL(triggered()), this, SLOT(setLanguageToGerman()));
    connect(action["Polish"], SIGNAL(triggered()), this, SLOT(setLanguageToPolish()));
    connect(action["Turkish"], SIGNAL(triggered()), this, SLOT(setLanguageToTurkish()));
    connect(action["Contribute Language"], SIGNAL(triggered()), this, SLOT(contributeLanguageInformation()));
    connect(&Main::instance(), SIGNAL(languageChanged()), this, SLOT(changeLanguage()));
    connect(ImageProcessor::instance(), SIGNAL(status(QString)), console, SLOT(print(QString)));
    connect(script->scriptingInterface(), SIGNAL(output(QString)), console, SLOT(print(QString)));

    QList<QByteArray> supportedFormats=QImageReader::supportedImageFormats();
    QString supportedFormatsString=Main::instance().translate("MainWindow", "Supported formats on this system: ");
    foreach(QByteArray byteArray, supportedFormats)
        supportedFormatsString+=QString(" ")+byteArray;
    console->print(supportedFormatsString);

    connect(documents, SIGNAL(currentChanged(int)), this, SLOT(updateGraphWindow()));

    addDockWidget(Qt::BottomDockWidgetArea, console);
    addDockWidget(Qt::RightDockWidgetArea, graph);
    addDockWidget(Qt::RightDockWidgetArea, script);
}

void MainWindow::updateGraphWindow()
{
    ImageOpenGLRenderer *renderer=dynamic_cast<ImageOpenGLRenderer*>(documents->currentWidget());

    if(!renderer)
        graph->updateStatistics(QImage());
    else
        graph->updateStatistics(renderer->image());
}

void MainWindow::saveWindowStates()
{
    script->saveWindowState();
}
