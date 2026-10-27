// 0x0051b280: function not yet identified
//
// Owner: SelectTeamCommandClass, virtual slot 1 (vtable +0x4) (from RTTI/vtables).
// Body: 28 bytes (frozen inventory bound).
// Referenced from 1 site (data).
// Ghidra prototype: undefined * __fastcall FUN_0051b280(int param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
#include "shared/ghidra_types.hpp"

namespace seed_0051b280 {

extern undefined4  FUN_007820f4(int, int, int);
extern "C" undefined4 DAT_00a4149c;
extern "C" char s_TeamSelect__d_007dca28[];

undefined * __fastcall FUN_0051b280(int param_1)
{
    FUN_007820f4((int)(&DAT_00a4149c), (int)(s_TeamSelect__d_007dca28), (int)(*(undefined4 *)(param_1 + 4)));
    return (unsigned char *)(&DAT_00a4149c);
}

}  // namespace seed_0051b280
