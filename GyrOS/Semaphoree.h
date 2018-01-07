#pragma once
extern Scheduler procesorManager;//potrzebny globalnie zadeklarowany obiekt schedulera
extern ProcessManagement processManager;//potrzebny globalnie zadeklarowany obiekt ProcessManagament
class  Semaphore
{
public:
	Semaphore(int k) {};
	void Signal();
	void Wait();

};

