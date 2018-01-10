#pragma once
#include <iostream>
#include <deque>
#include <algorithm>
#include "Process.h"
#include "Enterpreter.h"

using namespace std;

class Scheduler {
public:
	Scheduler(Enterpreter* inter);
	void AddProcess(Process* proc);
	void DeleteProcess();
	void DeleteProcess(Process* proc);
	void SetNext();
	Process* GetProcess();
	void Step(int steps);
	int quantum;
	Enterpreter* interpreter;
private:
	deque<Process*> processes;
	void ResetQuantum();
	Process* process;
};