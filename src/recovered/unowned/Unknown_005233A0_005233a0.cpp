// void __fastcall Unknown_005233A0(int key, bool release) -- 0x005233A0
// Purpose: records a key's state for the readers 0x005233D0/0x005233F0 while
// the key-state override 0x00A522AC is set: 0x8000 (down) unless release
// (shared/keyboard.hpp).
#include "shared/keyboard.hpp"
// @ref ?unknown_key_state_override_a522ac@@3HA=00a522ac
// @ref ?unknown_key_states_a51fd0@@3PAFA=00a51fd0

void __fastcall Unknown_005233A0(int key, bool release)
{
    if (unknown_key_state_override_a522ac != 0) {
        unknown_key_states_a51fd0[key & 0xff] = release ? 0 : 0x8000;
    }
}
