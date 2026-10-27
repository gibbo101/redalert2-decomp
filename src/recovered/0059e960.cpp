// 0x0059e960: function not yet identified
//
// Body: 101 bytes (frozen inventory bound).
// Referenced from 1 site (unconditional call).
// Ghidra prototype: char FUN_0059e960(char param_1)
//
// Types and names are Ghidra placeholders (see shared/ghidra_types.hpp);
// rename and retype as the purpose becomes known.
//
// seed-generated: tools/original_target/regenerate_seeds.py may rewrite this file;
// delete this line when editing it by hand.
#include "shared/ghidra_types.hpp"

namespace seed_0059e960 {

char __stdcall FUN_0059e960(char param_1)
{
    if (param_1 == '\n') {
        return ' ';
    }
    if (param_1 == -0x4d) {
        return '|';
    }
    if (param_1 == -0x3c) {
        return '-';
    }
    if (param_1 == -0x33) {
        return '=';
    }
    if (((((param_1 == -0x26) || (param_1 == -0x3e)) || (param_1 == -0x41)) ||
            ((((param_1 == -0x3a || (param_1 == -0x3d)) ||
                ((param_1 == -0x2f || ((param_1 == -0x3b || (param_1 == -0x28)))))) || (param_1 == -0x4b))))
          || ((((param_1 == -0x40 || (param_1 == -0x3f)) || (param_1 == -0x27)) ||
                  ((param_1 == -0x2b || (param_1 == -0x4c)))))) {
        param_1 = (char)('+');
    }
    return param_1;
}

}  // namespace seed_0059e960
