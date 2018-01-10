#pragma once
#include <string>
#include "Filesystem.h"


class Pamiec;
struct Process;
class ProcessManagement;

class Enterpreter {
public:
	Enterpreter(Pamiec& pam, ProcessManagement& processManager, Filesystem& dysk);

	Pamiec& memory;
	ProcessManagement&  processes;
	Filesystem& dysk;

	void InterpretLine(Process* proc);

	void runCommand(const std::string& command, Process* proc);
private:
	void parseError(Process& p);
	// str = rejestr, val = wartosc do wpisania
	void setRegister(Process& p, const std::string& str, int val);
	// str = rejestr
	int Enterpreter::getRegister(Process& p, const std::string& str, bool& error);

};