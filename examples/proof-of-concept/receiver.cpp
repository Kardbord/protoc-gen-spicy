#ifdef __linux__

#include <arpa/inet.h>
#include <constants.hpp>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  // Create a UDP socket
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) {
    std::cerr << "Error creating socket" << std::endl;
    return 1;
  }

  // Bind the socket to a port
  struct sockaddr_in serverAddr;
  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family      = AF_INET;
  serverAddr.sin_port        = htons(PORT);
  serverAddr.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP address

  if (bind(sockfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
    std::cerr << "Error binding socket" << std::endl;
    close(sockfd);
    return 1;
  }

  // Receive data
  char buffer[1024]; // Buffer to store received data
  struct sockaddr_in clientAddr;
  socklen_t clientAddrLen = sizeof(clientAddr);
  int bytesReceived       = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &clientAddr, &clientAddrLen);
  if (bytesReceived < 0) {
    std::cerr << "Error receiving data" << std::endl;
    close(sockfd);
    return 1;
  }

  std::cout << "Received " << bytesReceived << " bytes from " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << std::endl;

  // Print the received data
  buffer[bytesReceived] = '\0'; // Add null terminator to make it a valid C string
  std::cout << "Message: " << buffer << std::endl;

  // Close the socket
  close(sockfd);

  return 0;
}

#endif // __linux__