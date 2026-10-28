// void __fastcall TubeClass::Read_INI(CCINIClass &ini) (0x006EF5C0)
// Makes a tube of every [Tubes] entry: "enter x,y,facing,exit x,y,directions..." (a -1 direction ends the list).
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
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ??0TubeClass@@QAE@ABVCell@@H@Z=006ef1d0
extern "C" int __cdecl atoi(char const *string);

void __fastcall TubeClass::Read_INI(CCINIClass &ini)
{
    char buffer[512];
    int step = 0;
    int count = ini.Entry_Count(TubeSection_Tubes);
    for (int entry = 0; entry < count; entry++) {
        step = 0;
        char const *key = ini.Get_Entry(TubeSection_Tubes, entry);
        ini.Get_String(TubeSection_Tubes, key, 0, buffer, sizeof(buffer));
        TubeClass *tube = new TubeClass(Cell(0, 0), 0);
        tube->EnterCell.X = atoi(strtok(buffer, ","));
        tube->EnterCell.Y = atoi(strtok(0, ","));
        tube->Facing = atoi(strtok(0, ","));
        tube->ExitCell.X = atoi(strtok(0, ","));
        tube->ExitCell.Y = atoi(strtok(0, ","));
        tube->unknown_1c0 = -1;
        for (; step < 100; step++) {
            tube->Directions[step] = atoi(strtok(0, ","));
            tube->unknown_1c0++;
            if (tube->Directions[step] == -1) {
                break;
            }
        }
        Map[tube->EnterCell].unknown_116 = entry;
    }
}
