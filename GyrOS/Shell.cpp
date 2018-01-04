#include "stdafx.h"
#include "Shell.h"
#define test true ////////do testów
#define separator '~'
using namespace std;

void Shell::wydziel_rozkaz(string &kom) {
	int pos = -1;
	bool pom = true;
	string rozkaz, parametry;
	for (int i = 0; i < kom.size(); i++) {
		if (kom[i] != ' ')
		{
			pos++;
		}
		else
		{
			rozkaz = namale(kom.substr(0, pos + 1));

			if(rozkaz=="echo"||rozkaz=="go")
				parametry = kom.substr(pos + 2, kom.size() - pos);
			else
				parametry = end(standard(begin(kom.substr(pos + 2, kom.size() - pos))));

			rozpoznaj_rozkaz(rozkaz, parametry);
			pom = false;
			break;
		}
	}
	if (pom)
	{
		rozkaz = end(standard(namale(kom)));
		parametry = "";
		rozpoznaj_rozkaz(rozkaz, parametry);
	}
	/*cout << "\nKomenda: \"" << rozkaz << "\"";
	cout << "\nParametry: \"" << parametry << "\"";*/
}
void Shell::rozpoznaj_rozkaz(string s1, string s2) {
	switch (rozkaz[s1])
	{
	case 1: {help(); }; break;
	case 2: {cls();  }; break;
	case 3: {del(s2); }; break;
	case 4: {echo(s2); }; break;
	case 5: {ext(); }; break;
	case 6: {type(s2); }; break;
	case 7: {rename(s2); }; break;
	case 8: {start(s2); }; break;
	case 9: {taskkill(s2); }; break;
	case 10: {tasklist(); }; break;
	case 11: {go(s2); }; break;
	case 12: {check(); }; break;
	default: {
		if (s1.size()>4 && s1[s1.size() - 4] == '.' && s1[s1.size() - 3] == 'b' && s1[s1.size() - 2] == 'a' && s1[s1.size() - 1] == 't')
		{
			czytaj_skrypt(s1);
		}
		else
		{
			cout << "\tNiepoprawna komenda.\n";
		}
	}; break;
	}
}
void Shell::help()
{
	czytaj_skrypt("help.bat");
}
void Shell::echo(string &s) {
	if (echo_przekaz(s))
		cout << s << endl;
}
bool Shell::echo_przekaz(string &s) {
	bool tn = true;
	string txt = "", plik = "";
	int pos;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '\'' || s[i] == '\"')
			continue;
		if (s[i] != '>')
			txt += s[i];
		else
		{
			pos = i;
			tn = false;
			if (s[i + 1] == '>')
			{
				if (s[i + 2] == '\"' || s[i + 2] == '\'')
					tn = true;
			}
			else
			{
				if (s[i + 1] == '\"' || s[i + 1] == '\'')
					tn = true;
			}
			break;
		}
	}
	if (!tn)
	{
		if (s[pos + 1] == '>')
		{
			plik = s.substr(pos + 2, s.size() - pos - 2);
			if (plik[0] == ' ')
				plik = plik.substr(1, plik.size() - 1);
			dopisz(txt, plik);
		}
		else
		{
			plik = s.substr(pos + 1, s.size() - pos - 1);
			if (plik[0] == ' ')
				plik = plik.substr(1, plik.size() - 1);
			nadpisz(txt, plik);
		}
	}
	/*cout << endl << "Tekst:" << txt << endl;
	cout << endl << "Docel:" << plik << endl;*/
	return tn;
}
void Shell::nadpisz(string &s, string &p)
{
	cout << "Komenda nadpisz";
	if (test/*writeFile(s, p)*/)
	{
		cout << "\nUtworzono plik: " << p << endl;
	}
	else
	{
		cout << "\nBlad tworzwenia pliku"  << endl;
	}
}
void Shell::dopisz(string &s, string &p)
{
	cout << "Komenda dopisz";
	if (test/*appendFile(s, p)*/)
	{
		cout << "\nDopisano: " << s << " do pliku: " << p << endl;
	}
	else
	{
		cout << "\nBlad otwarcia pliku" << endl;
	}
}
void Shell::cls(){
	system("cls");
}
void Shell::del(string &s)
{
	cout << "Komenda del";
	if (test)
	{
		cout << "\nPlik: " << s << " usunieto" << endl;
	}
	else
	{
		cout << "\nNie udalo sie usunac pliku: " << s << endl;
	}
}
void Shell::ext(){
	kropki("Zamykanie systemu");
	work = false;
}
void Shell::type(string &s)
{
	string plik = "";
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] != separator)
			plik += s[i];
	}
	cout << "Komenda type";
	if (test)
		cout << "\nZawartosc pliku " << plik << ": ";
	else
		cout << "\nBlad otwarcia pliku" << endl;
}
void Shell::rename(string &s)
{
	string stara = "", nowa = "";
	bool n = false;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == separator)
		{
			n = true;
			continue;
		}
		if (!n)
		{
			stara += s[i];
		}
		if (n)
		{
			nowa += s[i];
		}
	}
	if (test)
		cout << "Komenda rename.\nZmiana nazwy pliku: " << stara << " na: " << nowa;
	else
		cout << "Nie udalo sie zmienic nazwy pliku: " << stara;
}
void Shell::start(string &s)//usprawnij tą funkcję o błędy w wyniku złego zapisania
{
	string nazwa = "", kod="", roz="";
	bool ok = true;
	int rozmiar, e=0;
	for(int i = 0; i < s.size(); i++)
	{
		if (s[i] == separator)
		{
			e++;
			continue;
		}
		if (e == 0)
		{
			nazwa += s[i];
		}
		if (e == 1)
		{
			if(nazwa!="")
				roz += s[i];
			else
			{
				ok = false;
				break;
			}
		}
		if (e == 2)
		{
			if(roz!="")
				kod += s[i];
			else
			{
				ok = false;
				break;
			}
		}
	}
	if (kod == "")
		ok = false;
	for (int j = 0; j < roz.size(); j++)
	{
		if (int(roz[j])< 48 || int(roz[j])>57)
		{
			ok = false;
			break;
		}
	}
	if (ok)
	{
		rozmiar = stoi(roz);
		cout << "Komenda start.\nStworzono proces: " << nazwa << " o rozmiarze : " << rozmiar << " i kodzie zrodlowym z pliku: " << kod;
	}
	else
	{
		cout << "\tNiepoprawna komenda.\n";
	}
	
	//AddProcess(s);
}
void Shell::taskkill(string &s)
{
	string nazwa = "";
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] != separator)
			nazwa += s[i];
	}
	cout << "Komenda taskkill.\nZabicie procesu o nazwie: " << nazwa;
	//KillProcess();
}
void Shell::tasklist()
{
	cout << "Komenda tasklist";
	//PrintAllProcess();
}
void Shell::go(string &s)
{
	cout << "Komenda go";
}
void Shell::check()
{
	cout << "\nStan systemu: ";
}
void Shell::czytaj_skrypt(string s)
{
	string  tekst;
	ifstream plik;
	plik.open(s);
	if (plik.is_open())
	{
		while (plik.good())
		{
			getline(plik, tekst);
			if (tekst != "");
			wydziel_rozkaz(tekst);
		}
	}
	else {
		cout << "\n\tNie znaleziono wskazanego pliku";
	}
}
string Shell::namale(string &s)
{
	string male = "";
	int pom = 0;
	for (int i = 0; i < s.size(); i++)
	{
		if (int(s[i]) >= 65 && int(s[i]) <= 90)
		{
			male += char(int(s[i]) + 32);
		}
		else
		{
			male += s[i];
		}
	}
	return male;
}
string Shell::standard(string &s)
{
	int pom = 0;
	string s2 = "";
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] != ' ')
		{
			pom = 0;
			s2 += s[i];
		}
		else
		{
			pom++;
		}
		if (pom == 1)
		{
			s2 += separator;
		}
	}
	//cout << endl << "Standard: \"" << s2 << "\"";
	return s2;
}
string Shell::begin(string &s)
{
	string kom = "";
	bool pom = true;
	if (s[0] == ' ')
	{
		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] != ' ')
			{
				pom = false;
			}
			if (!pom)
			{
				kom += s[i];
			}
		}
	}
	else
		kom = s;
	
	//cout << endl << "BEGIN: \"" << kom << "\"";
	return kom;
}
string Shell::end(string &s)
{
	string kom = "";
	bool pom = true;
	int z = s.size();
	if ((z-1) > 0)
	{
		if (s[s.size() - 1] == separator)
		{
			for (int i = s.size() - 1; i >= 0; i--)
			{
				if (s[i] != separator)
				{
					pom = false;
				}
				if (!pom)
				{
					kom = s[i] + kom;
				}
			}
		}
		else
			kom = s;
		/*cout << endl << "END: \"" << kom << "\"";*/
	}
	
	return kom;
}
void Shell::kropki(string s)
{
	int pom = 0, i=15;
	while (i)
	{
		pom++;
		if (pom>3)
			pom = pom - 3;

		if (pom == 1)
		{
			cout << s << ".";
			Sleep(300); system("cls");
		}
		if (pom == 2)
		{
			cout << s << "..";
			Sleep(300); system("cls");
		}
		if (pom == 3)
		{
			cout << s << "...";
			Sleep(300); system("cls");
		}
		i--;
	}
}
