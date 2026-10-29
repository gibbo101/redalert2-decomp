// unsigned char UnknownSessionState::Unknown_00672F10() (0x00672F10)
// The session's byte at +0x3080 (formerly the address-only leaf Leaf_672f10::get;
// the owner-draw control test 0x005E0760 calls it on the session at 0x00A3D298).
#include "shared/session_state.hpp"

unsigned char UnknownSessionState::Unknown_00672F10()
{
    return unknown_3080;
}
