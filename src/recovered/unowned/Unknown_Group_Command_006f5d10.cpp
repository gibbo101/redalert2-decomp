// void Unknown_006F5D10() (0x006F5D10)
// Answers a group command (hypothesis): when every listed object that is
// an object and passes slot 39 also answers slot 199 (7), the rules' +0x648
// sound plays; one refusal silences it.
#include "shared/uicmnds.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_objects_a40c60@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00a40c60
// @ref ?Voc_Play@@YIPAUAudioEvent@@HMHPAUAudioEventHandle@@@Z=00713db0

void Unknown_006F5D10()
{
    if (unknown_objects_a40c60.Count() > 0) {
        char agreed = 1;
        int count = unknown_objects_a40c60.Count();
        for (int index = 0; index < count; index++) {
            ObjectClass *object = unknown_objects_a40c60[index];
            if (object != 0 && object->AbstractFlags.IsTechno && object->unknown_slot39()) {
                agreed = (char)((TechnoClass *)object)->unknown_slot199(7);
                if (!agreed) {
                    break;
                }
            }
        }
        if (agreed) {
            Voc_Play(Rules->unknown_648, 1.0f, 0x2000, 0);
        }
    }
}
