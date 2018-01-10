#pragma once
#include <iostream>
#include <deque>
#include <algorithm>
#include "Process.h"
#include "Interpreter.h"

using namespace std;

class Scheduler {
public:
	Scheduler() { ResetQuantum(); };
	void AddProcess(Process* proc);
	void DeleteProcess();
	void DeleteProcess(Process* proc);
	Process* GetProcess();
	void Step(int steps);
	int quantum;
private:
	deque<Process*> processes;
	void ResetQuantum();
	Process* process;
};