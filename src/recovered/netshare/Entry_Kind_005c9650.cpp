// int __fastcall Entry_Kind_005c9650(NodeNameType *entry) (0x005C9650)
#include "shared/lobby.hpp"
// @ref ?unknown_closed_entry_a72d30@@3PAUNodeNameType@@A=00a72d30
// @ref ?unknown_easy_ai_entry_a72d34@@3PAUNodeNameType@@A=00a72d34
// @ref ?unknown_hard_ai_entry_a72d3c@@3PAUNodeNameType@@A=00a72d3c
// @ref ?unknown_medium_ai_entry_a72d38@@3PAUNodeNameType@@A=00a72d38
// @ref ?unknown_open_entry_a72d2c@@3PAUNodeNameType@@A=00a72d2c

int __fastcall Entry_Kind_005c9650(NodeNameType *entry)
{
    if (entry == unknown_open_entry_a72d2c) {
        return 2;
    }
    if (entry == unknown_closed_entry_a72d30) {
        return 3;
    }
    if (entry == unknown_easy_ai_entry_a72d34) {
        return 4;
    }
    if (entry == unknown_medium_ai_entry_a72d38) {
        return 5;
    }
    if (entry == unknown_hard_ai_entry_a72d3c) {
        return 6;
    }
    return entry == unknown_player_a72d44 ? 7 : 2;
}
