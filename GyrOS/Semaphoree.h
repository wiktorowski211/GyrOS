#pragma once
#include "ProcessManagement.h"
#include <queue>
#include <string>
using namespace std;


class Semaphore
{
public:
	int value;
	queue<string> que;
	ProcessManagement *ProcessM;
	bool Wait();
	void Signal();
	Semaphore(int k, ProcessManagement *procesik)
	{
		value = k;
		ProcessM = procesik;
	}
	Semaphore()
	{
		value = 1;
		ProcessM = nullptr;
	}
};

