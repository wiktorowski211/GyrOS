#pragma once



class Dysk
{
public:

	// zwraca nullptr w przypadku nieprawidlowego numeru bloku
	char* block(int number);

	const static int size = 1024;
	const static int blockSize = 32;
	const static int blockCount = Dysk::size / Dysk::blockSize;
private:
	char krazek[size];
};