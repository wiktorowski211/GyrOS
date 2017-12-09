#include <vector>
#include <string>
#include <iostream>
#include <queue>
using namespace std;
class Process {
public:
	Process(const string& name, int burst) : _name(name) { _burst = burst; }
	bool running() const { cout << "Running " << this->_name << endl; return true; }
	bool ending() const { cout << "Ending " << this->_name << endl; return true; }
	int _burst;

private:
	const string _name;
};

class Scheduler {
public:
	Scheduler() {};
	Process* _process;
	void addProcess(const string& name, int burst) { _processes.push(new Process(name, burst)); }
	void run()
	{ 
		while (_processes.size() >0) {
			singleProcessRun();
		}
	}
private:
	void singleProcessRun()
	{
		_process = _processes.front();
		_process->running();
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
			_process->ending();
		}
	}
private:
	queue<Process*> _processes;
	const int quantum = 10;
};