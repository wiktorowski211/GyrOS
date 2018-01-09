#pragma once
#include <iostream>
#include <vector>
#include <string>

struct Process
{
public:
	int PID;
	int processState; //0=virgin, 1=ready, 2=running, 3=waiting, 4=terminated;
	std::string name;

	Process* parent; //procesy przedstawiaj¹ drzewo, gdzie rodzic jest procesem macierzystym
	std::vector<Process*> children; //a dzieci jego procesami potomnymi

	int regA;    // 4 wartoœci rejestrów procesora
	int regB;
	int regC;
	int regD;

	int programCounter = 0; //wskazuje nastêpn¹ instrukcjê do wykonania
	int programPosition;

	int GetPID() { return PID; }
	int GetProcessState() { return processState; }
	int GetPid() { return PID; }

	Process(int ID, Process* father, std::string processName, std::string txt); //konstruktor procesu;
	
};

struct ProcessManagement
{
public:
	Process* init; //proces, który wytwarza się przy startowaniu systemu

	std::vector<Process*> readyProcesses;
	//
	//
	//
	//
	// tu dodać marcina rzeczy
	//
	//
	//
	//
	

	int freeID = 0; //nastepny wolny numer ID do wykorzystania

	ProcessManagement() {
		init = new Process(freeID, nullptr, "init", NULL);
		freeID++;
	};

	Process* FindProcess(int ID, Process* init); //funkcja przeszukująca drzewo procesów 

	Process* FindProcess(int ID, Process* init);

	Process* FindProcess(std::string name, Process* init);

	int FindFreeID();

	void AddProcess(std::string processName, std::string commands, int parentID);

	void KillProcess(std::string name);

	void ChangeState(std::string name, int newstate);

	void PrintProcess(int ID);

	void PrintAllProcesses();
};