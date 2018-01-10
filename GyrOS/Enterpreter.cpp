#include "Enterpreter.h"
#include "ProcessManagement.h"
#include "Pamiec.h"
#include "Process.h"


Enterpreter::Enterpreter(Pamiec& pam, ProcessManagement& processManager, Filesystem& dysk):
	memory{pam}, processes{processManager}, dysk{dysk}
{ 
//	this->memory = pam;
//	this->processes = processManager;
	//this->dysk = dysk;
}

void Enterpreter::InterpretLine(Process* proc) { 
	std::string currentCommand = memory.odczyt(proc->GetPID(), proc->get_counter());
	cout<< currentCommand <<endl;
	proc->set_counter(proc->get_counter()+1);
	runCommand(currentCommand, proc);
}

void Enterpreter::setRegister(Process& p, const std::string& str, int val)
{
	if (str == "A")
		p.set_A(val);
	else if (str == "B")
		p.set_B(val);
	else if (str == "C")
		p.set_C(val);
	else if (str == "D")
		p.set_D(val);
	else
		parseError(p);
}

int Enterpreter::getRegister(Process& p, const std::string& str, bool& error)
{
	if (str == "A")
		return p.get_A();
	else if (str == "B")
		return p.get_B();
	else if (str == "C")
		return p.get_C();
	else if (str == "D")
		return p.get_D();
	else
		parseError(p);
	return -1;
}

#include <sstream>
void Enterpreter::runCommand(const std::string& command, Process* proc)
{
	Process& reg = *proc;

	std::stringstream com{ command };
	std::string commandLine[5];
	std::string temp;
	for (int i = 0; com >> temp; ++i)
	{
		
		if (temp[0] == '"')
		{
			temp.erase(temp.begin());
			char ch1 = 0;
			char ch2 = 0;
			while (com.get(ch2))
			{
				if (ch2 == '"' && *(temp.end()-1) != '\\')
				{
					break;
				}
				if (ch2 == '"' && *(temp.end()-1)  == '\\')
				{
					temp.erase(temp.end() - 1);
				}
				ch1 = ch2;
				temp += ch2;
			}
		}

		commandLine[i] = temp;
		if (i == 6)
		{
			std::cout << "runCommand: Za dluga komenda.\n";
			parseError(reg);
			return;
		}
	}
	// przenies z rejestru drugiego do pierwszego
	if (commandLine[0] == "MV")
	{
		bool test;
		int num = getRegister(reg, commandLine[2], test);
		if(test) 
			setRegister(reg, commandLine[1], num);
		/*
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
		*/
	}
	// wpisz wartosc do rejestru [1] (z konsoli) WYRZUCIC
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
		/*
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
		*/
		setRegister(reg, commandLine[1], std::stoi(commandLine[2]));
	}
	// dodaj wartosc z [1] do rejestru A, jesli nie ma tam podanego rejestru to jest to liczba
	else if (commandLine[0] == "AD")
	{
		if (commandLine[1] == "A")
		{
			reg.set_A(reg.get_A() + reg.get_A());
		}
		else if (commandLine[1] == "B")
		{
			reg.set_A(reg.get_A() + reg.get_B());
		}
		else if (commandLine[1] == "C")
		{
			reg.set_A(reg.get_A() + reg.get_C());
		}
		else
		{
			reg.set_A(reg.get_A() + std::stoi(commandLine[1]));
		}
	}
	// odejmij wartosc z [1] od rejestru A, jesli nie ma tam podanego rejestru to jest to liczba
	else if (commandLine[0] == "SB")
	{
		if (commandLine[1] == "A")
		{
			reg.set_A(reg.get_A() - reg.get_A());
		}
		else if (commandLine[1] == "B")
		{
			reg.set_A(reg.get_A() - reg.get_B());
		}
		else if (commandLine[1] == "C")
		{
			reg.set_A(reg.get_A() - reg.get_C());
		}
		else
		{
			reg.set_A(reg.get_A() - std::stoi(commandLine[1]));
		}
	}
	// pomnoz wartosc z [1] razy rejestr A, jesli nie ma tam podanego rejestru to jest to liczba
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
			reg.set_A(reg.get_A() * std::stoi(commandLine[1]));
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
		/*
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
		*/
		bool test;
		int num = getRegister(reg, commandLine[1], test);
		if (test)
			std::cout << num;

	}
	// stworz plik - TODO: dodaj z dysku (createFile)
	else if (commandLine[0] == "CF")
	{
		if (!dysk.createFile(commandLine[1]))
			parseError(reg);
	}
	else if (commandLine[0] == "DF")
	{
		if (!dysk.deleteFile(commandLine[1]))
			parseError(reg);
	}
	else if (commandLine[0] == "AA")
	{
		if (!dysk.addFilename(commandLine[1], commandLine[2]))
			parseError(reg);
	}
	else if (commandLine[0] == "SF")
	{
		if (!dysk.changeFilename(commandLine[1], commandLine[2]))
			parseError(reg);
	}
	else if (commandLine[0] == "WF")
	{
		if (!dysk.writeFile(commandLine[1], commandLine[2]))
			parseError(reg);
	}
	else if (commandLine[0] == "AF")
	{
		if (!dysk.appendFile(commandLine[1], commandLine[2]))
			parseError(reg);
	}
	// WR = WRITE REGISTER, napisz do pliku o nazwie [1] wartosc rejestru [2]
	else if (commandLine[0] == "WR")
	{
		bool test;
		int num = getRegister(reg, commandLine[2], test);
		if (test)
			dysk.writeFile(commandLine[1], std::to_string(num));
	}
	// AR = APPEND REGISTER, dopisz do pliku o nazwie [1] wartosc rejestru [2]
	else if (commandLine[0] == "AR")
	{
		bool test;
		int num = getRegister(reg, commandLine[2], test);
		if (test)
			dysk.appendFile(commandLine[1], std::to_string(num));
	}
	// wypisz plik - TODO: dodaj z dysku (printFile), to co teraz tu mamy bedzie APPEND
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
		/*
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
		}*/
		bool test;
		int num = getRegister(reg, commandLine[1], test);
		if (test)
			setRegister(reg, commandLine[1], num + 1);

	}
	// dekrementuj rejestr
	else if (commandLine[0] == "DC")
	{
		/*
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
		*/
		bool test;
		int num = getRegister(reg, commandLine[1], test);
		if (test)
			setRegister(reg, commandLine[1], num - 1);
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
		std::cout << "Koniec programu z procesu " << reg.PID << std::endl;
		processes.ChangeState(reg.name, TERMINATED);
	}
	// TODO Otwieranie pliku FO = FILE OPEN
	else if (commandLine[0] == "FO")
	{
		//otworzplik(commandLine[1]);
	}
	// TODO Zamykanie pliku FC = FILE CLOSE
	else if (commandLine[0] == "FC")
	{

	}
	else {
		parseError(reg);
	}
	return;
}




void Enterpreter::parseError(Process& p)
{
	std::cout << "Blad parsowania. Proces " << p.GetPID() << " zostal przerwany.\n";
	processes.ChangeState(p.name, TERMINATED);
	return;

}

