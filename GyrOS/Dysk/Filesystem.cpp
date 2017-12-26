#include "Filesystem.h"

template <int num>
int find_free(std::bitset<num>& b)
{
	for (int i = 0; i < num; ++i)
		if (!b[i]) return i;
	return -1;
}

void Filesystem::free_block(int block)
{

}

void Filesystem::free_index_block(int block)
{

}

Filesystem::Filesystem(): freeBlockCount{Dysk::blockCount}, freeInodeCount{Filesystem::inodeCount}
{

}

bool Filesystem::createFile(const std::string& name)
{
	// brak wolnych i wezlow
	if (!freeInodeCount)
		return false;
	int newInode = find_free(freeInodeList);
	if (newInode == -1)
		throw std::logic_error("createFile: find_free returned -1 when it shouldn't\n");
	// plik o danej nazwie istnieje w katalogu glownym
	if (katalog.count(name))
		return false;

	wezly[newInode].hardlinks = 1;
	freeInodeList[newInode] = true;
	--freeInodeCount;

	katalog.emplace(name, newInode);
	return true;
}

bool Filesystem::deleteFile(const std::string& name)
{
	// plik nie istnieje wiec jest to niepoprawna operacja
	if (!katalog.count(name))
		return false;

	int toFree = katalog[name];
	freeInodeList[toFree] = 0;
	++freeInodeCount;
	free_block(wezly[toFree].block1);
	free_block(wezly[toFree].block2);
	free_index_block(wezly[toFree].indexblock);

	katalog.erase(name);
	return true;
}

std::string Filesystem::print_directory()
{
	std::string s;
	s += "Liczba wpisow: " + std::to_string(katalog.size()) + "\n";
	s += "Nazwa:\t\tNumer i-wezla:\n";
	for (auto& x : katalog)
	{
		s += x.first + "\t\t" + std::to_string(x.second) + "\n";
	}
	//s = "butt";
	return s;
}