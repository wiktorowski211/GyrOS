#include "IPC.h"


Socket::Socket()
{
	SockID = -1;
	ConnectedSock = -1;
	BindFlag = -1;
	ConnectionFlag = -1;
	
}

void Socket::Bind(Process p1)
{
	if (BindFlag == -1) {
		SockID = p1.PID;
		BindFlag = 0;
		
	}
	else {
		cout << "Socket already binded" << endl;
	}
}

void Socket::Connect(Socket sock)
{
	if (sock.ConnectionFlag == -1) {
			if (ConnectionFlag = -1) {
				sock.ConnectedSock = SockID;
				ConnectedSock = sock.SockID;
				sock.ConnectionFlag = 0;
				ConnectionFlag = 0;

			}
			else {
				cout << "Socket already conected" << endl;
			}
		
	}
	else {
		cout << "Socket to connect with isn't binded or has connection" << endl;
	}
}

void Socket::CloseConnection(Socket sock)
{
	ConnectedSock = -1;
	ConnectionFlag = -1;
	sock.ConnectedSock = -1;
	sock.ConnectionFlag = -1;
}

void Socket::Write(string msg)
{
	
	if (msgSize < 32) {
		buff.BufferWrite(msg);
	}
	else {
		cout << "Message too long" << endl;
	}
}

int Socket::GetSockID()
{
	return SockID;
}

void Socket::SetMsgSize(int msg)
{
	msgSize = msg;
}

string Socket::Read()
{
	string msg;
	msg = buff.BufferRead(msgSize);
	return msg;
}

void Buffer::BufferWrite(string msg)
{
	for (int i=0; i < msg.size(); i++) {
		tab[i] = msg[i];
	}

}

string Buffer::BufferRead(int msgSize)
{
	string msg = "";
	for (int i = 0; i < msgSize; i++) {
		msg = msg + tab[i];
	}

}

void IPC::SocketPair(Process p1, Process p2)
{
	Socket sock, sock1;
	sock.Bind(p1);
	sock1.Bind(p2);
	sock1.Connect(sock);
	SocketDomain[0] = sock;
	SocketDomain[1] = sock1;

}

void IPC::Send(Process sender, string msg)
{
	int size;
	size = msg.size();

	if (SocketDomain[0].GetSockID == sender.PID) {
		SocketDomain[1].SetMsgSize(size);
		SocketDomain[1].Write(msg);
	}
	else if (SocketDomain[1].GetSockID == sender.PID) {
		SocketDomain[0].SetMsgSize(size);
		SocketDomain[0].Write(msg);
	}
	else {
		cout << "Process isn't connected with any socket" << endl;
	}
}

string IPC::Recv(Process receiver)
{
	string temp;

	if (SocketDomain[0].GetSockID == receiver.PID) {
		
		temp=SocketDomain[1].Read();
	}
	else if (SocketDomain[1].GetSockID == receiver.PID) {
		
		temp=SocketDomain[0].Read();
	}
	else {
		cout << "Process isn't connected with any socket" << endl;
	}
}
