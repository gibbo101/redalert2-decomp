// short __fastcall Unknown_005233D0(int key) -- 0x005233D0
// Purpose: GetKeyState(key), or the recorded state of the key's low byte while
// the key-state override 0x00A522AC is set (shared/keyboard.hpp).
#include "shared/keyboard.hpp"
// @ref ?unknown_key_state_override_a522ac@@3HA=00a522ac
// @ref ?unknown_key_states_a51fd0@@3PAFA=00a51fd0

short __fastcall Unknown_005233D0(int key)
{
    if (unknown_key_state_override_a522ac == 0) {
        return GetKeyState(key);
    }
    return unknown_key_states_a51fd0[key & 0xff];
}
