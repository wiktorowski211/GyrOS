#include "ProcessManagement.h"

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
		Process* p = FindProcess(processName, init);
		while (FindProcess(processName, init))
		{
			processName = processName + "_" + std::to_string(id);
		}

		std::cout << "Stworzenie procesu o id: " << id << " o nazwie " << processName << ".\n";
		temp->children.emplace_back(new Process(id, temp, processName, commands)); //dodawanie do listy potomków dla rodzimego procesu
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
			temp->parent->children.erase(it);
			return;
		}
	}
	std::cout << "There's no that process!\n";
}

void ProcessManagement::ChangeState(std::string name, int newstate)
{
	Process* temp = FindProcess(name, init);
	temp->processState = newstate; //szukanie w drzewie procesu i zmiana jego stanu
	if (newstate == 1) //je¿eli stan procesu ustawiany jest na ready to:
	{
		readyProcesses.push_back(temp); //dodawanie procesu do kolejki gotowych procesów
	}
}

void ProcessManagement::PrintProcess(std::string name)
{
	Process* temp = FindProcess(name, init);
	std::cout << "Process " << temp->PID << ": with parent ID " << temp->parent->PID << std::endl;
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
}

