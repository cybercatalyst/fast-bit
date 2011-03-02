#include "application.h"
#include "frontend.h"
#include <iostream>

FastBit::FastBit(int argc, char** argv)
	: QApplication(argc, argv)
{
    std::cout << "Application launched." << std::endl;
}

FastBit::~FastBit()
{
}

int main(int argc, char* argv[])
{
	FastBit fastBit(argc, argv);
	return fastBit.exec();
}
