#include "application.h"
#include "frontend.h"
#include <iostream>
#include <QApplication>

FastBit::FastBit()

{
    Frontend::userInterface().information("Application launched.");
    Frontend::userInterface().message("This software is not meant for daily use.");
}

FastBit::~FastBit()
{
    Frontend::userInterface().information("Cleaning up.");
}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    FastBit fastBit;
    return app.exec();
}
