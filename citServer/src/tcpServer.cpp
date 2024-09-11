#include "../include/tcpServer.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <thread>

tcpServer::tcpServer(int port) : port_(port), server_fd_(-1)
{

}
tcpServer::~tcpServer(){
    if (server_fd_ != -1) {
        close(server_fd_);
    }
}
bool tcpServer::start(){
   // Create a socket
    server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd_ == -1) {
        std::cerr << "Socket creation error: " << strerror(errno) << std::endl;
        return false;
    }

    // Set up the server address struct
    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr)); // Clear struct
    server_addr.sin_family = AF_INET;              // IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY;      // Bind to any address
    server_addr.sin_port = htons(port_);           // Port

    // Bind the socket to the address and port
    if (bind(server_fd_, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Bind error: " << strerror(errno) << std::endl;
        close(server_fd_);
        return false;
    }

    // Listen for incoming connections
    if (listen(server_fd_, 5) < 0) {
        std::cerr << "Listen error: " << strerror(errno) << std::endl;
        close(server_fd_);
        return false;
    }

    std::cout << "Server is listening on port " << port_ << "..." << std::endl;
    return true; 
}
bool tcpServer::acceptConnections() {
    while (true) {
        sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int client_fd = accept(server_fd_, (struct sockaddr*)&client_addr, &client_addr_len);
        if (client_fd < 0) {
            std::cerr << "Accept error: " << strerror(errno) << std::endl;
            continue;  // Skip this iteration and continue with the next connection
        }

                // Start a thread to handle communication with this client
        std::thread client_thread(&tcpServer::handleClient, this, client_fd);
        client_thread.detach(); 
    }
}
// Method to handle client data
void tcpServer::handleClient(int client_fd) {
    char buffer[1024];
    while(true){
        ssize_t bytes_received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received < 0) {
            std::cerr << "Receive error: " << strerror(errno) << std::endl;

        } else if (bytes_received == 0) {
            std::cout << "Client disconnected." << std::endl;
            close(client_fd);
        } else {
            buffer[bytes_received] = '\0';  // Null-terminate the received data
            std::cout << "Received: " << buffer << std::endl;
            sendMessageToClient(client_fd, "ACK:  okay!!!");
        }

    }

    // Close the client socket
    // close(client_fd);
}


void tcpServer::sendMessageToClient(int client_fd, const std::string& message) {
    if (send(client_fd, message.c_str(), message.size(), 0) < 0) {
        std::cerr << "Send error: " << strerror(errno) << std::endl;
    }
}