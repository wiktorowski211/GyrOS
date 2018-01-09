#pragma once
#include "Process.h"
#include <iostream>
#include <vector>
#include <string>
#include "ProcesorManager.h"

class Pamiec;
struct ProcessManagement
{
public:
	Scheduler* scheduler;
	Pamiec *c;
	Process* init; //proces, który wytwarza się przy startowaniu systemu
	int freeID = 0; //nastepny wolny numer ID do wykorzystania

	ProcessManagement();

	std::vector<Process*> readyProcesses;

	Process* FindProcess(int ID, Process* init);

	Process* FindProcess(std::string name, Process* init);

	int FindFreeID();

	void AddProcess(std::string processName, std::string commands, int parentID);

	void KillProcess(std::string name);

	void ChangeState(std::string name, int newstate);

	void PrintProcess(std::string name);

	void PrintAllProcesses();


};
