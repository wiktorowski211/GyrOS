#pragma once
#include "stdafx.h"
#include<iostream>
#include<conio.h>
#include<string>
#include<list>
#include<algorithm>
using namespace std;

int SemaforPamieci = 0;

// Struktury wykorzystywane w listach 
struct proces
{
	string nazwa;
	int wielkosc;
	int start;
};
struct wolne_miejsca
{
	int wielkosc;
	int poczatek;
	int k = wielkosc + poczatek;
};



/// Predykat wykorzystywany podczas ustawiania kolejno bloków wolnej pamięci; ułatwia łączenie sąsiednich bloków w całość 
bool comp(const wolne_miejsca &a, const wolne_miejsca &b)
{
	return a.poczatek < b.poczatek;
}


class Pamiec
{
public:
	int ilosc = 128;
	int wolne = 128;

	list<proces> l_procesow;
	list<wolne_miejsca> l_wolne;


private:
	int ostatni = 0;

public:

	/*Sposób dodania procesu do pamięci opiera się na wartości zmiennej 'wolne'. Jeśli 'wolne' jest wieksze niz wielkosc procesu, ale żaden z bloków wolnej pamięci nie 
	spełnia wymagań, zachodzi fragmentacja pamięci a wraz z nią łączenie nowo powstałych bloków wolnej pamięci. Jeśli 'wolne' jest mniejsze od wielkości procesu,
	wtedy proces nie może zostać dołączony do pamięci.*/
	void dodaj(string n, int w)
	{
		bool szukaj_miejsca = false, po_fragmentacji = false;

		try {
			if (wolne < w)
				throw 0;
			else {

				do {
					po_fragmentacji = true;
					if (!l_wolne.empty())
					{
						for (auto e : l_wolne)
						{
							if (e.wielkosc >= w)
								szukaj_miejsca = true;
						}
					}
					else
						szukaj_miejsca = true;



					if (szukaj_miejsca)
					{
						wolne_miejsca wm;


						if (ostatni == 0)
						{
							wm.poczatek = w + 1;
							ostatni = w + 1;
							wm.k = 128;
							wm.wielkosc = wm.k - wm.poczatek;
							l_wolne.push_back(wm);
						}
						else
						{
							list<wolne_miejsca>::iterator itw;

							for (itw = l_wolne.begin(); itw != l_wolne.end(); itw++)
							{
								if (itw->wielkosc >= w)
								{
									wm.poczatek = itw->poczatek + w;
									break;
								}
							}
							bool finder = false;
							for (auto p : l_procesow)
							{
								if (p.start >= wm.poczatek)
								{
									wm.k = p.start - 1;
									finder = true;
									break;
								}
							}

							if (!finder)
							{
								wm.k = 128;
							}
							wm.wielkosc = wm.k - wm.poczatek;

							l_wolne.emplace_front(wm);
							l_wolne.erase(itw);
						}

						proces p;
						p.nazwa = n;
						p.wielkosc = w;
						p.start = wm.poczatek - w;
						l_procesow.push_back(p);

						cout << "Dodano proces:  " << n << "  o wielkosci:  " << w << endl;

						wolne -= w;

						po_fragmentacji = false;
					}
					else {
						fragmentacja();
						for (auto e : l_wolne)
						{
							if (e.wielkosc >= w)
								po_fragmentacji = true;
						}

					}
				} while (po_fragmentacji);

				laczenie();
			}
		}
		catch (int) { cout << "\n\tBrak pamieci!" << endl; };
	}


	/*Usuwa proces z listy procesów po czym tworzy blok wolnej pamięci w miejscu usuniętego procesu. Po tym zabiegu następuje łączenie wolnych bloków pamięci w całość.*/
	void usun(string n)
	{
		int s = 0;
		try {
			list<proces>::iterator it;
			bool tn = true;
			for (it = l_procesow.begin(); it != l_procesow.end(); ++it)
			{
				if (it->nazwa == n)
				{
					tn = false;
					break;
				}
			}
			if (tn)
				throw 0;

			wolne += it->wielkosc;
			s = it->wielkosc;
			int sp = it->start;
			cout << "\nUsunieto proces:  " << n << endl;

			wolne_miejsca pom;
			pom.poczatek = sp;
			pom.wielkosc = it->wielkosc;
			pom.k = sp + pom.wielkosc;
			l_wolne.push_front(pom);

			l_procesow.erase(it);
		}
		catch (int) { cout << "\n\tBrak wybranego procesu w pamieci!"; };


		laczenie();
	}


