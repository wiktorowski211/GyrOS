#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <Windows.h>
using namespace std;

class Shell {
public:
	map<string, int> rozkaz;
	bool work;
	Shell() {
		rozkaz.insert(pair<string, int>("help", 1)); //wyœwietla dostêpne komendy
		rozkaz.insert(pair<string, int>("cls", 2)); //czyœci konsole
		rozkaz.insert(pair<string, int>("del", 3));//usuwa plik
		rozkaz.insert(pair<string, int>("echo", 4));//przekazanie wartoœci na bufor lub do pliku
		rozkaz.insert(pair<string, int>("exit", 5));//zamyka konsolê
		rozkaz.insert(pair<string, int>("type", 6));//wyœwietla zawartoœæ pliku tekstowego
		rozkaz.insert(pair<string, int>("rename", 7));//zmienia nazwê pliku
		rozkaz.insert(pair<string, int>("start", 8));//uruchamia proces
		rozkaz.insert(pair<string, int>("taskkill", 9));//koñczy proces
		rozkaz.insert(pair<string, int>("tasklist", 10));//lista procesów
		rozkaz.insert(pair<string, int>("go", 11));//wykonuje rozkaz asemblerowy
		rozkaz.insert(pair<string, int>("check", 12));//pokazuje stan systemu 
		work = true;
	}
	void wydziel_rozkaz(string &kom);
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
	void go(string &s);
	void nadpisz(string &s, string &p);
	void dopisz(string &s, string &p);
	void czytaj_skrypt(string s);
	void check();
	string standard(string &s);
	string namale(string &s);
	string begin(string &s);
	string end(string &s);
	void kropki(string s);
};