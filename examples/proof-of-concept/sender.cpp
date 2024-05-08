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

  // Server address and port
  struct sockaddr_in serverAddr;
  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family      = AF_INET;
  serverAddr.sin_port        = htons(PORT);             // Example port number
  serverAddr.sin_addr.s_addr = inet_addr(ADDR.c_str()); // Example IP address

  // Data to send
  const char *message = "Hello, UDP Server!";
  int messageSize     = strlen(message);

  // Send data
  int bytesSent = sendto(sockfd, message, messageSize, 0, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
  if (bytesSent < 0) {
    std::cerr << "Error sending data" << std::endl;
    close(sockfd);
    return 1;
  }

  std::cout << "Sent " << bytesSent << " bytes to the server." << std::endl;

  // Close the socket
  close(sockfd);

  return 0;
}

#endif // __linux__