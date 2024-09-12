#include "../include/citHandler.h"
#include "memory"
#include "iostream"


citHandler::citHandler(const citHandler::e_SIPType type) : sipType(type){

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
    if (this->startConnection()){
        //test
        this->operationthread = std::thread(&citHandler::threadFunc, this);
        while(true){
            switch (this->tcpClientHandler->connectionState)
            {
            case tcpClient::e_TCP_DISCONNECTED:
            case tcpClient::e_TCP_RECIEVE_ERR:
                std::cout << "connection cloed" << std::endl;
                break;
            
            default:
                std::cout << "do someting...." << std::endl;
                break;
            }
            //to something
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    }
}

bool citHandler::startConnection(){
    this->CLIENT_IP_ADDRESS = (this->sipType == e_SIPType::e_master ? SIP_SERVER_MASTER_INTERNAL_IP_ADDR : SIP_SERVER_SLAVE_INTERNAL_IP_ADDR);

    this->tcpClientHandler = new tcpClient(CLIENT_IP_ADDRESS, 12345);
    int connectionTryCount = 0;

    while(connectionTryCount < MAX_CONNECTION_TRY_COUNT) {
        ++connectionTryCount;
        std::cout << "TCP Server Connection trying.....(" <<  connectionTryCount << ")" << std::endl;

        if (this->tcpClientHandler->connectToServer()) {
            std::cout << "TCP Server Connection success!" << std::endl;
            this->tcpClientHandler->startListening();
            return true;
        }else{
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    }
    std::cout << "TCP Server Connection FAILED!" << std::endl;
    return false;
}
//test
void citHandler::threadFunc(){
    while(this->isRunning){
        if (this->tcpClientHandler->sendData("hello Server!"))
        {
            std::cout << "Message sent. Listening for responses..." << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}
