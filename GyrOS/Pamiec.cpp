#include "Pamiec.h"
#include<fstream>
using namespace std;

/// Predykat wykorzystywany podczas ustawiania kolejno bloków wolnej pamięci; ułatwia łączenie sąsiednich bloków w całość 
bool comp(const wolne_miejsca &a, const wolne_miejsca &b)
{
	return a.poczatek < b.poczatek;
}

bool comp2(const proces &a, const proces &b)
{
	return a.start < b.start;
}

//void Pamiec::dodaj(int PID, int w, string commands)
int Pamiec::dodaj(int PID, string FileName)
{

	fstream plik;
	string commands, pom, com[128];

	plik.open(FileName);

	int w = 0, licznik = 0;

	if (plik.is_open())
	{
		while (plik.good())
		{
			getline(plik, pom);
			com[licznik] = pom;
			licznik++;
			
			for (int i = 0; i <= pom.length(); i++)
			{
				if (pom[i] != '\n')
					w++;
			}
			commands += pom;
			commands += '\n';
		}
	}
	else
	{
		//cout << "\n\tBlad! Brak podanego pliku.";
		return 2;
	}

	cout << "kom:" << commands << "k\n";

	bool pusty = true;
	for (int i = 0; i < commands.length(); i++)
	{
		if (commands[i] != ' ' && commands[i]!='\n')
		{
			pusty = false;
			break;
		}	
	}

	if (pusty)
	{
		//cout << "\tPlik jest pusty.";
		return 3;
	} 


	//FSBEM.WAIT();
	/*int linie = 1;
	for (int i = 0; i < commands.length(); i++)
	{
		if (commands[i] == '\n')
		{
			linie++;
		}
	}*/
	//int w = linie; 
	//w = linie;
	


	bool szukaj_miejsca = false, po_fragmentacji = false;

	try {
		if (wolne < w || wolne <=2)
		{
			
			//MemSem.Wait();
			throw 0;
			return 1;
		}

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
						l_wolne.pop_back();
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
						if(wm.wielkosc>0)
						l_wolne.emplace_front(wm);

						l_wolne.erase(itw);
					}

					proces p;
					p.PID = PID;
					p.wielkosc = w;
					p.commands = commands;
					p.start = wm.poczatek - w;
					l_procesow.push_back(p);


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

			return 0;
		}
	}
	catch (int) { return 1; };
	//FSBSEM.SIGNAL();
}
void Pamiec::usun(int pid)
{
	int s = 0;
	try {
		list<proces>::iterator it;
		bool tn = true;
		for (it = l_procesow.begin(); it != l_procesow.end(); ++it)
		{
			if (it->PID == pid)
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
		//	cout << "\nUsunieto proces:  " << pid << endl;

		wolne_miejsca pom;
		pom.poczatek = sp;
		pom.wielkosc = it->wielkosc;
		pom.k = sp + pom.wielkosc;
		l_wolne.push_front(pom);

		l_procesow.erase(it);

	}
	catch (int) { /*cout << "\n\tBrak wybranego procesu w pamieci!"; */};


	laczenie();
}

void Pamiec::zawartosc()
{
	list<proces>::iterator it;
	int i = 0, ilosc_w = 0;
	cout << "\nZawartosc pamieci:  " << endl << "[ID]\t[Rozmiar]\t[Adres]\t[Koniec]\t[Licznik Rozkazu]" << endl;
	for (it = l_procesow.begin(); it != l_procesow.end(); ++it)
	{
		cout << it->PID << "\t " << it->wielkosc << "\t\t " << it->start << "\t " << it->start+it->wielkosc << "\t\t " << it->MemoryPointer << endl;
		i++;
	}
	if (i == 0)
		cout << "Brak procesow w pamieci" << endl;
	cout << "\nPozostalo wolnej pamieci:  " << endl;
	for (auto e : l_wolne)
	{
		cout << "\tStart: " << e.poczatek << " --> End: " << e.k << "  =  Size: " << e.wielkosc << endl;
		ilosc_w += e.wielkosc;
	}
	cout << "Razem:  " << ilosc_w << endl;
	cout << "" << endl;

}

void Pamiec::laczenie()
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
void Pamiec::fragmentacja()
{
	list<proces>::iterator it;
	list<wolne_miejsca>::iterator iwm;
	int petla = 0;
	proces pp;

	l_procesow.sort(comp2);

	for (it = l_procesow.begin(); it != l_procesow.end(); ++it)
	{
		if (petla == 0)
		{
			it->start = 1;
		}
		else
		{
			it->start = pp.start + pp.wielkosc + 1;
		}

		pp = *it;

		petla++;
	}

	l_wolne.clear();
	wolne_miejsca wm;
	wm.poczatek = pp.start + pp.wielkosc + 1;
	wm.k = 128;
	wm.wielkosc = wm.k - wm.poczatek;

	l_wolne.push_back(wm);
}
string Pamiec::odczyt(int PID, int counter)
{
	//cout << "Odczytywanie: " << endl;
	list<proces>::iterator it;
	string komendy, zwrot;
	for (it = l_procesow.begin(); it != l_procesow.end(); it++)
	{
		if (it->PID == PID)
		{
			int licz = 0, i, linie = 1;
			/*for (i = 0; i < it->commands.length(); i++)
			{
				if (it->commands[i] == '\n')
				{
					linie++;
				}
			}*/	
			for (i = 0; i < it->commands.length(); i++)
			{
				if (it->commands[i] == '\n')
				{
					licz++;
				}
				if (licz == counter)
					break;
			}

			if (it->commands[i] == ';')
				i++;


			int kwant = 5, petla = 0;
			for (int j = i; j <= it->commands.length(); j++)
			{
				if (j == it->commands.length())
					break;

				if (it->commands[j] != ';')
				{
					it->MemoryPointer++;
					zwrot += it->commands[j];
				}
				else
					break;

			}
			/*if (it->processCounter == linie - 1)
				it->processCounter = 0;*/
			}
		}
		return zwrot;
}
char Pamiec::odczytznaku(int PID, int place)
{
	list<proces>::iterator it;
	string komendy;
	char znak;
	for (it = l_procesow.begin(); it != l_procesow.end(); it++)
	{
		if (it->PID == PID)
		{
			komendy = it->commands;
		}
	}
	int i;
	for (i = 0; i <= komendy.length(); i++)
	{
		if (i == place)
		{
			break;
		}
			
	}
	return komendy[i];
}
