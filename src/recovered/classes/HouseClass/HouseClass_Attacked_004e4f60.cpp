// void HouseClass::Attacked(TechnoClass *source) (0x004E4F60)
// An object of the house was attacked (TS's HouseClass::Attacked; name
// hypothesis). Unless the source declines (slot 31), the player's own house
// gets the base radar event and EVA warning, a house allied to the player the
// ally ones (except, outside the campaign, against a passive source house);
// every attached tag is then offered event 6.
#include "shared/techno.hpp"
#include "shared/radar_event.hpp"
#include "shared/rules.hpp"
#include "shared/tag.hpp"
#include "shared/vox_class.hpp"
// @ref ?Unknown_0063B5B0@@YI_NHVCell@@@Z=0063b5b0
// @ref ?Unknown_00715B40@@YIHPBDHH@Z=00715b40
// @ref ??_C@_0BJ@GFMD@EVA_OurBaseIsUnderAttack?$AA@=007da2b0
// @ref ??_C@_0BJ@CFMC@EVA_OurAllyIsUnderAttack?$AA@=007da294

void HouseClass::Attacked(TechnoClass *source)
{
    if (source != 0 && source->unknown_slot31()) {
        return;
    }
    bool is_player = Is_Player_Control();
    bool is_ally = unknown_player_a35db4 != 0 && unknown_player_a35db4 != this && Is_Ally(unknown_player_a35db4)
        && (unknown_game_mode_a3d298 == 0 || !source->House->Type->MultiplayPassive);
    if (is_player) {
        if (Unknown_0063B5B0(3, Coord_Cell(source->Center_Coord()))) {
            Unknown_00715B40("EVA_OurBaseIsUnderAttack", -1, -1);
            Voc_Play(Rules->BaseUnderAttackSound, 1.0f, 0x2000, 0);
        }
    } else if (is_ally) {
        if (Unknown_0063B5B0(16, Coord_Cell(source->Center_Coord()))) {
            Unknown_00715B40("EVA_OurAllyIsUnderAttack", -1, -1);
            Voc_Play(Rules->BaseUnderAttackSound, 1.0f, 0x2000, 0);
        }
    }
    for (int index = 0; index < unknown_38.Count(); index++) {
        unknown_38[index]->Spring(6, 0, unknown_cell_a40f10);
    }
}
