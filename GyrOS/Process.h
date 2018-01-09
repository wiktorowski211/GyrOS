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

	Process(int ID, Process* father, std::string processName, std::string txt)
	{
		processState = 0;
		PID = ID;
		parent = father;
		//ram->WriteToMemory(ID, commands);
		name = processName;
	}//konstruktor procesu;

};