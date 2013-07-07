/*
 * Exercise 12.15: Rewrite the first exercise to use a lambda (§ 10.3.2, p. 388)
 * in place of the end_connection function.
 */

#include <iostream>  // std::cout
#include <memory>    // std::shared_ptr

/**
 * @brief Represents a network destination with address and port
 *
 * Contains connection endpoint information including:
 * - Network address (IP or hostname)
 * - Port number
 */
struct Destination {
  std::string address;  // Network address (e.g., "192.168.1.1")
  unsigned port;        // TCP/UDP port number
};

/**
 * @brief Manages an active network connection
 *
 * Contains connection state information including:
 * - Pointer to destination
 * - Socket file descriptor
 */
struct Connection {
  Destination* dest;  // Connected destination
  int socket_fd;      // OS-level socket descriptor
  // Other connection state...
};

/**
 * @brief Establishes a connection to the specified destination
 * @param dest Pointer to target destination
 * @return Connection object with active link
 *
 * @note Performs all necessary system calls to establish
 *       network connectivity
 */
Connection Connect(Destination* dest) {
  std::cout << "Connecting to " << dest->address << ":" << dest->port << "\n";
  return Connection{dest, 1};  // Simulated socket fd
}

/**
 * @brief Terminates a network connection
 * @param connection Connection to terminate
 *
 * @warning Must be called exactly once per active connection
 * @sideeffect Closes underlying socket descriptor
 */
void Disconnect(Connection connection) {
  std::cout << "Closing connection to " << connection.dest->address << ":"
            << connection.dest->port << "\n";
  // Actual implementation would close socket_fd
}

/**
 * @brief Processes data through a managed network connection
 * @param destination Destination endpoint
 *
 * @pre Destination must be valid and reachable
 * @post Connection is automatically closed on scope exit
 * @throws std::runtime_error if connection fails
 *
 * @usage ProcessConnection(server);
 */
void ProcessConnection(Destination& destination /* other params */) {
  // Establish connection with automatic cleanup
  Connection connection = Connect(&destination);
  std::shared_ptr<Connection> ptr(&connection,
                                  [](Connection* ptr) { Disconnect(*ptr); });

  // Use the connection
  std::cout << "Using connection (fd: " << ptr->socket_fd << ")\n";

  // Connection automatically closed when p goes out of scope
}

int main() {
  Destination server{"example.com", 8080};

  ProcessConnection(server);

  return 0;
}

/*
 * $ g++ -o main chapter-12/exercise-15.cc && ./main
 * Connecting to example.com:8080
 * Using connection (fd: 1)
 * Closing connection to example.com:8080
 */
