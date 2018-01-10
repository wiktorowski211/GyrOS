#pragma once
#include "Process.h"
#include "Scheduler.h"
#include "Pamiec.h"
#include "Enterpreter.h"
#include <iostream>
#include <vector>
#include <string>

class Pamiec;

class ProcessManagement
{
public:
	Scheduler* scheduler = nullptr;
	Pamiec* MemoryManagement = nullptr;
	Enterpreter* interpreter = nullptr;

	Process* init; //proces, który wytwarza się przy startowaniu systemu
	int freeID = 0; //nastepny wolny numer ID do wykorzystania

	bool memory_is_available = true;

	// prosze nie tworzyc innych konstruktorow!!!
	ProcessManagement(Pamiec* P, Enterpreter* inter) : MemoryManagement{ P } {
		init = new Process(FindFreeID(), nullptr, "init", "comm");
		interpreter = inter;
		scheduler = new Scheduler(interpreter,init);
		MemoryManagement->dodaj(0, "init.txt");
		init->processState = READY;
	}

	Process* FindProcess(int ID, Process* init);

	Process* FindProcess(std::string name, Process* init);

	int FindFreeID();

	void AddProcess(std::string processName, std::string commands, int parentID);

	void KillProcess(std::string name);

	void ChangeState(std::string name, int newstate);

	void PrintProcess(std::string name);

	void PrintAllProcesses();

};
