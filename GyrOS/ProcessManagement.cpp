#include "ProcessManagement.h"

void Process::set_A(int a){ regA = a; }
void Process::set_B(int b){ regB = b; }
void Process::set_C(int c){ regC = c; }
void Process::set_D(int d){ regD = d; }
int Process::get_A(){ return regA; }
int Process::get_B(){ return regB; }
int Process::get_C(){ return regC; }
int Process::get_D(){ return regD; }

void Process::set_counter(int counter){ programCounter = counter; }
int Process::get_counter(){ return programCounter; }

Process* ProcessManagement::FindProcess(int ID, Process* init)
{
	if (init->PID == ID) //je¿eli ID procesu siê zgadza z szukanym
	{
		return init; //koniec rekurencji, zwraca znaleziony proces w postaci wskaŸnika
	}
	else
	{
		for each (Process* process in init->children)
		{
			Process* notnullptr = FindProcess(ID, process); //wykonaj rekurencje
			if (notnullptr)
			{
				return notnullptr;
			}
		}
		return nullptr;
	}
} //funkcja przeszukuj¹ca drzewo procesów 

Process* ProcessManagement::FindProcess(std::string name, Process* init)
{
	if (init->name == name) //je¿eli nazwa procesu siê zgadza z szukanym
	{
		return init; //koniec rekurencji, zwraca znaleziony proces w postaci wskaŸnika
	}
	else
	{
		for each (Process* process in init->children)
		{
			Process* notnullptr = FindProcess(name, process); //wykonaj rekurencje
			if (notnullptr)
			{
				return notnullptr;
			}
		}
		return nullptr;
	}
} //funkcja przeszukuj¹ca drzewo procesów 


int ProcessManagement::FindFreeID()
{
	int a = freeID;
	freeID++;
	return a;
}
//wybieranie wolnego ID

void ProcessManagement::AddProcess(std::string processName, std::string commands, int parentID)
{
	Process* temp = FindProcess(parentID, init);
	if (temp == nullptr)
	{
		std::cout << "Wrong parent ID" << std::endl;
	}
	else
	{
		int id = FindFreeID();

		while (FindProcess(processName, init))
		{
			processName = processName + "_" + std::to_string(id);
		}
		temp->children.emplace_back(new Process(id, temp, processName, commands)); //dodawanie do listy potomków dla rodzimego procesu

		flag_writing_to_memory = MemoryManagement->dodaj(id, commands);
		if (flag_writing_to_memory == 1)
		{
			flag_writing_to_memory = 0;
			KillProcess(processName);
			std::cout << "There's no enough memory to create process " << processName << std::endl;
			return;
		}
		else if (flag_writing_to_memory == 2)	
		{
			flag_writing_to_memory = 0;
			KillProcess(processName);
			std::cout << "There's nothing in file with commands " << processName << std::endl;
			return;
		}
		else if (flag_writing_to_memory == 3)
		{
			flag_writing_to_memory = 0;
			KillProcess(processName);
			std::cout << "There's no file like that " << processName << std::endl;
			return;
		}
		std::cout << "New process with ID " << id << " and name " << processName << ".\n";
		ChangeState(processName, READY);
	}
}


void ProcessManagement::KillProcess(std::string name)
{
	Process* temp = FindProcess(name, init);
	if (!temp)
	{
		std::cout << "Can't find that process\n";
		return;
	}

	if (temp == init) {
		std::cout << "You cannot delete init process!" << std::endl;
		return;
	}

	for each (Process* process in temp->children)
	{
		process->parent = init;
		init->children.push_back(process);
	}
	auto it = temp->parent->children.begin();
	for (auto it = temp->parent->children.begin(); it != temp->parent->children.end(); it++)
	{
		if ((*it)->name == name)
		{
			scheduler->DeleteProcess(temp);// to dodaje marcin!!
			temp->parent->children.erase(it);
			if (flag_writing_to_memory == 1 || flag_writing_to_memory == 2 || flag_writing_to_memory == 3)
			{
				
				MemoryManagement->usun(temp->PID);
			}
			else
			{
				flag_writing_to_memory = 0;
			}
			std::cout << "Process " << name << " has been deleted!" << std::endl;
			return;
		}
	}
	std::cout << "There's no that process!\n";
}

void ProcessManagement::ChangeState(std::string name, int newstate)
{
	Process* temp = FindProcess(name, init);
	if (!temp)
		std::cout << "ChangeState: There's no process like this.\n";
	temp->processState = newstate; //szukanie w drzewie procesu i zmiana jego stanu
	if (newstate == READY) //je¿eli stan procesu ustawiany jest na ready to:
	{
		scheduler->AddProcess(temp); //dodawanie procesu do kolejki gotowych procesów
	}
	else if (newstate == TERMINATED) //je¿eli stan procesu ustawiany jest na ready to:
	{
		KillProcess(name);
	}
	else if (newstate == WAITING)
	{
		scheduler->DeleteProcess();
		int counter = temp->get_counter();
		if (counter > 0)
		{
			counter--;
			temp->set_counter(counter);
		}
	}
}

void ProcessManagement::PrintProcess(std::string name)
{
	Process* temp = FindProcess(name, init);
	if (!temp)
	{
		std::cout << "Can't find that process\n";
		return;
	}
	std::cout << "Process " << temp->PID << ": with parent ID " << temp->parent->PID << ", state: "<< temp->GetProcessState() << ", with registers:\n";
	std::cout << "Registery A: " << temp->get_A() << std::endl;
	std::cout << "Registery B: " << temp->get_B() << std::endl;
	std::cout << "Registery C: " << temp->get_C() << std::endl;
	std::cout << "Registery D: " << temp->get_D() << std::endl;
}

void ProcessManagement::PrintAllProcesses()
{
	for (int i = 0; i < freeID; i++)
	{
		Process* temp = FindProcess(i, init);

		if (temp)
		{
			if (temp->parent == nullptr)
			{
				std::cout << "Process " << temp->name << " id ID " << temp->PID << std::endl;
			}
			else
			{
				std::cout << "Process " << temp->name << " id ID " << temp->PID << " with parent ID " << temp->parent->PID << " has a state: " << temp->processState << std::endl;
			}
		}
	}
	MemoryManagement->zawartosc();
}

