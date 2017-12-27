#include <vector>
#include <string>
#include <iostream>
#include <queue>
using namespace std;
class Process {
public:
	Process(const string& name, int burst) : _name(name) { _burst = burst; }
	bool Running() const { cout << "Running " << this->_name << endl; return true; }
	bool Ending() const { cout << "Ending " << this->_name << endl; return true; }
	int _burst;

private:
	const string _name;
};

class Scheduler {
public:
	Scheduler() {};
	Process* _process;
	void AddProcess(const string& name, int burst) { _processes.push(new Process(name, burst)); }
	void Run()
	{
		while (_processes.size() > 0 ) { 
			SingleProcessRun(); 
		}
	}
private:
	void SingleProcessRun()
	{
		_process = _processes.front();
		_process->Running();
		int tmpQuantum = quantum;
		while (tmpQuantum >0 && _process->_burst > 0) {
			cout << _process->_burst << endl;
			tmpQuantum--;
			_process->_burst--;
		}
		_processes.pop();
		if (_process->_burst > 0)
		{
			_processes.push(_process);
		}
		else
		{
			_process->Ending();
		}
	}
private:
	queue<Process*> _processes;
	const int quantum = 10;
};