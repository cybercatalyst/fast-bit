#include "application.h"
#include "frontend.h"
#include <iostream>
#include <QApplication>

FastBit::FastBit()

{
    Frontend::userInterface().information("Application launched.");
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
