#pragma once
#include "Process.h"
#include "Pamiec.h"

class Enterpreter {
public:
	Enterpreter(Pamiec* pam) {
		this->memory = pam;
	}

	Pamiec * memory = nullptr;
	void InterpretLine(Process* proc);
};