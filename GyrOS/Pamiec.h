#pragma once
#include<iostream>
#include<conio.h>
#include<string>
#include<list>
#include<algorithm>
#include<fstream>
using namespace std;


// Struktury wykorzystywane w listach 
struct proces
{
	int PID;
	int wielkosc;
	int start;
	string commands;
	int MemoryPointer = 0;
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
	
	Pamiec()
	{
		wolne_miejsca wm;
		wm.poczatek = 1;
		wm.k = 128;
		wm.wielkosc = wm.k - wm.poczatek;
		l_wolne.push_back(wm);
	}
private:
	int ostatni = 0;

public:

	/*Sposób dodania procesu do pamięci opiera się na wartości zmiennej 'wolne'. Jeśli 'wolne' jest wieksze niz wielkosc procesu, ale żaden z bloków wolnej pamięci nie
	spełnia wymagań, zachodzi fragmentacja pamięci a wraz z nią łączenie nowo powstałych bloków wolnej pamięci. Jeśli 'wolne' jest mniejsze od wielkości procesu,
	wtedy proces nie może zostać dołączony do pamięci.*/
	
	int dodaj(int PID, string FileName);
	
	/*Usuwa proces z listy procesów po czym tworzy blok wolnej pamięci w miejscu usuniętego procesu. Po tym zabiegu następuje łączenie wolnych bloków pamięci w całość.*/
	void usun(int pid);

	void zawartosc();
	void laczenie();
	void fragmentacja();
	string odczyt(int PID, int counter);
	char odczytznaku(int PID, int place);
};

