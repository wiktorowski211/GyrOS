#include "Enterpreter.h"

void Enterpreter::InterpretLine(Process* proc) {//counter jeszcze 
	cout<< memory->odczyt(proc->GetPID(),proc->programCounter)<<endl;
	proc->programCounter++;
}
