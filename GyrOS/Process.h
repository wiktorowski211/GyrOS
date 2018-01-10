#pragma once
#include <iostream>
#include <vector>
#include <string>

enum State
{
	VIRGIN = 0,
	READY = 1,
	RUNNING = 2,
	WAITING = 3,
	TERMINATED = 4,
};

struct Process
{
public:
	int PID;
	int processState; //0=virgin, 1=ready, 2=running, 3=waiting, 4=terminated;
	std::string name;

	Process* parent; //procesy przedstawiaj¹ drzewo, gdzie rodzic jest procesem macierzystym
	std::vector<Process*> children; //a dzieci jego procesami potomnymi
private:
	int regA;    // 4 wartoœci rejestrów procesora
	int regB;
	int regC;
	int regD;
	int programCounter = 0; //wskazuje nastêpn¹ instrukcjê do wykonania
public:
	int programPosition;

	int GetPID() { return PID; }
	int GetProcessState() { return processState; }
	void set_A(int a);
	void set_B(int b);
	void set_C(int c);
	void set_D(int d);
	int get_A();
	int get_B();
	int get_C();
	int get_D();	
	
	void set_counter(int counter);
	int get_counter();
	
	
	Process(int ID, Process* father, std::string processName, std::string txt)
	{
		processState = VIRGIN;
		PID = ID;
		parent = father;
		//ram->WriteToMemory(ID, commands);
		name = processName;
	}//konstruktor procesu;

};
