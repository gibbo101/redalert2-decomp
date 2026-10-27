// void __fastcall Unknown_006F61F0(int group) (0x006F61F0)
// Selects the group (hypothesis: group - 1 at +0x1AC): the screen's placement
// modes are switched off, then every unselected player-side techno of the
// group gets slot 80 (selection) with the effect sound suppressed.
#include "shared/uicmnds.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0049CAC0@DisplayClass@@QAEXH@Z=0049cac0
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ?Technos@@3V?$DynamicVectorClass@PAVTechnoClass@@@@A=00a40c20

// @ref ?Unknown_0049C980@UnknownCommandScreen@@QAEXH@Z=0049c980
// @ref ?Unknown_0049C860@UnknownCommandScreen@@QAEXH_N@Z=0049c860
// @ref ?Unknown_0049CA20@UnknownCommandScreen@@QAEXH@Z=0049ca20
// @ref ?Unknown_0049C7C0@UnknownCommandScreen@@QAEXH@Z=0049c7c0
// @ref ?Unknown_0049CAC0@UnknownCommandScreen@@QAEXH@Z=0049cac0
// @ref ?unknown_sound_enabled_7d88d6@@3_NA=007d88d6

void __fastcall Unknown_006F61F0(int group)
{
    Map.Unknown_0049C980(0);
    Map.Unknown_0049C860(0, false);
    Map.Unknown_0049CA20(0);
    Map.Unknown_0049C7C0(0);
    Map.Unknown_0049CAC0(0);
    unknown_sound_enabled_7d88d6 = true;
    for (int index = 0; index < Technos.Count(); index++) {
        TechnoClass *techno = Technos[index];
        if (techno != 0 && !techno->unknown_76 && techno->unknown_1ac == group - 1) {
            if (Is_Player_Side(techno) && !techno->unknown_77) {
                techno->unknown_slot80();
                unknown_sound_enabled_7d88d6 = false;
            }
        }
    }
    unknown_sound_enabled_7d88d6 = true;
}
