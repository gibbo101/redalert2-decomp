// void Unknown_006F5940() (0x006F5940; TabClass::AI and the deploy command 0x0051BF20): the deploy key. A selected
// player building with a positive 0x004532F0 is deployed alone (slot 199 with 9); otherwise every selected
// deployable techno (slot 39 or 38, slots 185 and 186) gets slot 199 with 9, except that when the selection mixes
// deploying and undeployed deployer infantry the deploying ones are left; one sound (Rules +0x64C) when any did.
// The count is read once after the building test; undeployed, the index and deploying are initialised in that
// order (bl, edi, then a stack byte).
#include "shared/uicmnds.hpp"
#include "shared/infantry.hpp"
#include "shared/rules.hpp"
#include "shared/sound_play.hpp"

void Unknown_006F5940()
{
    bool deployed = false;
    if (unknown_objects_a40c60.Count() <= 0) {
        return;
    }
    if (unknown_objects_a40c60[0] != 0) {
        BuildingClass *building = (BuildingClass *)unknown_objects_a40c60[0];
        if (building != 0 && building->Kind_Of() == 6 && building->unknown_4532f0() > 0
            && building->House->Unknown_004F52B0()) {
            ObjectClass *object = unknown_objects_a40c60[0];
            if (object != 0 && object->AbstractFlags.IsTechno && ((TechnoClass *)object)->unknown_slot199(9)) {
                Voc_Play(Rules->unknown_64c, 1.0f, 0x2000, 0);
            }
            return;
        }
    }

    int count = unknown_objects_a40c60.Count();
    bool undeployed = false;
    int index = 0;
    bool deploying = false;
    for (; index < count; index++) {
        ObjectClass *object = unknown_objects_a40c60[index];
        if (object != 0 && object->Kind_Of() == 15 && ((InfantryClass *)object)->unknown_5090a0()) {
            if (((InfantryClass *)object)->unknown_5090d0()) {
                deploying = true;
            } else {
                undeployed = true;
            }
            if (deploying && undeployed) {
                break;
            }
        }
    }

    for (index = 0; index < count; index++) {
        ObjectClass *object = unknown_objects_a40c60[index];
        if (object != 0 && (object->unknown_slot39() || object->unknown_slot38()) && object->AbstractFlags.IsTechno
            && ((TechnoClass *)object)->unknown_slot185() && ((TechnoClass *)object)->unknown_slot186()) {
            if (object->Kind_Of() == 15 && ((InfantryClass *)object)->unknown_5090a0() && deploying && undeployed
                && ((InfantryClass *)object)->unknown_5090d0()) {
                continue;
            }
            if (((TechnoClass *)object)->unknown_slot199(9)) {
                deployed = true;
            }
        }
    }
    if (deployed) {
        Voc_Play(Rules->unknown_64c, 1.0f, 0x2000, 0);
    }
}
