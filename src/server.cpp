#include <iostream>
#include <cstring>
#include <cerrno>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(){

  // create a file descriptor for socker
  int fd = socket(AF_INET, SOCK_STREAM,0);

  if(fd <0) {
      perror("Socket failed");
      return 1;
  }

  // setting socket options
  // SO_REUSEADDR is used with a val of 1 so that server can bind to same ip:port after a restart
  int val = 1;
  if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)) <0){
    perror("Setsockopt error");
    close(fd);
    return 1;
  };

  // bind socket to ip and port
  sockaddr_in addr = {};
  addr.sin_family = AF_INET;
  // CPU store data in little endian, but tcp requires it in big endian format so we need to convert it
  // htons(16bits) converts little endian to big endian
  addr.sin_port = htons(1234);
  // htonl(32bits) converts little endian to big endian
  addr.sin_addr.s_addr = htonl(0); // wildcard IP 0.0.0.0
  
  // bind the socket to the address


  if(bind(fd, (struct sockaddr*)&addr, sizeof(addr))<0){
    perror("Bind failed");
    close(fd);
    return 1;
  }

  // listen to the request 
  if (listen(fd, SOMAXCONN) < 0){
    perror("Listen error");
    close(fd);
    return 1;
  }

  std::cout << "Listening on 0.0.0.0:1234\n";

  // actually listen to the socket
  while(true){
    
    sockaddr_in client_addr = {};
    socklen_t addrlen = sizeof(client_addr);
    
    int connfd = accept(fd, reinterpret_cast<sockaddr*>(&client_addr), &addrlen);
    if(connfd < 0){
      perror("Accept");    
      continue;
      // error so dont send anything back
    }
    

    // show client info
    char ip[INET_ADDRSTRLEN];
    // convert binary addess to dotted decimal
    inet_ntop(AF_INET, &client_addr.sin_addr, ip, sizeof(ip));
    std::cout << "Connection from " << ip << ":" << ntohs(client_addr.sin_port) << "\n";
    
    // do_something();
    // close connection
    const char* msg = "hello there\n";
    write(connfd, msg, std::strlen(msg));
    close(connfd);
  }

  close(fd);
  
  return 0;
}
