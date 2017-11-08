#!/usr/bin/env python

import socket, threading
class Forwarder:
    def __init__(self):
        self.clients = []

    def forward(self, source, data):
        for client in self.clients:
            if source != client:
                client.send(data)

    def addClient(self, client):
        self.clients.append(client)

    def removeClient(self, client):
        self.clients.remove(client)

class ClientThread(threading.Thread):

    def __init__(self,ip,port,clientsocket,forwarder):
        threading.Thread.__init__(self)
        self.ip = ip
        self.port = port
        self.csocket = clientsocket
        self.forwarder = forwarder
        print "[+] New thread started for "+ip+":"+str(port)

    def run(self):
        print "Connection from : "+ip+":"+str(port)
        clientsock.send("Welcome to the server")
        data = "dummydata"
        while len(data):
            data = self.csocket.recv(2048)
            print "Client(%s:%s) sent : %s"%(self.ip, str(self.port), data)
            self.forwarder.forward(self, data)
        print "Client at "+self.ip+" disconnected..."
        forwarder.removeClient(self)

    def send(self, data):
        self.csocket.send(data)

host = "0.0.0.0"
port = 4242

tcpsock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
tcpsock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

tcpsock.bind((host,port))
forwarder = Forwarder()
while True:
    tcpsock.listen(4)
    print "Listening for incoming connections..."
    (clientsock, (ip, port)) = tcpsock.accept()

    #pass clientsock to the ClientThread thread object being created
    newthread = ClientThread(ip, port, clientsock, forwarder)
    forwarder.addClient(newthread)
    newthread.start()
