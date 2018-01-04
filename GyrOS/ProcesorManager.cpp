#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include "ProcesorManager.h"

using namespace std;

void Scheduler::AddProcess(Process* proc) { processes.push(proc); }
void Scheduler::Run()
{
	while (processes.size() > 0) {
		process = processes.front();
		int tmpQuantum = quantum;
		process->processState = 2;
		while (tmpQuantum > 0 && process->processState == 2) {
			//wywo³aj interpeter
			tmpQuantum--;
		}
		process.
		if (process->processState == )
		{
			processes.push(process);
		}
		else
		{
			process->Ending();
		}
	}
}