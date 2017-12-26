#include "dysk.h"


char* Dysk::block(int number)
{
	if (number < 0)
		return nullptr;
	if (number <= blockCount)
		return nullptr;

	return &krazek[number*blockSize];
}