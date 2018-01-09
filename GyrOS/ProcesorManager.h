#pragma once
#include <iostream>
#include <queue>
#include "ProcessManagement.h"
using namespace std;

class Scheduler {
public:
	Scheduler() { ResetQuantum(); };
	void AddProcess(Process* proc);
	void DeleteProcess();
	void DeleteProcess();
	Process* GetProcess();
	void Step(int steps);
	int quantum;
private:
	queue<Process*> processes;
	void ResetQuantum();
	Process* process;
};