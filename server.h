#ifndef SERVER_H
#define SERVER_H
#include <unistd.h>
#include <string>

class Server
{
public:
    Server() = default;
    //Server(int port,const std::string &addr);
    void run();
protected:
    virtual void HandleMessage(const char* message) = 0;
};

#endif
