#include "../include/citHandler.h"
#include "memory"
#include "iostream"

citHandler::citHandler(const citHandler::e_SIPType type) : sipType(type){
    tcpServer server(12345);
    if (server.start())
    {
        server.acceptConnections();
    }
    
}
citHandler::~citHandler(){
}