	void zawartosc()
	{
		list<proces>::iterator it;
		int i = 0;
		cout << "\nZawartosc pamieci:  " << endl;
		for (it = l_procesow.begin(); it != l_procesow.end(); ++it)
		{
			cout << it->nazwa << "   " << it->wielkosc << "  Start: " << it->start << endl;
			i++;
		}
		if (i == 0)
			cout << "Brak procesow w pamieci" << endl;
		cout << ">>>>>>>>>>>>>\nPozostalo wolnej pamieci:  " << wolne << endl;
		for (auto e : l_wolne)
		{
			cout << "\tPUSTE: " << e.poczatek << " --> K: " << e.k << "  =  W: " << e.wielkosc << endl;
		}
		cout << "<<<<<<<<<<<<<" << endl;

	}

	void laczenie()
	{
		list<wolne_miejsca>::iterator it, it2, it3;
		int petla = 0;
		bool war = false;

		l_wolne.sort(comp);  // dziala

		do {
			war = false;
			petla = 0;
			for (it = l_wolne.begin(); it != l_wolne.end(); ++it)
			{
				if (petla >= 1)
				{
					if (it->poczatek == it2->k)
					{
						wolne_miejsca wm;
						war = true;
						wm.poczatek = it2->poczatek;
						wm.k = it->k;
						wm.wielkosc = it->wielkosc + it2->wielkosc;

						l_wolne.push_front(wm);

					}
					if (war)
					{
						l_wolne.sort(comp);
						it++;
						l_wolne.erase(it2, it);
					}
				}

				if (war)
					break;
				petla++;

				it2 = it;

			}
		} while (war);


	}

	void fragmentacja()
	{
		cout << "Fragmentacja" << endl;
		list<proces>::iterator it, it2;
		list<wolne_miejsca>::iterator iwm;
		int p = 0, startp = 0;
		bool war = false;
		do {
			p = 0;
			war = false;
			for (it = l_procesow.begin(); it != l_procesow.end(); it++)
			{
				if (p == 0)
				{
					if (it->start != 0)
					{
						proces np;

						np.nazwa = it->nazwa;
						np.wielkosc = it->wielkosc;
						np.start = 1;
						startp = 1;
						l_procesow.emplace(it, np);
						war = true;


						wolne_miejsca wm;
						wm.poczatek = np.start + np.wielkosc;
						wm.wielkosc = it->start - np.start;
						wm.k = wm.poczatek + wm.wielkosc;
						l_wolne.push_back(wm);
						it->start = 1;
					}

				}

				if (p >= 1)
				{
					proces np;
					np.nazwa = it->nazwa;
					np.wielkosc = it->wielkosc;
					np.start = it2->start + it2->wielkosc + 1;
					l_procesow.emplace(it, np);
					war = true;

					wolne_miejsca wm;
					wm.poczatek = np.start + np.wielkosc;
					wm.wielkosc = it->start - np.start;
					wm.k = wm.poczatek + wm.wielkosc;
					l_wolne.push_back(wm);
					it->start = np.start;

				}
				if (war)
					break;
				cout << "\t\t" << it->nazwa;
				it2 = it;
				p++;
			}
			if (war)
			{
				l_procesow.erase(it);
				l_wolne.sort(comp);

				bool ui = false;


				for (iwm = l_wolne.begin(); iwm != l_wolne.end(); iwm++)
				{
					if (iwm->poczatek == startp)
					{
						ui = true;
						break;
					}
				}

				if (ui)
					l_wolne.erase(iwm);

				laczenie();
			}

		} while (!war);

	}
};
