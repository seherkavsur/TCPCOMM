#include "../include/tcpClient.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
tcpClient::tcpClient(const std::string& serverIP, int serverPort) : serverIP(serverIP), serverPort(serverPort), sockfd(-1)
{
    listening = false;
}
tcpClient::~tcpClient(){
    std::cout << "stop listening..." << std::endl;
    stopListening();
    if (sockfd != -1) {
            close(sockfd);
        }
}
/**
 * create TCP socket
 */
bool tcpClient::connectToServer() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Socket creation failed" << std::endl;
        return false;
    }

    // Define server address
    sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    if (inet_pton(AF_INET, serverIP.c_str(), &serverAddr.sin_addr) <= 0) {
        std::cerr << "Invalid address or address not supported" << std::endl;
        close(sockfd);
        return false;
    }

    // Connect to server
    if (connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        close(sockfd);
        return false;
    }

    std::cout << "Connected to server" << std::endl;
    return true;
}
/**
 * Send data to Server
 */
bool tcpClient::sendData(const std::string& data) {
    if (send(sockfd, data.c_str(), data.size(), 0) < 0) {
        std::cerr << "Send failed" << std::endl;
        return false;
    }
    return true;
}


// std::string tcpClient::receiveData(size_t size) {
//     char buffer[size];
//     ssize_t bytesReceived = recv(sockfd, buffer, size, 0);
//     if (bytesReceived < 0) {
//         std::cerr << "Receive failed" << std::endl;
//         return "";
//     }
//     return std::string(buffer, bytesReceived);
// }
/**
 * create a thread for listen socket
 */
void tcpClient::startListening() {
    listening = true;
    listeningThread = std::thread(&tcpClient::listenForMessages, this);
}

void tcpClient::stopListening() {
    if (listening) {
        std::cout << "stop listening" << std::endl;
        listening = false;
        if (listeningThread.joinable()) {
            listeningThread.join();
        }
    }
}
void tcpClient::listenForMessages() {
    while (listening) {
        char buffer[1024];
        ssize_t bytes_received = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received < 0) {
            std::cerr << "Receive error: " << strerror(errno) << std::endl;
            break;
        } else if (bytes_received == 0) {
            std::cout << "Server disconnected." << std::endl;
            break;
        } else {
            buffer[bytes_received] = '\0';  // Null-terminate the received data
            std::cout << "Received: " << buffer << std::endl;
            std::string strBuffer = buffer;
        }
    }
}