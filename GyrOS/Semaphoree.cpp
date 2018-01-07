#include <iostream>
#include <queue>
#include "ProcessManagement.h"
#include "ProcesorManager.h"
#include "Semaphoree.h"
using namespace std;

class Semaphore//Semafor pracuje na ID procesow
{
	int value;
	queue<int> que;//Kolejka FIFO
	void Wait()
	{
		if (value > 0)
			value -= 1;
		else
		
		{
			int aktualny_proces = procesorManager.process->PID;
			que.push(aktualny_proces);
			processManager.ChangeState(aktualny_proces, 3);
			
		}
	}
	void Signal()
	{
		if (que.empty() == false)
		{
			int procesID = que.front();
			processManager.ChangeState(procesID, 1);
			que.pop();
		}
		else
		{
			value++;
		}
	}
	Semaphore(int k)
	{
		value = k;
	}
};
