#ifdef __linux__

#include <SimpleMessage.pb.h>
#include <arpa/inet.h>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <utils.hpp>

int main() {
  // Create a UDP socket
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) {
    std::cerr << "Error creating socket"
              << "\n";
    return EXIT_FAILURE;
  }

  // Bind the socket to a port
  struct sockaddr_in serverAddr;
  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family      = AF_INET;
  serverAddr.sin_port        = htons(PORT);
  serverAddr.sin_addr.s_addr = inet_addr(ADDR.c_str());

  if (bind(sockfd, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
    std::cerr << "Error binding socket"
              << "\n";
    close(sockfd);
    return EXIT_FAILURE;
  }

  // Receive data
  char buffer[1024]; // Buffer to store received data
  struct sockaddr_in clientAddr;
  socklen_t clientAddrLen = sizeof(clientAddr);
  std::cout << "Waiting to receive...\n";
  int bytesReceived = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &clientAddr, &clientAddrLen);
  if (bytesReceived < 0) {
    std::cerr << "Error receiving data"
              << "\n";
    close(sockfd);
    return EXIT_FAILURE;
  }

  std::cout << "Received " << bytesReceived << " bytes from " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << "\n";

  // Print the received data
  buffer[bytesReceived] = '\0';
  std::cout << "Raw Message: " << bufferToHexStr(buffer, bytesReceived) << "\n";

  // Deserialize protobuf message
  SimpleMessage msg;
  msg.ParseFromString({buffer, static_cast<size_t>(bytesReceived)});

  std::cout << "Deserialized Message: " << msg.ShortDebugString() << "\n";

  // Close the socket
  close(sockfd);

  return EXIT_SUCCESS;
}

#endif // __linux__