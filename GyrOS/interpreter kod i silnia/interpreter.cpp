#include<iostream>
#include<string>
#include<fstream>

using namespace std;

class Registry
{
	int counter = 0;
	short int registerA;
	short int registerB;
	short int registerC;
public:
	Registry()
	{
		registerA = 0; //akumulator
		registerB = 1; //rejestr B
		registerC = 0; //rejestr C - na podstawie tego rozkazu zachodza (lub nie) skoki
		counter = 0; //adres rozkazu, ktory bedzie wykonywany
	}

	short int get_A();
	short int get_B();
	short int get_C();

	void set_A(short int);
	void set_B(short int);
	void set_C(short int);

	int get_counter();
	void set_counter(int);
};

short int Registry::get_A()
{
	return registerA;
}

short int Registry::get_B()
{
	return registerB;
}

short int Registry::get_C()
{
	return registerC;
}

void Registry::set_A(short int v)
{
	registerA = v;
}

void Registry::set_B(short int v)
{
	registerB = v;
}

void Registry::set_C(short int v)
{
	registerC = v;
}

int Registry::get_counter()
{
	return counter;
}

void Registry::set_counter(int v)
{
	counter = v;
}


void readFile(string myArray[])
{
	using namespace std;

	ifstream file("silnia.txt");
	if (file.is_open())
	{

		for (int i = 0; i < 30; ++i)
		{
			getline(file, myArray[i]);
			//cout << myArray[i] << endl;
		}
	}
	file.close();
}

void readFile(string myArray[], string fileName)
{
	using namespace std;

	ifstream file(fileName);
	if (file.is_open())
	{

		for (int i = 0; i < 30; ++i)
		{
			getline(file, myArray[i]);
			//cout << myArray[i] << endl;
		}
	}
	file.close();
}

string* split(string toSplit)
{
	string* splitted = new string[5];
	short counter = 0;
	for (short i = 0; i<toSplit.length(); i++) {
		if (toSplit[i] == ' ')
			counter++;
		else
			splitted[counter] += toSplit[i];
	}
	return splitted;
}

