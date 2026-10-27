// int ConnectionClass::Service() (0x00481370, slot 5)
#include "shared/connection.hpp"

int ConnectionClass::Service()
{
    if (Service_Send_Queue() && Service_Receive_Queue()) {
        return 1;
    }
    return 0;
}
