// int Unknown_00603C10() (0x00603C10; Set_Scheme_Lighting 0x00520A80): the number of extra palette names (the
// table is made on first use).
#include "shared/scheme_table.hpp"

int Unknown_00603C10()
{
    return Scheme_Table()->Names->Count();
}