void runCommand(string command, Registry &reg)
{
	string *commandLine = split(command);
	cout << commandLine[0] << " " << commandLine[1] <<" "<< commandLine[2] << endl;

	reg.set_counter(reg.get_counter() + 6);

	if (commandLine[0] == "MV")
	{
		if (commandLine[1] == "A")
		{
			if (commandLine[2] == "B")
			{
				reg.set_A(reg.get_B());
			}
			else if (commandLine[2] == "C")
			{
				reg.set_A(reg.get_C());
			}
		}
		else if (commandLine[1] == "B")
		{
			if(commandLine[2] == "A")
			{
				reg.set_B(reg.get_A());
			}
			else if (commandLine[2] == "C")
			{
				reg.set_B(reg.get_C());
			}
		}
		else if (commandLine[1] == "C")
		{
			if (commandLine[2] == "A")
			{
				reg.set_C(reg.get_A());
			}
			else if (commandLine[2] == "B")
			{
				reg.set_C(reg.get_B());
			}
		}
	}
	else if (commandLine[0] == "RD")
	{
		if (commandLine[1] == "A")
		{
			short int val;
			cout << "Wpisz wartosc do rej. A: "; cin >> val;
			cin.ignore();
			reg.set_A(val);
		}
		else if (commandLine[1] == "B")
		{
			short int val;
			cout << "Wpisz wartosc do rej. B: "; cin >> val;
			cin.ignore();
			reg.set_B(val);
		}
		else if (commandLine[1] == "C")
		{
			short int val;
			cout << "Wpisz wartosc do rej. C: "; cin >> val;
			cin.ignore();
			reg.set_C(val);
		}
	}
	else if (commandLine[0] == "MI")
	{
		if (commandLine[1] == "A")
		{
			reg.set_A(stoi(commandLine[2]));
		}
		else if (commandLine[1] == "B")
		{
			reg.set_B(stoi(commandLine[2]));
		}
		else if (commandLine[1] == "C")
		{
			reg.set_C(stoi(commandLine[2]));
		}
	}
	else if (commandLine[0] == "AD")
	{
		if (commandLine[1] == "A")
		{
			reg.set_A(reg.get_A() + reg.get_A());
		}
		else if (commandLine[1] == "B")
		{
			reg.set_B(reg.get_A() + reg.get_B());
		}
		else if (commandLine[1] == "C")
		{
			reg.set_C(reg.get_A() + reg.get_C());
		}
		else
		{
			reg.set_A(reg.get_A() + stoi(commandLine[2]));
		}
	}
	else if (commandLine[0] == "SB")
	{
		if (commandLine[1] == "A")
		{
			reg.set_A(reg.get_A() - reg.get_A());
		}
		else if (commandLine[1] == "B")
		{
			reg.set_B(reg.get_A() - reg.get_B());
		}
		else if (commandLine[1] == "C")
		{
			reg.set_C(reg.get_A() - reg.get_C());
		}
		else
		{
			reg.set_A(reg.get_A() - stoi(commandLine[2]));
		}
	}
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
		else
		{
			reg.set_A(reg.get_A() * stoi(commandLine[2]));
		}
	}
	else if (commandLine[0] == "JC")
	{
		if(reg.get_C()!=0)
		reg.set_counter(stoi(commandLine[1]));
	}
	else if (commandLine[0] == "JZ")
	{
		if (reg.get_C() == 0)
			reg.set_counter(stoi(commandLine[1]));
	}
	else if (commandLine[0] == "JL")
	{
		if (reg.get_C() < 0)
			reg.set_counter(stoi(commandLine[1]));
	}
	else if (commandLine[0] == "JP")
	{
			reg.set_counter(stoi(commandLine[1]));
	}
	else if (commandLine[0] == "JM")
	{
		if (reg.get_C() > 0)
			reg.set_counter(stoi(commandLine[1]));
	}
	else if (commandLine[0] == "PR")
	{
		if (commandLine[1] == "A")
		{
			cout << reg.get_A();
		}
		else if (commandLine[1] == "B")
		{
			cout << reg.get_B();
		}
		else if (commandLine[1] == "C")
		{
			cout << reg.get_C();
		}
	}
	else if (commandLine[0] == "CF")
	{
		cout << "Tworzenie pliku wyjsciowego o nazwie: wynik.txt" << endl;
		{
			fstream plik;
			plik.open("wynik.txt", ios::out);
			plik.close();
		}
	}
	else if (commandLine[0] == "PF")
	{
		if (commandLine[1] == "A")
		{
			fstream plik;
			plik.open("wynik.txt", ios::app);
			plik << reg.get_A();
			plik.close();
		}
		else if (commandLine[1] == "B")
		{
			fstream plik;
			plik.open("wynik.txt", ios::app);
			plik << reg.get_B();
			plik.close();
		}
		else if (commandLine[1] == "C")
		{
			fstream plik;
			plik.open("wynik.txt", ios::app);
			plik << reg.get_C();
			plik.close();
		}
		else
		{
			fstream plik;
			plik.open("wynik.txt", ios::app);
			plik << (char)stoi(commandLine[1]);
			plik.close();
		}
	}
	else if (commandLine[0] == "IC")
	{
		if (commandLine[1] == "A")
		{
			reg.set_A(reg.get_A() + 1);
		}
		else if (commandLine[1] == "B")
		{
			reg.set_B(reg.get_A() + 1);
		}
		else if (commandLine[1] == "C")
		{
			reg.set_C(reg.get_A() + 1);
		}
	}
	else if (commandLine[0] == "DC")
	{
		if (commandLine[1] == "A")
		{
			reg.set_A(reg.get_A() - 1);
		}
		else if (commandLine[1] == "B")
		{
			reg.set_B(reg.get_B() - 1);
		}
		else if (commandLine[1] == "C")
		{
			reg.set_C(reg.get_C() - 1);
		}
	}
	else if (commandLine[0] == "FK")
	{
		//funkcja tworzenia procesu o nazwie commandLine[1]
	}
	else if (commandLine[0] == "WT")
	{
		//funkcja wstrzymania procesu o nazwie commandLine[1]
	}
	else if (commandLine[0] == "SE")
	{
		//komunikacja miedzy procesowa
	}
	else if (commandLine[0] == "KL")
	{
		//zabicie procesu o PID stoi(commandLine[1])
	}
	else if (commandLine[0] == "EX")
	{
		reg.set_counter(92);
		cout << "Koniec programu ";
	}
	else if (commandLine[0] == "OF")
	{
		//otworzplik(commandLine[1]);
	}
}

void runProgram(string program[], Registry &reg)
{
	string command;
	while (reg.get_counter() != 92)
	{
		command = program[reg.get_counter() / 6];
		runCommand(command, reg);
	}
}

//int main()
//{
//	Registry reg;
//	string program[30];
//	readFile(program);
//	runProgram(program,reg);
//	//cout << program[4];
//	system("pause");
//	return 0;
//}

