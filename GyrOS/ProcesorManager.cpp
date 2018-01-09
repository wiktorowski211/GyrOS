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

void Scheduler::DeleteProcess()//wywolac jesli proces zmieni stan z running na waiting/terminated
{
	processes.pop();
	ResetQuantum();
	process = processes.front();
}

void Scheduler::ResetQuantum() {
	quantum = 5;
}

void Scheduler::Step(int steps)
{
	for (int i = 0; i < steps; i++)
	{
		if (processes.size > 0) {
			if (quantum > 0 && process->processState == 1) {
				process->processState = 2;
				//wywo³aj jedna linie kodu;
				quantum--;
			}

			if (quantum <= 0 && process->processState == 2)
			{
				DeleteProcess();

				process->processState = 1;
				processes.push(process);

				process = processes.front();
			}
		}
	}
	}
}