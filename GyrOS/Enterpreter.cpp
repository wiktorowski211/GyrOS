#include "Enterpreter.h"
#include "ProcessManagement.h"

void Enterpreter::InterpretLine(Process* proc) {//counter jeszcze 
	std::string currentCommand = memory->odczyt(proc->GetPID(), proc->get_counter());
	cout<< currentCommand <<endl;
	proc->set_counter(proc->get_counter()+1);
	runCommand(currentCommand, proc);
}

#include <sstream>
State Enterpreter::runCommand(const std::string& command, Process* proc)
{
	Process& reg = *proc;

	std::stringstream com{ command };
	std::string commandLine[5];
	std::string temp;
	for (int i = 0; com >> temp; ++i)
	{
		commandLine[i] = temp;
		if (i == 6)
		{
			std::cout << "runCommand: Za dluga komenda.\n";
			return parseError(reg);
		}
	}
	// przenies z rejestru drugiego do pierwszego
	if (commandLine[0] == "MV")
	{
		if (commandLine[1] == "A")
		{
			if (commandLine[2] == "B")
			{
				reg.set_A(reg.get_B());
			}
			else if (commandLine[2] == "C")
			{
				reg.set_A(reg.get_C());
			}
		}
		else if (commandLine[1] == "B")
		{
			if (commandLine[2] == "A")
			{
				reg.set_B(reg.get_A());
			}
			else if (commandLine[2] == "C")
			{
				reg.set_B(reg.get_C());
			}
		}
		else if (commandLine[1] == "C")
		{
			if (commandLine[2] == "A")
			{
				reg.set_C(reg.get_A());
			}
			else if (commandLine[2] == "B")
			{
				reg.set_C(reg.get_B());
			}
		}
	}
	// wpisz wartosc do rejestru [1] (z konsoli)
	else if (commandLine[0] == "RD")
	{
		if (commandLine[1] == "A")
		{
			int val;
			cout << "Wpisz wartosc do rej. A: "; cin >> val;
			cin.ignore();
			reg.set_A(val);
		}
		else if (commandLine[1] == "B")
		{
			int val;
			cout << "Wpisz wartosc do rej. B: "; cin >> val;
			cin.ignore();
			reg.set_B(val);
		}
		else if (commandLine[1] == "C")
		{
			int val;
			cout << "Wpisz wartosc do rej. C: "; cin >> val;
			cin.ignore();
			reg.set_C(val);
		}
	}
	// wpisz wartosc do rejestru [1] z argumentu [2]
	else if (commandLine[0] == "MI")
	{
		if (commandLine[1] == "A")
		{
			reg.set_A(std::stoi(commandLine[2]));
		}
		else if (commandLine[1] == "B")
		{
			reg.set_B(std::stoi(commandLine[2]));
		}
		else if (commandLine[1] == "C")
		{
			reg.set_C(std::stoi(commandLine[2]));
		}
	}
	// dodaj do wartosci z [1] wartosc z [2], jesli nie ma tam podanego rejestru to jest to liczba
	else if (commandLine[0] == "AD")
	{
		if (commandLine[1] == "A")
		{
			reg.set_A(reg.get_A() + reg.get_A());
		}
		else if (commandLine[1] == "B")
		{
			reg.set_B(reg.get_A() + reg.get_B());
		}
		else if (commandLine[1] == "C")
		{
			reg.set_C(reg.get_A() + reg.get_C());
		}
		else
		{
			reg.set_A(reg.get_A() + std::stoi(commandLine[2]));
		}
	}
	// dodaj do wartosci z [1] wartosc z [2], jesli nie ma tam podanego rejestru to jest to liczba
	else if (commandLine[0] == "SB")
	{
		if (commandLine[1] == "A")
		{
			reg.set_A(reg.get_A() - reg.get_A());
		}
		else if (commandLine[1] == "B")
		{
			reg.set_B(reg.get_A() - reg.get_B());
		}
		else if (commandLine[1] == "C")
		{
			reg.set_C(reg.get_A() - reg.get_C());
		}
		else
		{
			reg.set_A(reg.get_A() - std::stoi(commandLine[2]));
		}
	}
	// pomnoz wartosc z rejestru [1] wartosc z [2], jesli nie ma tam podanego rejestru to jest to liczba
	else if (commandLine[0] == "MP")
	{
		if (commandLine[1] == "A")
		{
			reg.set_A(reg.get_A() * reg.get_A());
		}
		else if (commandLine[1] == "B")
		{
			reg.set_A(reg.get_A() * reg.get_B());
		}
		else if (commandLine[1] == "C")
		{
			reg.set_A(reg.get_A() * reg.get_C());
		}
		else
		{
			reg.set_A(reg.get_A() * std::stoi(commandLine[2]));
		}
	}
	// jesli C nie jest zero skocz
	else if (commandLine[0] == "JC")
	{
		if (reg.get_C() != 0)
			reg.set_counter(std::stoi(commandLine[1]));
	}
	// jesli C jest zero skocz
	else if (commandLine[0] == "JZ")
	{
		if (reg.get_C() == 0)
			reg.set_counter(std::stoi(commandLine[1]));
	}
	// jesli C jest ujemne skocz
	else if (commandLine[0] == "JL")
	{
		if (reg.get_C() < 0)
			reg.set_counter(std::stoi(commandLine[1]));
	}
	// skok bezwarunkowy
	else if (commandLine[0] == "JP")
	{
		reg.set_counter(std::stoi(commandLine[1]));
	}
	// jesli C jest dodatnie
	else if (commandLine[0] == "JM")
	{
		if (reg.get_C() > 0)
			reg.set_counter(std::stoi(commandLine[1]));
	}
	// wypisz rejestr [1]
	else if (commandLine[0] == "PR")
	{
		if (commandLine[1] == "A")
		{
			cout << reg.get_A();
		}
		else if (commandLine[1] == "B")
		{
			cout << reg.get_B();
		}
		else if (commandLine[1] == "C")
		{
			cout << reg.get_C();
		}
	}
	// stworz plik - TODO: dodaj z dysku (createFile)
	else if (commandLine[0] == "CF")
	{
		cout << "Tworzenie pliku wyjsciowego o nazwie: wynik.txt" << endl;
		{
			fstream plik;
			plik.open("wynik.txt", ios::out);
			plik.close();
		}
	}
	// wypisz plik - TODO: dodaj z dysku (writeFile)
	else if (commandLine[0] == "PF")
	{
		if (commandLine[1] == "A")
		{
			fstream plik;
			plik.open("wynik.txt", ios::app);
			plik << reg.get_A();
			plik.close();
		}
		else if (commandLine[1] == "B")
		{
			fstream plik;
			plik.open("wynik.txt", ios::app);
			plik << reg.get_B();
			plik.close();
		}
		else if (commandLine[1] == "C")
		{
			fstream plik;
			plik.open("wynik.txt", ios::app);
			plik << reg.get_C();
			plik.close();
		}
		else
		{
			fstream plik;
			plik.open("wynik.txt", ios::app);
			plik << (char)stoi(commandLine[1]);
			plik.close();
		}
	}
	// inkrementuj rejestr
	else if (commandLine[0] == "IC")
	{
		if (commandLine[1] == "A")
		{
			reg.set_A(reg.get_A() + 1);
		}
		else if (commandLine[1] == "B")
		{
			reg.set_B(reg.get_A() + 1);
		}
		else if (commandLine[1] == "C")
		{
			reg.set_C(reg.get_A() + 1);
		}
	}
	// dekrementuj rejestr
	else if (commandLine[0] == "DC")
	{
		if (commandLine[1] == "A")
		{
			reg.set_A(reg.get_A() - 1);
		}
		else if (commandLine[1] == "B")
		{
			reg.set_B(reg.get_B() - 1);
		}
		else if (commandLine[1] == "C")
		{
			reg.set_C(reg.get_C() - 1);
		}
	}
	// tworzy proces dziecko TODO
	else if (commandLine[0] == "FK")
	{
		//funkcja tworzenia procesu o nazwie commandLine[1]
	}
	// TODO ??? Filip mowi ze nie ma
	else if (commandLine[0] == "WT")
	{
		//funkcja wstrzymania procesu o nazwie commandLine[1]
	}
	// TODO tutaj trzeba zrobic
	else if (commandLine[0] == "SE")
	{
		//.sendCom(commandLine[1],commandLine[2]);
	}
	// TODO ustaw dziecku terminated
	else if (commandLine[0] == "KL")
	{
		//zabicie procesu o PID stoi(commandLine[1])
	}
	// TODO Bezwarunkowy koniec programu, wymagane
	else if (commandLine[0] == "EX")
	{
		reg.set_counter(92);
		cout << "Koniec programu ";
	}
	// TODO Otwieranie pliku
	else if (commandLine[0] == "OF")
	{
		//otworzplik(commandLine[1]);
	}
	else {

	}
	return RUNNING;
}




State Enterpreter::parseError(Process& p)
{
	std:cout << "Blad parsowania. Proces " << p.GetPID() << " zostal przerwany.\n";

	return TERMINATED;

}

