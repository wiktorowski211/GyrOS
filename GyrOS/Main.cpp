#include "Dysk/Filesystem.h"
#include <iostream>


int main()
{
	Filesystem file;
	file.createFile("Seba");
	file.createFile("sonsiad");
	file.deleteFile("Seba");

	std::cout << file.print_directory() << std::endl;
	getchar();
	return 0;
}