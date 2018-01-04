#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <queue>
using namespace std;

class Scheduler {
public:
	Scheduler() {};
	Process* process;
	void AddProcess(const string& name, int burst) { processes.push(new Process(name, burst)); }
	void Run()
	{
		while (processes.size() > 0) {
			SingleProcessRun();
		}
	}
private:
	void SingleProcessRun()
	{
		process = processes.front();
		process->Running();
		int tmpQuantum = quantum;
		while (tmpQuantum >0 && process->_burst > 0) {
			cout << process->_burst << endl;
			tmpQuantum--;
			process->_burst--;
		}
		processes.pop();
		if (process->_burst > 0)
		{
			processes.push(process);
		}
		else
		{
			process->Ending();
		}
	}
private:
	queue<Process*> processes;
	const int quantum = 10;
};