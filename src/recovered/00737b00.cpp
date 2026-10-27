// 0x00737b00: function not yet identified
//
// Body: 23 bytes (frozen inventory bound).
// Referenced from 3 sites (unconditional call).
// Ghidra prototype: char * __fastcall FUN_00737b00(char *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00737b00 {

extern "C" undefined4 __cdecl _strncpy(...);  // @ref __strncpy=007823d0
extern "C" char s_gsmallwoo_007d8904[];

char * __fastcall FUN_00737b00(char *param_1)
{
    _strncpy(param_1,s_gsmallwoo_007d8904,0x20);
    return param_1;
}

}  // namespace seed_00737b00
