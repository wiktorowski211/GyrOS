#pragma once
#include <queue>
#include "ProcessManagement.h"
#include "ProcesorManager.h"
#include <string>
using namespace std;

class Semaphore
{
public:
	int value;
	queue<string> que;
	Scheduler *ProcesorM;
	ProcessManagement *ProcessM;
	void Wait();
	void Signal();
	Semaphore(int k,Scheduler *procek, ProcessManagement *procesik)
	{
		value = k;
		ProcessM = procesik;
		procek = ProcesorM;
	}
};
struct SemaphoreFactory {
	Scheduler *ProcesorM;
	ProcessManagement *ProcessM;
	Semaphore CreateSemaphore(int k);
	SemaphoreFactory(Scheduler *p, ProcessManagement *h)
	{
		ProcesorM = p;
		ProcessM = h;
	}
};
