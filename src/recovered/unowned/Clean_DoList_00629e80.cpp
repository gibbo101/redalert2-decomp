// void __fastcall Clean_DoList(ConnManClass *net) (0x00629E80).
#include "shared/queue.hpp"
// @ref ?Frame@@3HA=00a40d2c
// @ref ?DoList@@3V?$QueueClass@VEventClass@@$0EAAA@@@A=00866270

void __fastcall Clean_DoList(ConnManClass *net)
{
    while (DoList.Count) {
        if (!DoList.First().IsExecuted && ::Frame <= DoList.First().Frame) {
            break;
        }
        DoList.Next();
    }
}
