#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include "ProcessManagement.h"
using namespace std;

class Scheduler {
public:
	Scheduler() {};
	Process* process;
	void AddProcess(Process* proc);
	void Run();
private:
	queue<Process*> processes;
};