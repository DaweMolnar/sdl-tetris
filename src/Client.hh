#pragma once
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>

class TcpClient
{
private:
	int sock;
	struct sockaddr_in server; 
public:
	TcpClient(std::string, int);
	void send(const std::string&);
	std::string receive(int);
};

TcpClient::TcpClient(std::string address, int port)
{
	sock = socket(AF_INET , SOCK_STREAM, 0);
	if (sock == -1) throw std::runtime_error("Could not create socket");
	if(inet_addr(address.c_str()) == -1) {
		server.sin_addr.s_addr = inet_addr( address.c_str() );
	}
	server.sin_family = AF_INET;
	server.sin_port = htons( port );
	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)	{
		throw std::runtime_error("Could not connect to given address");
	}
}

void TcpClient::send(const std::string& data)
{
	if( ::send(sock , data.data() , data.size(), 0) < 0) {
		throw std::runtime_error("Could not send data");
	}
}
 
std::string TcpClient::receive(int size=512)
{
	char buffer[size];
	int n = recv(sock , buffer , sizeof(buffer) , 0);
	if (n < 0) {
		throw std::runtime_error("Could not receive data");
	}
	return std::string(buffer, n);
}
