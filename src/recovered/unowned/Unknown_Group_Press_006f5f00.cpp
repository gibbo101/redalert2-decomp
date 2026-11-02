// void __fastcall Unknown_006F5F00(int group) (0x006F5F00; TabClass::AI): the group-select key. A second press of
// the same group within 25 frames while the group is exactly the selection (0x006F5E80, expanded) re-selects it
// through 0x006F60D0; otherwise the selection is dropped and the group's player-side technos are selected and
// flashed (unknown_13c restarted at Rules->RadarCombatFlashTime), with the effect sound suppressed.
#include "shared/uicmnds.hpp"
#include "shared/map_view.hpp"
#include "shared/rules.hpp"
#include "shared/cd_timer.hpp"
// @ref ?unknown_sound_enabled_7d88d6@@3_NA=007d88d6
void __fastcall Unknown_006F60D0(int group);
// The frame and group of the last group selection (a second press within 25 frames centres the view).
// @ref ?unknown_group_frame_7f8bcc@@3HA=007f8bcc
// @ref ?unknown_group_7f8bd0@@3HA=007f8bd0
extern int unknown_group_frame_7f8bcc;     // 0x007F8BCC
extern int unknown_group_7f8bd0;           // 0x007F8BD0

void __fastcall Unknown_006F5F00(int group)
{
    Map.Unknown_0049C980(0);
    Map.Unknown_0049C860(0, false);
    Map.Unknown_0049CA20(0);
    Map.Unknown_0049C7C0(0);
    Map.Unknown_0049CAC0(0);
    if (Frame - unknown_group_frame_7f8bcc < 25 && group == unknown_group_7f8bd0 && Unknown_006F5E80(group)) {
        Unknown_006F60D0(group);
        return;
    }
    unknown_group_frame_7f8bcc = Frame;
    unknown_group_7f8bd0 = group;
    unknown_selected_83996c->Unknown_006AAD40();
    unknown_sound_enabled_7d88d6 = true;
    for (int index = 0; index < Technos.Count(); index++) {
        TechnoClass *techno = Technos[index];
        if (techno != 0 && !techno->unknown_76 && techno->unknown_1ac == group - 1) {
            if (Is_Player_Side(techno) && !techno->unknown_77) {
                techno->unknown_slot80();
                techno->unknown_13c = CDTimerClass<FrameTimerClass>(Rules->RadarCombatFlashTime);
                unknown_sound_enabled_7d88d6 = false;
            }
        }
    }
    unknown_sound_enabled_7d88d6 = true;
    TechnoClass::unknown_6d7990();
}
