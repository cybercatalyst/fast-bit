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

#ifndef CHAIN_PROCESSOR_H
#define CHAIN_PROCESSOR_H

#include <QImage>
#include <QObject>
#include <QThread>

class ChainProcessor : public QObject
{
    Q_OBJECT
public:
    ChainProcessor(QObject *sender);
    ~ChainProcessor();

    void addTask(QString methodName, QList<QGenericArgument> arguments = QList<QGenericArgument>());

public slots:
    void handleImage(QImage image);

signals:
    /**
      * This signal is emitted, whenever there is a new status message.
      */
    void status(QString message);

private:
    struct Task
    {
        QString methodName;
        QList<QGenericArgument> arguments;
    };

    QList<Task> tasks;

    QObject *sender;
    QThread *processingThread;
};

#endif // CHAIN_PROCESSOR_H
