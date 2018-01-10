#include "Semaphoree.h"
#include "ProcessManagement.h"

Semaphore::Semaphore(int k, ProcessManagement *procesik)
{
	value = k;
	ProcessM = procesik;
}
bool Semaphore::Wait()
{
	if (value > 0)
	{
	value = value - 1;
	return true;//wszedł
	}
		
	else
	{
		string aktualny_proces = ProcessM->scheduler->GetProcess()->name;
		que.push(aktualny_proces);
		ProcessM->ChangeState(aktualny_proces, 3);
		//ProcessM->scheduler->GetProcess()->programCounter++;
		return false;//nie wszedł
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
