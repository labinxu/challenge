#ifndef SERVER_H
#define SERVER_H
#include <unistd.h>
#include <string>

class Server
{
public:
    Server() = default;
    void run();
protected:
    virtual void HandleConnection(int connect);
    virtual std::string HandleMessage(char* message) = 0;

};

#endif
