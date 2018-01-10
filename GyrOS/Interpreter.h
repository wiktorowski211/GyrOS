#pragma once
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

class Registry
{
	int counter = 0;
	short int registerA;
	short int registerB;
	short int registerC;
public:
	Registry()
	{
		registerA = 0; //akumulator
		registerB = 1; //rejestr B
		registerC = 0; //rejestr C - na podstawie tego rozkazu zachodza (lub nie) skoki
		counter = 0; //adres rozkazu, ktory bedzie wykonywany
	}

	short int get_A();
	short int get_B();
	short int get_C();

	void set_A(short int);
	void set_B(short int);
	void set_C(short int);

	int get_counter();
	void set_counter(int);
};

void readFile(string myArray[]);

void readFile(string myArray[], string fileName);

string* split(string toSplit);

void runCommand(string command, Registry &reg);

void runProgram(string program[], Registry &reg);

