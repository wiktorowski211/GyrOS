// SO.cpp : Defines the entry point for the console application.
//

#include "Shell.h"
using namespace std;
int main()
{
	Shell powloka = Shell();
	cout << "Symulacja systemu operacyjnego GyrOS\n";
	while (powloka.work)
	{
		cout << "<GyrOS> ";
		string komenda;
		getline(cin, komenda);
		powloka.wydziel_rozkaz(powloka.begin(komenda));
		cout << endl;
	}
	cout << "\nSystem zostal poprawnie zamkniety" << endl;
	return 0;
}

