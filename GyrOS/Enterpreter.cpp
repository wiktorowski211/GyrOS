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
	}
	// wpisz wartosc do rejestru [1] z argumentu [2]
	else if (commandLine[0] == "MI")
	{
		if (commandLine[2] != "" && isdigit(commandLine[2][0]))
			setRegister(reg, commandLine[1], std::stoi(commandLine[2]));
		else
			parseError(reg);
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
		else if (commandLine[1] != "" && isdigit(commandLine[1][0]))
		{
			reg.set_A(reg.get_A() + std::stoi(commandLine[1]));
		}
		else
		{
			parseError(reg);
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
		else if (commandLine[1] != "" && isdigit(commandLine[1][0]))
		{
			reg.set_A(reg.get_A() - std::stoi(commandLine[1]));
		}
		else
		{
			parseError(reg);
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
		else if (commandLine[1] == "D")
		{
			reg.set_A(reg.get_A() * reg.get_D());
		}
		else
		{
			if (commandLine[1] != "" && isdigit(commandLine[1][0]))
				reg.set_A(reg.get_A() * std::stoi(commandLine[1]));
			else
				parseError(reg);
		}
	}
	// jesli C nie jest zero skocz
	else if (commandLine[0] == "JC")
	{
		if(commandLine[1] != "" && isdigit(commandLine[1][0]))
			if (reg.get_C() != 0)
				reg.set_counter(std::stoi(commandLine[1]));
			else;
		else
			parseError(reg);
	}
	// jesli C jest zero skocz
	else if (commandLine[0] == "JZ")
	{
		if (commandLine[1] != "" && isdigit(commandLine[1][0]))
			if (reg.get_C() == 0)
				reg.set_counter(std::stoi(commandLine[1]));
			else;
		else
				parseError(reg);
	}
	// jesli C jest ujemne skocz
	else if (commandLine[0] == "JL")
	{
		if (commandLine[1] != "" && isdigit(commandLine[1][0]))
			if((reg.get_C() < 0))
				reg.set_counter(std::stoi(commandLine[1]));
			else;
		else
			parseError(reg);
	}
	// skok bezwarunkowy
	else if (commandLine[0] == "JP")
	{
		if (commandLine[1] != "" && isdigit(commandLine[1][0]))
			reg.set_counter(std::stoi(commandLine[1]));
		else
			parseError(reg);
	}
	// jesli C jest dodatnie
	else if (commandLine[0] == "JM")
	{
		if (commandLine[1] != "" && isdigit(commandLine[1][0]))
			if(reg.get_C() > 0)
				reg.set_counter(std::stoi(commandLine[1]));
			else;
		else
			parseError(reg);
	}
	// wypisz rejestr [1]
	else if (commandLine[0] == "PR")
	{
		bool test;
		int num = getRegister(reg, commandLine[1], test);
		if (test)
			std::cout << num << std::endl;

	}
	// stworz plik - TODO: dodaj z dysku (createFile)
	else if (commandLine[0] == "CF")
	{
		if (commandLine[1] == "")
		{
			parseError(reg);
			return;
		}
		if (!dysk.createFile(commandLine[1]))
			parseError(reg);
	} // DELETE FILE
	else if (commandLine[0] == "DF")
	{
		if (!dysk.deleteFile(commandLine[1]))
			parseError(reg);
	} // ANOTHER ALIAS 
	else if (commandLine[0] == "AA")
	{
		if (commandLine[1] == "" || commandLine[2] == "")
		{
			parseError(reg);
			return;
		}
		if (!dysk.addFilename(commandLine[1], commandLine[2]))
			parseError(reg);
	} // SWITCH FILENAME
	else if (commandLine[0] == "SF")
	{
		if (commandLine[1] == "" || commandLine[2] == "")
		{
			parseError(reg);
			return;
		}
		if (!dysk.changeFilename(commandLine[1], commandLine[2]))
			parseError(reg);
	} // WRITE FILE
	else if (commandLine[0] == "WF")
	{
		if (!dysk.writeFile(commandLine[1], commandLine[2]))
			parseError(reg);
	} // APPEND FILE
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
	// inkrementuj rejestr
	else if (commandLine[0] == "IC")
	{
		bool test;
		int num = getRegister(reg, commandLine[1], test);
		if (test)
			setRegister(reg, commandLine[1], num + 1);

	}
	// dekrementuj rejestr
	else if (commandLine[0] == "DC")
	{
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
	else if (commandLine[0] == "CC")
	{
		processes.ChangeState(reg.name, WAITING);
		processes.AddProcess("dziecko", "silnia.txt", reg.PID);
		Process* proc = reg.children[reg.children.size() - 1];
		communication.SocketPair(reg, *proc);
	}
	//wyslij wiadomosc
	else if (commandLine[0] == "SM")
	{

	}
	//odbierz wiadomosc
	else if (commandLine[0] == "RM")
	{

	}
	else if (commandLine[0] == "NP")
	{
		// nic
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

