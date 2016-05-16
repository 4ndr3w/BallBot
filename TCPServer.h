#ifndef TCP_Server_h
#define TCP_Server_h

class TCPServer {
	int port;
	int taskId;
public:
	TCPServer(int port);
	~TCPServer();
	void spawnServer();
	virtual void handleClient(int client) = 0;
};


#endif
