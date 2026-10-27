// 0x00406350: function not yet identified
//
// Body: 32 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: char * __fastcall FUN_00406350(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00406350 {

extern "C" undefined4 DAT_00830fb8;
extern "C" char s_no_events_007cccd4[];
extern "C" char s_unknown_007ccce0[];

char * __fastcall FUN_00406350(int param_1)
{
    if (DAT_00830fb8 == 0) {
        return s_no_events_007cccd4;
    }
    if (*(int *)(param_1 + 0x24) == 0) {
        return s_unknown_007ccce0;
    }
    return (char *)(*(int *)(param_1 + 0x24) + 0x6c);
}

}  // namespace seed_00406350
