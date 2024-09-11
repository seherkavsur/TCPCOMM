#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include <string>
#include <thread>
static constexpr char SIP_SERVER_SLAVE_INTERNAL_IP_ADDR[] = "172.173.20.12";
static constexpr char SIP_SERVER_MASTER_INTERNAL_IP_ADDR[] = "127.0.0.1";
class tcpClient
{
public:
    explicit tcpClient(const std::string& serverIP, int serverPort);
    ~tcpClient();

    bool connectToServer();
    bool sendData(const std::string& data);
    void startListening();
    void stopListening();

private:
    std::string serverIP;
    int serverPort;
    int sockfd;
    bool listening;

    std::thread listeningThread;
    void listenForMessages();
};
#endif //TCPCLIENT_H