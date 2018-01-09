#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include "ProcessManagement.h"
using namespace std;

class Scheduler {
public:
	Scheduler() { ResetQuantum(); };
	Process* process;
	void AddProcess(Process* proc);
	void DeleteProcess();
	void Step(int steps);
	int quantum;
private:
	queue<Process*> processes;
	void ResetQuantum();
};