#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include "ProcesorManager.h"

using namespace std;

void Scheduler::AddProcess(Process* proc)
{
	processes.push(proc);
}

void Scheduler::Run()
{
	while (processes.size() > 0) {
		process = processes.front();
		int quantum = 5;
		process->processState = 2;
		while (quantum > 0 && process->processState == 2) {
			//wywo³aj jedna linie kodu
			quantum--;
		}
		processes.pop();
		if (process->processState == 1)
		{
			processes.push(process);
		}
	}
}