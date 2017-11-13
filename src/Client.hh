#pragma once
#include <arpa/inet.h>
#include <string>

class TcpClient
{
private:
	int sock;
	struct sockaddr_in server; 
public:
	TcpClient(std::string, int);
	void send(const std::string&);
	std::string receive(int wait_timeout = 5, int size = 512);
};
