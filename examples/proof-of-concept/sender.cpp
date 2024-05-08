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

  // Server address and port
  struct sockaddr_in serverAddr;
  memset(&serverAddr, 0, sizeof(serverAddr));
  serverAddr.sin_family      = AF_INET;
  serverAddr.sin_port        = htons(PORT);             // Example port number
  serverAddr.sin_addr.s_addr = inet_addr(ADDR.c_str()); // Example IP address

  // Data to send
  SimpleMessage msg;
  msg.set_message("Hello, UDP Server!");
  msg.set_id(42);

  // Send data
  std::string payload = msg.SerializeAsString();
  int bytesSent       = sendto(sockfd, payload.c_str(), payload.size(), 0, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
  if (bytesSent < 0) {
    std::cerr << "Error sending data"
              << "\n";
    close(sockfd);
    return EXIT_FAILURE;
  }

  std::cout << "Sent " << bytesSent << " bytes to " << inet_ntoa(serverAddr.sin_addr) << ":" << ntohs(serverAddr.sin_port) << "\n"
            << "Raw Data:\n"
            << bufferToHexStr(payload.c_str(), payload.size()) << "\n"
            << "Deserialized Message:\n"
            << msg.ShortDebugString() << "\n";

  // Close the socket
  close(sockfd);

  return EXIT_SUCCESS;
}

#endif // __linux__