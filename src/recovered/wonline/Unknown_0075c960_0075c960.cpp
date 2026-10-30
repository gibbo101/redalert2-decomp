// void Unknown_0075c960() (0x0075C960)
// Sends "G" through IChat slot 15 when the chat object exists.
#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
// @ref ??_C@_01PACF@G?$AA@=008003d0

void Unknown_0075c960()
{
    if (unknown_chat_a72cfc) unknown_chat_a72cfc->unknown_slot15("G");
}
