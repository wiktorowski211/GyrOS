#include "ProcessManagement.h"

Process::Process(int ID, Process* father, std::string processName, std::string commands) //konstruktor procesu;
{
	processState = 0;
	processBlocked = false;
	PID = ID;
	parent = father;
	ram->WriteToMemory(ID, commands);
	name = processName;
}

ProcessManagement::ProcessManagement()
{
	init = new Process(freeID, nullptr, "init", NULL);
	freeID++;
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

int ProcessManagement::FindID()
{
	freeID++;
	return freeID;
}

void ProcessManagement::AddProcess(std::string processName, std::string commands, int parentID)
{
	Process* virgin = new Process(FindID(), FindProcess(parentID, init), processName, commands); //tworzenie procesu
	freeID++;
	FindProcess(parentID, init)->children.push_back(virgin); //dodawanie do listy potomków dla rodzimego procesu
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
	std::cout << "Process " << FindProcess(ID, init)->PID << ": with parent ID " << FindProcess(ID, init)->parent << std::endl;
}

void ProcessManagement::PrintCurrent(Process* p)
{

}

void ProcessManagement::PrintAllProcesses()
{

}

