#pragma once

#include <bitset>
#include <string>
#include <vector>
#include <unordered_map>

#include "dysk.h"
#include "inode.h"


class Filesystem
{
public:
	Filesystem();

	bool createFile(const std::string& name);
	bool deleteFile(const std::string& name);

	bool writeFile(const std::string& name, const std::string& tresc);
	// coming soon, reszta tych funkcji juz dziala
	bool appendFile(const std::string& name, const std::string& tresc);
	bool readFile(const std::string& name, std::string& output) const;
	std::string print_directory() const;
	std::string statistics() const;

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
};

template <int num>
int find_free(std::bitset<num>& b);