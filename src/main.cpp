#include <iostream>

#include "AppChangeEventDriver.h"


int main(int argc, char **argv) {
	aced::AppChangeEventDriver driver;
	driver.start();

	return 0;
}
