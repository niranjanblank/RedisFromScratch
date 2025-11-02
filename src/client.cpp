#include <iostream>
#include <cstring>
#include <cerrno>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main (){
  
  // assigning a socker
  int fd = socket(AF_INET, SOCK_STREAM, 0);

  if (fd < 0){
    perror("Socket creation failed");
    return 1;
  }

  // address of the server we want to connect to
  sockaddr_in server_addr = {};
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(1234);
  server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK); // 127.0.0.1
  // connect to the server
  if(connect(fd, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) < 0){
    perror("connect");
    close(fd);
    return 1;
  }

  // get data from server
  char buffer[1024];
  ssize_t n = read(fd, buffer, sizeof(buffer)-1);
  if(n>0){
    buffer[n]='\0';
    std::cout << "Server: "<<buffer << std::endl;
  }else if (n == 0) {
    std::cout << "Server closed connection"<< std::endl;
  } else {
    perror("read");
  }

  close(fd);
  return 0;
}
