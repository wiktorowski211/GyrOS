#include "Scheduler.h"

using namespace std;

Scheduler::Scheduler(Enterpreter* inter, Process* init) {
	this->interpreter = inter;
	this->init = init;
	process = init;
	ResetQuantum();
};

void Scheduler::AddProcess(Process* proc)
{
	processes.push_back(proc);
	if (process == init) {
		process = processes.front();
		ResetQuantum();
	}
}

void Scheduler::DeleteProcess()
{
	processes.pop_front();
	SetNext();
}

void Scheduler::DeleteProcess(Process* proc)//wywolac jesli proces zmieni stan na terminated
{
	if (proc == init)
		return;
	if (proc == process) {
		DeleteProcess();
	}
	else {
		processes.erase(std::remove(processes.begin(), processes.end(), proc), processes.end());
	}
}

Process* Scheduler::GetProcess() 
{
	return process;
}

void Scheduler::ResetQuantum() 
{
	quantum = 5;
}

void Scheduler::Step(int steps)
{
	for (int i = 0; i < steps; i++)
	{
		if (quantum > 0 && (process->processState == READY || process->processState == RUNNING))
		{
			process->processState = 2;
			std::cout << "Actual process: " << process->name << " ID: " << process->GetPID() << " Quantum: " << quantum << endl;
			quantum--;
			interpreter->InterpretLine(process);
		}
		else if (process->processState != READY && process->processState != RUNNING) {
			std::cout << "Wrong process state!!! Actual process: " << process->name << " ID: " << process->GetPID() << endl;
		}

		if (quantum <= 0 && process->processState == 2)
		{
			if (processes.size() > 0) {
				process->processState = 1;
				processes.pop_front();
				processes.push_back(process);
				SetNext();
			}
			else if (process == init) {
				ResetQuantum();
			}
		}
	}
}

void Scheduler::SetNext() {
	ResetQuantum();
	if (processes.size() > 0)
		process = processes.front();
	else
		process = init;
}
