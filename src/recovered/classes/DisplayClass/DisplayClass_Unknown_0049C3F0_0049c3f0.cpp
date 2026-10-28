// void __fastcall Unknown_0049C3F0(ObjectClass *object) (0x0049C3F0)
// The selection band's function for each object in it (DisplayClass slot 48
// passes it to Tactical 0x006AA610): selects one of the player's selectable
// objects; a building only when its type can undeploy (+0x3CC) and is not one
// of the rules' BuildConst types. A successful selection clears 0x007D88D6.
#include "shared/display.hpp"
#include "shared/house_screen.hpp"
#include "shared/techno.hpp"
#include "shared/techno_type.hpp"
#include "shared/building_type_class.hpp"
#include "shared/rules.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_sound_enabled_7d88d6@@3_NA=007d88d6

void __fastcall Unknown_0049C3F0(ObjectClass *object)
{
    HouseClass *house = object->Owning_House();
    BuildingClass *building = object->Kind_Of() == 6 ? (BuildingClass *)object : 0;
    if (house != 0 && house->Unknown_004F52B0() && object->unknown_slot76()) {
        if (building != 0) {
            BuildingTypeClass *type = building->Type;
            if (type->UndeploysInto == 0) {
                return;
            }
            for (int index = 0; index < Rules->unknown_7c8.Count(); index++) {
                if (Rules->unknown_7c8[index] == type) {
                    return;
                }
            }
        }
        if (!object->unknown_76 && object->unknown_slot80()) {
            unknown_sound_enabled_7d88d6 = false;
        }
    }
}
