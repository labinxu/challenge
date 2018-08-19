#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include "orderrouter.h"

int main() {
    auto router = new OrderRouter();
    router->run();
    return 0;
}
