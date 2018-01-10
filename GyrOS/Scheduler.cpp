#include "Scheduler.h"

using namespace std;

void Scheduler::AddProcess(Process* proc)
{
	processes.push_back(proc);
}

void Scheduler::DeleteProcess()
{
	processes.pop_front();
	ResetQuantum();
	process = processes.front();
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
			if (quantum > 0 && process->processState == 1) 
			{
				process->processState = 2;

				//wywo³aj jedna linie kodu;

				//std::cout << "Actual process: " << process->name<<" ID: "<<process->GetPID()<<endl;	//to wrzucimy w interpreterze
				quantum--;
			}

			if (quantum <= 0 && process->processState == 2)
			{
				DeleteProcess();

				process->processState = 1;
				processes.push_back(process);

				process = processes.front();
			}
		}
	}
}