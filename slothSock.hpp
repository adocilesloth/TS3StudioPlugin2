/*******************************************
A Docile Sloth 2017 (adocilesloth@gmail.com)
*******************************************/
#pragma once
#include <vector>
#include <string>

#if _WIN32
#include <winsock2.h>
#include <windows.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

class slothSock
{
private:
	SOCKET sock;
public:
	slothSock() {};

	bool connectToHost(int port, char* adrs);
	void closeConnection();
	bool sendAll(char *buffer, int length, int flag);
	bool sendAll(const char *buffer, int length, int flag);
	bool recvAll(char *buffer, int length, int flag);
	bool recvAll(std::vector<char> &vbuffer, int length, int flag);
	bool recvAll(char *buffer, int length, int flag, std::string endid);
	bool recvAll(std::vector<char> &vbuffer, int length, int flag, std::string endid);
};
#else
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class slothSock
{
private:
	int sock;
public:
	slothSock() {};

	bool connectToHost(int port, char* adrs);
	void closeConnection();
	bool sendAll(char *buffer, int length, int flag);
	bool sendAll(const char *buffer, int length, int flag);
	bool recvAll(char *buffer, int length, int flag);
	bool recvAll(std::vector<char> &vbuffer, int length, int flag);
	bool recvAll(char *buffer, int length, int flag, std::string endid);
	bool recvAll(std::vector<char> &vbuffer, int length, int flag, std::string endid);
};
#endif
