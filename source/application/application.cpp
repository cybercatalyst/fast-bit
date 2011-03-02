#include "application.h"
#include "frontend.h"

FastBit::FastBit(int argc, char** argv)
	: QApplication(argc, argv)
{
	Frontend::userInterface().information("Starting application..");
}

FastBit::~FastBit()
{
	qDebug("Cleaning up..");
}

int main(int argc, char* argv[])
{
	FastBit fastBit(argc, argv);
	return fastBit.exec();
}
