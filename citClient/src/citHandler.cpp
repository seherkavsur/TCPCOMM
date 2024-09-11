#include "../include/citHandler.h"
#include "memory"
#include "iostream"


citHandler::citHandler(const citHandler::e_SIPType type) : sipType(type){
    CLIENT_IP_ADDRESS = (this->sipType == e_SIPType::e_master ? SIP_SERVER_MASTER_INTERNAL_IP_ADDR : SIP_SERVER_SLAVE_INTERNAL_IP_ADDR);

    this->tcpClientHandler = new tcpClient(CLIENT_IP_ADDRESS, 12345);
    if (this->tcpClientHandler->connectToServer()) {
        this->tcpClientHandler->startListening();
        

    }
}
citHandler::~citHandler(){
    std::cout << "cit dtor" << std::endl;
    
    this->isRunning = false;
    if (this->operationthread.joinable())
    {
        operationthread.join(); 
    }
    delete this->tcpClientHandler;
}

void citHandler::run(){
    this->operationthread = std::thread(&citHandler::threadFunc, this);
}

void citHandler::threadFunc(){
    while(this->isRunning){
        if (this->tcpClientHandler->sendData("hello Server!"))
        {
            std::cout << "Message sent. Listening for responses..." << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}
