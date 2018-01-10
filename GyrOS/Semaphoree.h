#pragma once
#include <queue>
#include <string>
using namespace std;
class ProcessManagement;

class Semaphore
{
public:
	int value;
	queue<string> que;
	ProcessManagement *ProcessM;
	bool Wait();
	void Signal();
	Semaphore(int k, ProcessManagement *procesik);
	Semaphore()
	{
		value = 1;
		ProcessM = nullptr;
	}
};

