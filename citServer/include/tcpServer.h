#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include <string>
class tcpServer
{
public:
    explicit tcpServer(int port);
    ~tcpServer();

    bool start();
    bool acceptConnections();

private:
    int port_;
    int server_fd_;
    void handleClient(int client_fd);
    void sendMessageToClient(int client_fd, const std::string& message);
};
#endif //TCPCLIENT_H