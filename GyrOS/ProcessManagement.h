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

	Process* parent; //procesy przedstawiają drzewo, gdzie rodzic jest procesem macierzystym
	std::vector<Process*> children; //a dzieci jego procesami potomnymi

	int regA;    // 4 wartości rejestrów procesora
	int regB;
	int regC;
	int regD;

	int programCounter = 0; //wskazuje następną instrukcję do wykonania
	int programPosition;

	int GetPID() { return PID; }
	int GetProcessState() { return processState; }
	int GetPid() { return PID; }

	Process(int ID, Process* father, std::string processName, std::string txt)
	{
		processState = 0;
		PID = ID;
		parent = father;
		//ram->WriteToMemory(ID, commands);
		name = processName;
	}//konstruktor procesu;

};

struct ProcessManagement
{
public:
	Process* init; //proces, który wytwarza się przy startowaniu systemu
	int freeID = 0; //nastepny wolny numer ID do wykorzystania

	ProcessManagement() {
		init = new Process(FindFreeID(), nullptr, "init", "comm");
	}

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































/*
//
//struct Process
//{
//public:
//	int PID;
//	int processState; //0=virgin, 1=ready, 2=running, 3=waiting, 4=terminated;
//	std::string name;
//
//	Process* parent; //procesy przedstawiają drzewo, gdzie rodzic jest procesem macierzystym
//	std::vector<Process*> children; //a dzieci jego procesami potomnymi
//
//	int regA;    // 4 wartości rejestrów procesora
//	int regB;
//	int regC;
//	int regD;
//
//	int programCounter = 0; //wskazuje następną instrukcję do wykonania
//	int programPosition;
//
//	int GetPID();
//	int GetProcessState();
//
//	Process(int ID, Process* father, std::string processName, std::string txt); //konstruktor procesu;
//
//};
//
//
//struct ProcessManagement
//{
//public:
//	Process* init; //proces, który wytwarza się przy startowaniu systemu
//
//	std::vector<Process*> readyProcesses;
//	//
//	//
//	//
//	//
//	// tu dodać marcina rzeczy
//	//
//	//
//	//
//	//
//
//
//	int freeID = 0; //nastepny wolny numer ID do wykorzystania
//
//	ProcessManagement() {
//		init = new Process(FindFreeID(), nullptr, "init", NULL);
//	};
//
//	Process* FindProcess(int ID, Process* init); //funkcja przeszukująca drzewo procesów
//
//	Process* FindProcess(std::string name, Process* init);
//
//	int FindFreeID(); //wybieranie wolnego ID
//
//	void AddProcess(std::string processName, std::string commands, int parentID = 0);
//
//	void KillProcess(std::string name);
//
//	void ChangeState(int ID, int newstate);
//
//	void PrintProcess(std::string name);
//
//	void PrintAllProcesses();
//};*/