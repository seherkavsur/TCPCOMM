#ifndef CITHANDLER_H
#define CITHANDLER_H

#include <string>
#include <memory>
#include "tcpClient.h"
class citHandler
{
public:
    enum e_SIPType{
        e_master = 0,
        e_slave
    };

    citHandler(const citHandler::e_SIPType type);
    ~citHandler();
    void run();
    void threadFunc();

private:
    std::string CLIENT_IP_ADDRESS{"127.0.0.1"};
    e_SIPType sipType;
    tcpClient *tcpClientHandler;
    std::thread operationthread;
    bool isRunning = true;

    
};

#endif // CITHANDLER_H
