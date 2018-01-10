#pragma once
#include <string>

//

class Pamiec;
class Process;
class ProcessManagement;

class Enterpreter {
public:
	Enterpreter(Pamiec* pam, ProcessManagement* processManager);

	Pamiec * memory = nullptr;
	ProcessManagement*  processes = nullptr;

	void InterpretLine(Process* proc);

	void runCommand(const std::string& command, Process* proc);
private:
	void parseError(Process& p);

};