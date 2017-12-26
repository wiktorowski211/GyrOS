#pragma once



struct inode
{

	// dowiazania twarde
	int hardlinks = 0;
	int size = 0;

	int block1 = -1;
	int block2 = -1;
	// indeksowanie jednopoziomowe
	int indexblock = -1;
};