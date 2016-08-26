#include <iostream>

#include "AppChangeEventDriver.h"


int main(int argc, char **argv) {
	std::cout << "programm started" << std::endl;

	AppChangeEventDriver driver;
	driver.start();

	std::cout << "programm ended" << std::endl;
	return 0;
}
