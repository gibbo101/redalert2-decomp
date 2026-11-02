// void __fastcall Unknown_006F60D0(int group) (0x006F60D0): re-selects the group: the selection is dropped unless
// its first object is a foot in the group, the group's player-side technos are selected (sound suppressed) and
// the screen is redrawn. The first object's foot flag goes through a bool local (it is stored and the element
// read again).
#include "shared/uicmnds.hpp"
#include "shared/map_view.hpp"
// @ref ?Unknown_0049E3B0@DisplayClass@@QAEXXZ=0049e3b0
// @ref ?unknown_objects_a40c60@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00a40c60
// @ref ?unknown_sound_enabled_7d88d6@@3_NA=007d88d6

void __fastcall Unknown_006F60D0(int group)
{
    Map.Unknown_0049C980(0);
    Map.Unknown_0049C860(0, false);
    Map.Unknown_0049CA20(0);
    Map.Unknown_0049C7C0(0);
    Map.Unknown_0049CAC0(0);
    if (unknown_objects_a40c60.Count() != 0) {
        ObjectClass *object = unknown_objects_a40c60[0];
        bool is_foot = false;
        if (object != 0) {
            is_foot = object->AbstractFlags.IsFoot;
        }
        if (!is_foot || ((TechnoClass *)unknown_objects_a40c60[0])->unknown_1ac != group - 1) {
            unknown_selected_83996c->Unknown_006AAD40();
        }
    }
    for (int index = 0; index < Technos.Count(); index++) {
        TechnoClass *techno = Technos[index];
        if (techno != 0 && !techno->unknown_76 && techno->unknown_1ac == group - 1) {
            if (Is_Player_Side(techno) && !techno->unknown_77) {
                techno->unknown_slot80();
                unknown_sound_enabled_7d88d6 = false;
            }
        }
    }
    Map.Unknown_0049E3B0();
    Map.Flag_To_Redraw(1);
    unknown_sound_enabled_7d88d6 = true;
}
