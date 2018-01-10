#pragma once
#include "Process.h"


#include <string>
#include <iostream>
#include <vector>


using namespace std;

class Socket {
private: 
	int SockID, ConnectedSock, BindFlag, ConnectionFlag, msgSize;
	Buffer buff; // 0 - otrzymabe

public: 
	Socket();
	void Bind(Process p1);
	void Connect(Socket sock); //argument to socket z którym chcesz siê po³¹czyæ, musi byæ zbindowany
	void CloseConnection(Socket sock);
	int GetSockID();
	void SetMsgSize(int msg);
	void Write(string msg);
	string Read();
	~Socket() {};
	
};
class Buffer {
private:
		 char tab[32];

public:

	Buffer() {};
	void BufferWrite(string msg);
	string BufferRead(int msgSize);
	
};

class IPC {
private:
	Socket SocketDomain[2]; //maksymalnie 2 sockety jednoczeœnie
public:
	IPC() {};
	
	void SocketPair(Process p1, Process p2);
	void Send(Process sender, string msg);
	string Recv(Process receiver);

};