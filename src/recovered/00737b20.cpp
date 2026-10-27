// 0x00737b20: function not yet identified
//
// Body: 47 bytes (frozen inventory bound).
// Referenced from 0 sites.
// Ghidra prototype: char * __fastcall FUN_00737b20(char *param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_00737b20 {

extern undefined4  FUN_00784130(uint *param_1, char param_2);
extern "C" char s_gsmallwoo_007d8904[];

char * __fastcall FUN_00737b20(char *param_1)
{
    int iVar1;

    *param_1 = s_gsmallwoo_007d8904[0];
    param_1[1] = '\0';
    param_1[2] = '\0';
    iVar1 = (int)(FUN_00784130((uint *)(s_gsmallwoo_007d8904), (char)(0x5f)));
    if (iVar1 != 0) {
        param_1[1] = *(char *)(iVar1 + 1);
    }
    return param_1;
}

}  // namespace seed_00737b20
