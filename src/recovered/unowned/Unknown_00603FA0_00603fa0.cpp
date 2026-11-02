// void Unknown_00603FA0() (0x00603FA0; Prog_End and 0x006910E5): deletes the per-palette scheme table.
#include "shared/scheme_table.hpp"
// @ref ??1SchemeTable@@QAE@XZ=00604250

void Unknown_00603FA0()
{
    if (unknown_scheme_table_a76414 != 0) {
        delete unknown_scheme_table_a76414;
        unknown_scheme_table_a76414 = 0;
    }
}
