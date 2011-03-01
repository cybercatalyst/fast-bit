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
#include "headerFiles/ChainProcessor.h"
#include <QImage>

ChainProcessor::ChainProcessor(QObject *_sender)
    : QObject(),
    sender(_sender)
{
    processingThread = new QThread();
    processingThread->start();
    moveToThread(processingThread);
}

ChainProcessor::~ChainProcessor()
{
    emit status(Main::instance()->translate("ChainProcessor", "Deleting chain processing adapter."));
    processingThread->quit();
    //delete processingThread;
}

void ChainProcessor::addTask(QString _methodName, QList<QGenericArgument> _arguments)
{
    Task task;
    task.methodName = _methodName;
    task.arguments = _arguments;
    tasks.push_back(task);
}

void ChainProcessor::handleImage(QImage image)
{
    if(tasks.size())
    {
        Task task = tasks[0];
        tasks.pop_front();

        emit status(QString(Main::instance()->translate("ChainProcessor", "Starting task: %1")).arg(task.methodName));

        task.arguments.push_front(Q_ARG(QImage, image));
        task.arguments.push_front(Q_ARG(QObject*, this));
        QMetaObject::invokeMethod(ImageProcessor::instance(),
                                  task.methodName.toStdString().c_str(),
                                  Qt::QueuedConnection,
                                  task.arguments.value(0, QGenericArgument()),
                                  task.arguments.value(1, QGenericArgument()),
                                  task.arguments.value(2, QGenericArgument()),
                                  task.arguments.value(3, QGenericArgument()),
                                  task.arguments.value(4, QGenericArgument()),
                                  task.arguments.value(5, QGenericArgument()),
                                  task.arguments.value(6, QGenericArgument()),
                                  task.arguments.value(7, QGenericArgument()),
                                  task.arguments.value(8, QGenericArgument()),
                                  task.arguments.value(9, QGenericArgument()));
    }
    else
    {
        QMetaObject::invokeMethod(sender, "handleImage", Q_ARG(QImage, image));
        this->deleteLater();
    }
}
