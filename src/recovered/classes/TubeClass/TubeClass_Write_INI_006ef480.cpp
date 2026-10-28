// void __fastcall TubeClass::Write_INI(CCINIClass &ini) (0x006EF480)
// Rewrites [Tubes]: renumbers the tubes (deleting the unusable), then one "index=x,y,facing,x,y,directions" entry each.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/tube.hpp"
#include "shared/vector_class.hpp"
#include "shared/ccini_class.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/tube_data.hpp"
// @ref _TubeSection_Tubes=007f8628
// @ref ??_C@_05GBCE@Tubes?$AA@=007f862c
// @ref ?unknown_TubeClass_list_008661c8@@3V?$DynamicVectorClass@PAVTubeClass@@@@A=008661c8
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Update_All_Indexes@TubeClass@@SAXXZ=006ef400
// @ref ??_C@_02MECO@?$CFd?$AA@=007ce9bc
// @ref ??_C@_03FOBE@?0?$CFd?$AA@=007cfa6c
// @ref ??_C@_0P@PHNA@?$CFd?0?$CFd?0?$CFd?0?$CFd?0?$CFd?$AA@=007f8650
extern "C" int __cdecl sprintf(char *buffer, char const *format, ...);
extern "C" unsigned int __cdecl strlen(char const *string);

void __fastcall TubeClass::Write_INI(CCINIClass &ini)
{
    ini.Clear(TubeSection_Tubes, 0);
    Update_All_Indexes();
    for (int index = 0; index < unknown_TubeClass_list_008661c8.Count(); index++) {
        TubeClass *tube = unknown_TubeClass_list_008661c8[index];
        if (tube != 0) {
            char key[12];
            char value[552];
            sprintf(key, "%d", index);
            sprintf(value, "%d,%d,%d,%d,%d", (int)tube->EnterCell.X, (int)tube->EnterCell.Y, tube->Facing, (int)tube->ExitCell.X, (int)tube->ExitCell.Y);
            for (int step = 0; step < 100; step++) {
                sprintf(value + strlen(value), ",%d", tube->Directions[step]);
            }
            ini.Put_String(TubeSection_Tubes, key, value);
        }
    }
}
