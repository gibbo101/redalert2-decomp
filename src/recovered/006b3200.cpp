// 0x006b3200: function not yet identified
//
// Body: 41 bytes (frozen inventory bound).
// Referenced from 3 sites (unconditional call).
// Ghidra prototype: char * __thiscall FUN_006b3200(char *param_1,char *param_2)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_006b3200 {

extern "C" undefined4 __cdecl _strncpy(...);  // @ref __strncpy=007823d0

struct Owner_006b3200 { char * FUN_006b3200(char *param_2); };

char * Owner_006b3200::FUN_006b3200(char *param_2)
{
    char * param_1 = (char *)this;
    if (param_2 == (char *)0x0) {
        *param_1 = '\0';
        return param_1;
    }
    _strncpy(param_1,param_2,0x1f);
    param_1[0x1f] = '\0';
    return param_1;
}

}  // namespace seed_006b3200
