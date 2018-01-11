#pragma once

#include <bitset>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

#include "dysk.h"
#include "inode.h"
#include "Semaphoree.h"

class ProcessManagement;

class Filesystem
{
public:
	Filesystem(ProcessManagement& ProcessManager);

	bool openFile(const std::string& name);
	bool closeFile(const std::string& name);

	// stworz plik name
	bool createFile(const std::string& name);
	// usun plik name
	bool deleteFile(const std::string& name);
	// dodaj alias name2 do pliku name
	bool addFilename(const std::string& name, const std::string& name2);
	// zmien nazwe pliku z name na newname
	bool changeFilename(const std::string& name, const std::string& newname);
	// zapisz tresc do pliku o naziwe name ACHTUNG! Czysci to co bylo wczesniej napisane
	bool writeFile(const std::string& name, const std::string& tresc);
	// dopisz tresc do pliku o nazwie name
	bool appendFile(const std::string& name, const std::string& tresc);
	// wczytaj plik o nazwie name do std::stringa output
	bool readFile(const std::string& name, std::string& output) const;
	// czy plik o nazwie name istnieje, true = tak, false = nie
	bool exists(const std::string& name);
	// wyswietla pliki w katalogu i ich rozmiar
	void print_directory() const;
	// wyswietla zajete miejsce na dysku i ilosc iwezlow
	void statistics() const;

	static const int inodeCount = Dysk::blockCount;
private:
	int freeBlockCount;
	std::bitset<Dysk::blockCount> freeBlockList;

	int freeInodeCount;
	std::bitset<inodeCount> freeInodeList;
	
	std::unordered_map<std::string, int> katalog;

	Dysk dysk;
	inode wezly[inodeCount];

	void free_block(int block);
	int allocate_block();
	int create_index_block();
	bool resize(inode& node, int size);

	ProcessManagement& ProcessManager;
};

template <int num>
int find_free(std::bitset<num>& b);