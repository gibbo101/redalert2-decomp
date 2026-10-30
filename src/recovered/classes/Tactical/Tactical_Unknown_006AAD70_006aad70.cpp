// bool Tactical::Unknown_006AAD70() (0x006AAD70): with exactly one object selected,
// owned by a house that is not the player's (+0x135 in the campaign,
// 0x004F52B0 otherwise), unselects it (slot 81) and returns true (hypothesis).
#include "shared/tactical.hpp"
#include "shared/vector_class.hpp"
#include "shared/object.hpp"
#include "shared/house_screen.hpp"
// @ref ?unknown_objects_a40c60@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00a40c60
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0

bool Tactical::Unknown_006AAD70()
{
    if (unknown_objects_a40c60.Count() == 1) {
        ObjectClass *object = unknown_objects_a40c60[0];
        if (object->Owning_House() != 0) {
            if (unknown_game_mode_a3d298 == 0) {
                if (!object->Owning_House()->unknown_135) {
                    object->unknown_slot81();
                    return true;
                }
            } else if (!object->Owning_House()->Unknown_004F52B0()) {
                object->unknown_slot81();
                return true;
            }
        }
    }
    return false;
}
