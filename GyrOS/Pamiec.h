#pragma once
#include "stdafx.h"
#include<iostream>
#include<conio.h>
#include<string>
#include<list>
#include<algorithm>
#include<fstream>
#include "Semaphoree.h"
//#include "ProcesorManager.h"
using namespace std;


// Struktury wykorzystywane w listach 
struct proces
{
	int PID;
	int wielkosc;
	int start;
	string commands;
	int processCounter = 0;
};
struct wolne_miejsca
{
	int wielkosc;
	int poczatek;
	int k = wielkosc + poczatek;
};


class Pamiec
{
public:
	int ilosc = 128;
	int wolne = 128;
	list<proces> l_procesow;
	list<wolne_miejsca> l_wolne;
	Semaphore Mem;
	/*Semaphore FullMemmory;
	Semaphore FSBEM;
	ProcessManagement * p;
	Pamiec(ProcessManagement *h)
	{
	p = h;
	FullMemmory.SetArg(1, h);
	FSBEM.SetArg(1, h);
	}*/
private:
	int ostatni = 0;

public:

	/*Sposób dodania procesu do pamięci opiera się na wartości zmiennej 'wolne'. Jeśli 'wolne' jest wieksze niz wielkosc procesu, ale żaden z bloków wolnej pamięci nie
	spełnia wymagań, zachodzi fragmentacja pamięci a wraz z nią łączenie nowo powstałych bloków wolnej pamięci. Jeśli 'wolne' jest mniejsze od wielkości procesu,
	wtedy proces nie może zostać dołączony do pamięci.*/
	//void dodaj(int PID, int w, string commands);
	void dodaj(int PID, string FileName);
	/*Usuwa proces z listy procesów po czym tworzy blok wolnej pamięci w miejscu usuniętego procesu. Po tym zabiegu następuje łączenie wolnych bloków pamięci w całość.*/
	void usun(int pid);

	void zawartosc();
	void laczenie();
	void fragmentacja();
	void odczyt(int PID);
};
