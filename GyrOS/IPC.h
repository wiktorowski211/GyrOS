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
	void CreateConnection(Process p1, Process p2);

	void CloseConnection();

	void Write(string msg);

	void Read();
};