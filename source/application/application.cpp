#include "application.h"

FastBit::FastBit(int argc, char** argv)
	: QApplication(argc, argv)
{
	qDebug("Starting application..");
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
