#include "TCPServer.h"
#include "sockLib.h"
#include "taskLib.h"
#include "inetLib.h"
#include "strLib.h"

void spawnTCPServerHandler(void *ptr) {
  ((TCPServer*)ptr)->spawnServer();
}

void spawnClientHandler(void *ptr, int socket, void *listElement)
{
  ((TCPServer*)ptr)->handleClient(socket);
}

TCPServer::TCPServer(int port) {
  this->port = port;
  taskId = taskSpawn("TCPServerTask", 101, VX_FP_TASK, 2048, (FUNCPTR)spawnTCPServerHandler, (int)this,0,0,0,0,0,0,0,0,0);
}

TCPServer::~TCPServer() {
  taskDelete(taskId);
  root = NULL;
}

void TCPServer::spawnServer() {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  sockaddr_in bindaddr;
  int sockaddr_len = sizeof(sockaddr_in);
  bzero((char*)&bindaddr, sockaddr_len);
  bindaddr.sin_family = AF_INET;
  bindaddr.sin_port = htons(port);
  bindaddr.sin_addr.s_addr = INADDR_ANY;
  bindaddr.sin_len = sockaddr_len;

  if ( bind(sock, (sockaddr*)&bindaddr, sockaddr_len) == ERROR ) {
    close(sock);
    exit(1);
  }

  if ( listen(sock, 10) == ERROR ) {
    close(sock);
    exit(1);
  }

  while (true) {
    sockaddr_in src;
    int client = accept(sock, (sockaddr*)&src, &sockaddr_len);

    if ( client != ERROR ) {
      ClientNode *thisClient = (ClientNode*)malloc(sizeof(ClientNode));
      thisClient->socket = client;
      if ( root == NULL )
        root = lastClient = thisClient;
      else
      {
        lastClient->next = thisClient;
        thisClient->prev = lastClient;
        lastClient = thisClient;
      }

      taskSpawn("TCPClientHandler", 101, VX_FP_TASK, 2048, (FUNCPTR)spawnClientHandler, (int)this,client,(int)thisClient,0,0,0,0,0,0,0);
    }
  }
}
