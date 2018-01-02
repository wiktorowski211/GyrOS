#include "Filesystem.h"

template <int num>
int find_free(std::bitset<num>& b)
{
	for (int i = 0; i < num; ++i)
		if (!b[i]) return i;
	return -1;
}

bool Filesystem::resize(inode& node, int size)
{
	int reqBlocks = (int)ceil((double)size / (double)Dysk::blockSize);

	// jesli mamy za duzo blokow zwolnij kilka
	if (node.blocks > reqBlocks)
	{
		for (int i = node.blocks; i > reqBlocks && i > 1; --i)
		{
			free_block(dysk.block(node.indexblock)[i - 2]);
			dysk.block(node.indexblock)[i - 2] = -1;
		}

		if ((reqBlocks == 0 || reqBlocks == 1) && node.indexblock != -1)
		{
			free_block(node.indexblock);
			node.indexblock = -1;
		}

		if ( reqBlocks == 0)
		{
			free_block(node.block1);
			node.block1 = -1;
		}
	}
	// jesli mamy za malo blokow zaalokuj kilka
	if (node.blocks < reqBlocks)
	{
		if (node.blocks == 0)
		{
			node.block1 = allocate_block();
			if (node.block1 == -1)
				return false;

			node.blocks = 1;
		}
		if (node.indexblock == -1 && reqBlocks > 1)
		{
			node.indexblock = create_index_block();
			// za malo miejsca na stworzenie bloku indeksowego
			if (node.indexblock == -1)
			{
				// przywroc poprzedni stan
				resize(node, node.size);
				return false;
			}

		}
		for (int i = node.blocks+1; i <= reqBlocks; ++i)
		{
			dysk.block(node.indexblock)[i - 2] = allocate_block();
			// alokacja bloku nie powiodla sie
			if (dysk.block(node.indexblock)[i - 2] == -1)
			{
				// przywroc poprzedni stan
				resize(node, node.size);
				return false;
			}
			++node.blocks;
		}

	}
	node.size = size;
	node.blocks = reqBlocks;
	return true;
}

void Filesystem::free_block(int block)
{
	if (!freeBlockList[block])
		throw std::logic_error("free_block: you are trying to free unallocated block");
	freeBlockList[block] = false;
	++freeBlockCount;
}
int Filesystem::allocate_block()
{
	// brak wolnych bloków
	if (freeBlockCount == 0)
		return -1;
	for (int i = 0; i < freeBlockList.size(); ++i)
	{
		if (freeBlockList[i] == 0)
		{
			freeBlockList[i] = 1;
			--freeBlockCount;
			return i;
		}
	}
	return -1;
}

int Filesystem::create_index_block()
{
	int newIndexB = allocate_block();
	if (newIndexB == -1)
		return -1;
	int i = 3;
	memset(dysk.block(newIndexB), -1, Dysk::blockSize);
	i = 5;
	return newIndexB;
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
	--wezly[toFree].hardlinks;
	if (wezly[toFree].hardlinks == 0)
	{
		freeInodeList[toFree] = 0;
		++freeInodeCount;
		resize(wezly[toFree], 0);
	}
	katalog.erase(name);
	return true;
}

bool Filesystem::writeFile(const std::string& name, const std::string& tresc)
{
	// plik nie jestnieje wiec jest to niepoprawna operacja
	if (!katalog.count(name))
		return false;
	// maksymalny przyjety rozmiar pliku to 1 blok w inode i 10 blokow w bloku indeksowym
	if (tresc.length() > inode::maxBlocks * Dysk::blockSize)
		return false;

	/// WARUNEK: jesli plik nie jest otwarty przez ten proces - zwroc FALSE

	if(!resize(wezly[katalog[name]], (int)tresc.size()))
		return false;

	// przepisz dane
	int lastBlockSpace;
	auto& node = wezly[katalog[name]];

	if ((node.size % Dysk::blockSize) == 0)
		lastBlockSpace = Dysk::blockSize;
	else
		lastBlockSpace = node.size%Dysk::blockSize;

	int trescLoc = 0;
	if (node.blocks == 0)
		return true;
	if (node.blocks == 1)
	{
		for (int i = 0; i < lastBlockSpace; ++i)
		{
			dysk.block(node.block1)[i] = tresc[trescLoc];
			++trescLoc;
		}
	}
	else
	{
		for (int i = 0; i < Dysk::blockSize; ++i)
		{
			dysk.block(node.block1)[i] = tresc[trescLoc];
			++trescLoc;
		}
		for (int n = 2; n < node.blocks; ++n)
		{
			for (int i = 0; i < Dysk::blockSize; ++i)
			{
				dysk.block(dysk.block(node.indexblock)[n - 2])[i] = tresc[trescLoc];
				++trescLoc;
			}
		}
		for (int i = 0; i < lastBlockSpace; ++i)
		{
			// node.blocks -1 (liczymy od 0) - 1 (blok bezposrednio w iwezle)
			dysk.block(dysk.block(node.indexblock)[node.blocks - 2])[i] = tresc[trescLoc];
			++trescLoc;
		}
	}

	return true;
}

bool appendFile(const std::string& name, const std::string& tresc)
{
	return false;
}

std::string Filesystem::readFile(const std::string& name) const
{
	/// WARUNEK: jesli plik nie jest otwarty przez ten proces - zwroc pusty
	
	auto it = katalog.find(name);
	if (it == katalog.end())
		return "";
	int inode = it->second;
	std::string s;
	auto& node = wezly[inode];

	int lastBlockSpace;
	if ((node.size % Dysk::blockSize) == 0)
		lastBlockSpace = Dysk::blockSize;
	else
		lastBlockSpace = node.size%Dysk::blockSize;

	if (node.blocks == 0)
		return s;
	if (node.blocks == 1)
	{
		for (int i = 0; i < lastBlockSpace; ++i)
			s += dysk.block(node.block1)[i];
	}
	else
	{
		for (int i = 0; i < Dysk::blockSize; ++i)
			s += dysk.block(node.block1)[i];
		for (int n = 2; n < node.blocks; ++n)
		{
			for (int i = 0; i < Dysk::blockSize; ++i)
				s += dysk.block(dysk.block(node.indexblock)[n-2])[i];
		}
		for (int i = 0; i < lastBlockSpace; ++i)
			// node.blocks -1 (liczymy od 0) - 1 (blok bezposrednio w iwezle)
			s += dysk.block(dysk.block(node.indexblock)[node.blocks - 2])[i];
	}

	return s;
}

std::string Filesystem::print_directory() const
{
	std::string s;
	s += "Liczba wpisow: " + std::to_string(katalog.size()) + "\n";
	s += "Nazwa:\t\tNumer i-wezla:\n";
	for (auto& x : katalog)
	{
		s += x.first + "\t\t" + std::to_string(x.second) + "\n";
	}

	return s;
}

std::string Filesystem::statistics() const
{
	std::string s;
	s += "Miejsce (wolne/zajete): " + std::to_string(freeBlockCount) + "/" + std::to_string(Dysk::blockCount);
	return s;
}