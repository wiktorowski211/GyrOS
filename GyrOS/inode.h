#pragma once



struct inode
{
	static const int maxBlocks = 11;
	// dowiazania twarde
	int hardlinks = 0;
	int size = 0;
	int blocks = 0;

	int block1 = -1;
	// indeksowanie jednopoziomowe
	int indexblock = -1;
};