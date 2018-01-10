#include "Scheduler.h"

using namespace std;

Scheduler::Scheduler() {
	ResetQuantum();
};

void Scheduler::AddProcess(Process* proc)
{
	processes.push_back(proc);
	if (process == nullptr) {
		process = processes.front();
	}
}

void Scheduler::DeleteProcess()
{
	processes.pop_front();
	SetNext();
}

void Scheduler::DeleteProcess(Process* proc)//wywolac jesli proces zmieni stan na terminated
{
	if (proc == process) {
		DeleteProcess();
	}
	else {
		processes.erase(std::remove(processes.begin(), processes.end(), proc), processes.end()); // TRZEBA PRZESTOWAC
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
		if (processes.size() > 0)
		{
			if (quantum > 0 && (process->processState == 1 || process->processState == 2))
			{
				process->processState = 2;

				//wywo³aj jedna linie kodu;

				std::cout << "Actual process: " << process->name << " ID: " << process->GetPID() << " Quantum: " << quantum << endl;	//to wrzucimy w interpreterze
				quantum--;
			}
			else if (process->processState != 1 && process->processState != 2) {
				std::cout <<"Zly stan procesu!!! Actual process: " << process->name << " ID: " << process->GetPID() << endl;
			}

			if (quantum <= 0 && process->processState == 2)
			{
				process->processState = 1;
				processes.pop_front();
				processes.push_back(process);
				SetNext();
			}
		}
	}
}
void Scheduler::SetNext() {
	ResetQuantum();
	if (processes.size() > 0)
		process = processes.front();
	else
		process = nullptr;
}
