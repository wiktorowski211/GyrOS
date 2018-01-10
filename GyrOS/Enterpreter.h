#pragma once
#include "Process.h"
#include "Pamiec.h"
//


class Enterpreter {
public:
	Enterpreter(Pamiec* pam) {this->memory = pam;}

	Pamiec * memory = nullptr;

	void InterpretLine(Process* proc);

	State runCommand(const std::string& command, Process* proc);
private:
	State parseError(Process& p);

};