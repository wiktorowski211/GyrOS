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

	std::string print_directory();

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
	void free_index_block(int block);
};

template <int num>
int find_free(std::bitset<num>& b);