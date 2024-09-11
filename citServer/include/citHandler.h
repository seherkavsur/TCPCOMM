#ifndef CITHANDLER_H
#define CITHANDLER_H

#include <string>
#include <memory>
#include "tcpServer.h"
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

private:
    e_SIPType sipType;
    
};

#endif // CITHANDLER_H
