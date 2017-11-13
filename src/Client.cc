#include "Client.hh"
#include <stdexcept>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/types.h>
#include <netdb.h>
#include <fcntl.h>

TcpClient::TcpClient(std::string address, int port)
{
	sock = socket(AF_INET , SOCK_STREAM, 0);
	if (sock == -1) throw std::runtime_error("Could not create socket");
	int rv = fcntl(sock, F_SETFL, O_NONBLOCK); // socket set to NONBLOCK
	if(rv < 0) throw std::runtime_error("nonblock failed");
	if(inet_addr(address.c_str()) == -1) {
		server.sin_addr.s_addr = inet_addr( address.c_str() );
	}
	server.sin_family = AF_INET;
	server.sin_port = htons( port );
	while (true) {
		if (connect(sock, (struct sockaddr *)&server , sizeof(server)) < 0)	{
			if (errno != EAGAIN) {
				throw std::runtime_error("Could not connect to given address");
			}
		} else break;
	}
}

void TcpClient::send(const std::string& data)
{
	if( ::send(sock , data.data() , data.size(), 0) < 0) {
		throw std::runtime_error("Could not send data");
	}
}

std::string TcpClient::receive(int wait_timeout, int size)
{
	fd_set set;
	struct timeval timeout;
	FD_ZERO(&set);
	FD_SET(sock, &set);
	timeout.tv_sec = wait_timeout;
	timeout.tv_usec = 0;
	int rv = select(sock + 1, &set, nullptr, nullptr, &timeout);
	if (rv == -1) throw std::runtime_error("SOCKETERROR");
	else if (rv == 0) return "";
	char buffer[size];
	int n = recv(sock , buffer , sizeof(buffer) , 0);
	if (n < 0) {
		throw std::runtime_error("Could not receive data");
	}
	return std::string(buffer, n);
}
