// int __fastcall unknown_state_index_6f7ea0(int state) -- 0x006F7EA0
// Purpose: maps -1 to 0, 0 to 1, 1 to 2 and anything else to 0.
// Assumptions: what the states are is unknown (two identical copies,
// 0x006F7EA0 and 0x006F8190).

int __fastcall unknown_state_index_6f7ea0(int state)
{
    if (state == -1) {
        return 0;
    }
    if (state == 0) {
        return 1;
    }
    return state == 1 ? 2 : 0;
}
