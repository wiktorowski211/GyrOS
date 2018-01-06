#include "ProcessManagement.h"

Process::Process(int ID, Process* father, std::string processName, std::string commands) //konstruktor procesu;
{
	processState = 0;
	PID = ID;
	parent = father;
	//ram->WriteToMemory(ID, commands);
	name = processName;
}

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
			return FindProcess(ID, process); //wykonaj rekurencje
		}
		return nullptr;
	}
}

int ProcessManagement::FindFreeID()
{
	freeID++;
	return freeID;
}

void ProcessManagement::AddProcess(std::string processName, std::string commands, int parentID)
{
	Process* temp = FindProcess(parentID, init);
	Process* virgin = new Process(FindFreeID(), temp, processName, commands); //tworzenie procesu
	freeID++;
	temp->children.push_back(virgin); //dodawanie do listy potomków dla rodzimego procesu
}

void ProcessManagement::KillProcess(int ID)
{
	Process* temp = FindProcess(ID, init);
	int i = 0;
	if (temp->children[i])
	{
		for each (Process* process in temp->children)
		{
			process->parent = init;
		}
	}
	delete temp;
}

void ProcessManagement::ChangeState(int ID, int newstate)
{
	Process* temp = FindProcess(ID, init);
	temp->processState = newstate; //szukanie w drzewie procesu i zmiana jego stanu
	if (newstate == 1) //je¿eli stan procesu ustawiany jest na ready to:
	{
		readyProcesses.push_back(temp); //dodawanie procesu do kolejki gotowych procesów
	}
}

void ProcessManagement::PrintProcess(int ID)
{
	Process* temp = FindProcess(ID, init);
	std::cout << "Process " << temp->PID << ": with parent ID " << temp->parent << std::endl;
}

void ProcessManagement::PrintAllProcesses()
{
	for (int i = 0; i < freeID; i++)
	{
		Process* temp = FindProcess(i, init);

		if (temp)
		{
			std::cout << "Process " << temp->PID << ": with parent ID " << temp->parent << std::endl;
		}
	}
}