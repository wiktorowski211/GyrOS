#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <Windows.h>
#include "Filesystem.h"
#include "ProcessManagement.h"
#include "Pamiec.h"
using namespace std;

class Shell {
public:
	/*
	Deklaracje pozostałych modułów
	*/
	Pamiec ram;
	ProcessManagement procesy;
	Filesystem dysk;
	map<string, int> rozkaz;
	map<string, int> chk;
	bool work;
	Shell() : ram{}, procesy{ &ram }, dysk{}
	{
		rozkaz.insert(pair<string, int>("help", 1)); //wyświetla dostępne komendy
		rozkaz.insert(pair<string, int>("cls", 2)); //czyści konsole
		rozkaz.insert(pair<string, int>("del", 3));//usuwa plik
		rozkaz.insert(pair<string, int>("echo", 4));//przekazanie wartości na bufor lub do pliku
		rozkaz.insert(pair<string, int>("exit", 5));//zamyka konsolę
		rozkaz.insert(pair<string, int>("type", 6));//wyświetla zawartość pliku tekstowego
		rozkaz.insert(pair<string, int>("rename", 7));//zmienia nazwę pliku
		rozkaz.insert(pair<string, int>("start", 8));//uruchamia proces
		rozkaz.insert(pair<string, int>("taskkill", 9));//kończy proces
		rozkaz.insert(pair<string, int>("tasklist", 10));//lista procesów
		rozkaz.insert(pair<string, int>("go", 11));//wykonuje rozkaz asemblerowy - krok systemu
		rozkaz.insert(pair<string, int>("check", 12));//pokazuje stan systemu
		rozkaz.insert(pair<string, int>("mklink", 13));//dopisuje alias do wskazanego pliku
		rozkaz.insert(pair<string, int>("dir", 14));//wyswietla liste plikow
		rozkaz.insert(pair<string, int>("reg", 15));//stan rejestrow aktualnego procesu
		
		chk.insert(pair<string, int>("disc", 1));
		chk.insert(pair<string, int>("ram", 2));
		work = true;
	}
	void wydziel_rozkaz(string &kom);
	string begin(string &s);
private:
	void rozpoznaj_rozkaz(string s1, string s2);
	bool echo_przekaz(string &s);
	void help();
	void cls();
	void del(string &s);
	void echo(string &s);
	void ext();
	void type(string &s);
	void rename(string &s);
	void start(string &s);
	void taskkill(string &s);
	void tasklist();
	void go();
	void mklink(string &s);
	void reg();
	void nadpisz(string &s, string &p);
	void dopisz(string &s, string &p);
	void czytaj_skrypt(string s);
	void check(string &s);
	void dir();
	string standard(string &s);
	string namale(string &s);
	string end(string &s);
	void kropki(string s);
	string cudzy(string &s);
	int ilsep(string &s);
};