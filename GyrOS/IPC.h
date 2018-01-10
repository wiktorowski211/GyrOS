#pragma once
#include "Process.h"

#include <string>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Socket {

	string temporary, pathfile, data;
	ofstream file;
	int sockID, connectedProcess, connectedProcess1, isConnected;

	Socket() {
		pathfile = "socket.txt";
		isConnected = 0;
		connectedProcess = -1;
		connectedProcess1 = -1;
	}
	void CreateConnection(Process p1, Process p2) {
		if (isConnected == 0) {
			connectedProcess = p1.PID;
			connectedProcess1 = p2.PID;
		}
		else
			cout << "Already connected" << endl;
	}

	void CloseConnection() {
		connectedProcess = -1;
		connectedProcess1 = -1;
		isConnected = 0;
	}

	void Write (string msg) {
		
				file.open(pathfile, ios::app);
				if (file.is_open())
				{
					file << msg;
				}
				else
					cout << "Send error" << endl;
				file.close();
		}

	void Read()
	{
		ifstream file(pathfile);
		string line;
		if (file.is_open())
		{
			while (getline(file, line))
			{
				temporary == line;
			}
		}
		else
		cout << "Read error" << endl;

		file.clear();
		file.close();
	}
};