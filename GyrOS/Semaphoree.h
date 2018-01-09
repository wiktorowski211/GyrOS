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
	void Wait();
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
