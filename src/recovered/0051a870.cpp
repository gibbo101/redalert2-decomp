// 0x0051a870: function not yet identified
//
// Body: 16 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: void FUN_0051a870(void)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0051a870 {

struct Callee_006e8510 { undefined4 FUN_006e8510(char *param_2); };
extern "C" undefined4 DAT_00a35d78;
extern "C" char s_INTRO_007dbc90[];

void  FUN_0051a870(void)
{
    ((Callee_006e8510*)(&DAT_00a35d78))->FUN_006e8510((char *)(s_INTRO_007dbc90));
    return;
}

}  // namespace seed_0051a870
