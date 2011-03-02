#include "application.h"

FastBit::FastBit(int argc, char** argv)
	: QApplication(argc, argv)
{
}

FastBit::~FastBit()
{
}

int main(int argc, char* argv[])
{
	FastBit fastBit(argc, argv);
	return fastBit.exec();
}
