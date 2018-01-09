#include "stdafx.h"
#include "Semaphoree.h"


void Semaphore::Wait()
{
	if (value > 0)
		value = value - 1;
	else
	{
		string aktualny_proces = ProcesorM->process->name;
		que.push(aktualny_proces);
		ProcessM->ChangeState(aktualny_proces, 3);
	}
}
void Semaphore::Signal()
{
	if (que.empty() == false)
	{
		string procesName = que.front();
		ProcessM->ChangeState(procesName, 1);
		que.pop();
	}
	else
	{
		value++;
	}
}
Semaphore SemaphoreFactory::CreateSemaphore(int k)
{
		return Semaphore{ k, ProcesorM,ProcessM };	
}
