#include "Pamiec.h"
#include<fstream>
using namespace std;

/// Predykat wykorzystywany podczas ustawiania kolejno bloków wolnej pamięci; ułatwia łączenie sąsiednich bloków w całość 
bool comp(const wolne_miejsca &a, const wolne_miejsca &b)
{
	return a.poczatek < b.poczatek;
}

//void Pamiec::dodaj(int PID, int w, string commands)
void Pamiec::dodaj(int PID, string FileName)
{

	fstream plik;
	string commands, pom;
	plik.open(FileName);

	int w = 0;

	if (plik.is_open())
	{
		while (plik.good())
		{
			getline(plik, pom);
			
			for (int i = 0; i <= pom.length(); i++)
			{
				if(pom[i]!='\n')
				w++;
			}
			commands += pom;
		}
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

					cout << "Dodano proces:  " << PID << "  o wielkosci:  " << w << endl;

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
	catch (int) { cout << "\n\tBrak wybranego procesu w pamieci!"; };


	laczenie();
}
void Pamiec::zawartosc()
{
	list<proces>::iterator it;
	int i = 0, ilosc_w = 0;
	cout << "\nZawartosc pamieci:  " << endl << "[ID]\t[Rozmiar]\t[Adres]\t[Licznik Rozkazu]" << endl;
	for (it = l_procesow.begin(); it != l_procesow.end(); ++it)
	{
		cout << it->PID << "\t " << it->wielkosc << "\t\t " << it->start << "\t " << it->processCounter << endl;
		i++;
	}
	if (i == 0)
		cout << "Brak procesow w pamieci" << endl;
	cout << ">>>>>>>>>>>>>\nPozostalo wolnej pamieci:  "<< endl;
	for (auto e : l_wolne)
	{
		cout << "\tPUSTE: " << e.poczatek << " --> K: " << e.k << "  =  W: " << e.wielkosc << endl;
		ilosc_w += e.wielkosc;
	}
	cout << "Razem:  " << ilosc_w << endl;
	cout << "<<<<<<<<<<<<<" << endl;

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

					np.PID = it->PID;
					np.wielkosc = it->wielkosc;
					np.start = 1;
					np.commands = it->commands;
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
				np.PID = it->PID;
				np.wielkosc = it->wielkosc;
				np.start = it2->start + it2->wielkosc + 1;
				np.commands = it->commands;
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
			cout << "\t\t" << it->PID;
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
void Pamiec::odczyt(int PID)
{
	cout << "Odczytywanie: " << endl;
	list<proces>::iterator it;
	string komendy;
	for (it = l_procesow.begin(); it != l_procesow.end(); it++)
	{
		if (it->PID == PID)
		{
			komendy = it->commands;
			int licz = 0, i, linie=1;
			for (i = 0; i < it->commands.length(); i++)
			{
				if (it->commands[i] == '\n')
				{
				linie++;
				}
			}

			for (i = 0; i < it->commands.length(); i++)
			{
				if (it->commands[i] == '\n')
				{
					licz++;
				}
				if (licz == it->processCounter)
					break;
			}

			if (it->commands[i] == '\n')
				i++;

			
			int kwant = 5, petla = 0;
			for (int j = i; j <= it->commands.length(); j++)
			{
				if (j == it->commands.length())
					break;

				if (petla < kwant)
				{
					if (komendy[j] == '\n')
					{
						it->processCounter++;
						petla++;
					}
					cout << komendy[j];

				}
				else break;
			}
			if (it->processCounter == linie-1)
				it->processCounter = 0;
		}
	}
	cout << "\n\n";
}
