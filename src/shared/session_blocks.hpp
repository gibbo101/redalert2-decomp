// Blocks of the session (UnknownSessionState, shared/unknown_globals.hpp) that MPCooperative
// slot 34 0x005A46C0 saves and slot 37 0x005A5720 restores whole (struct copies: rep movsd for
// 0x60 and 0x20 bytes, four dword moves for the 16 bytes at the unaligned +0x3022; contents
// not recovered).
#ifndef RA2_SHARED_SESSION_BLOCKS_HPP
#define RA2_SHARED_SESSION_BLOCKS_HPP

struct UnknownSessionBlock_293C { int unknown[24]; };
struct UnknownSessionBlock_299C { int unknown[8]; };
struct UnknownSessionBlock_3022 { unsigned short unknown[8]; };

#endif
