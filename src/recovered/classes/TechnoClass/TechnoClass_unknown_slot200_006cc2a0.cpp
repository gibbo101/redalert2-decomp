// bool TechnoClass::unknown_slot200(int mission, AbstractClass *target, int destination, int follow) (0x006CC2A0, slot 200)
// The player orders a mission: a move or attack (1, 2) becomes 0x1D while
// 0x006F6670 and slot 275 hold; planning mode records a MEGAMISSION event
// instead; otherwise the mission's voice plays and the MEGAMISSION is queued.
#include "shared/techno.hpp"
#include "shared/techno_type.hpp"
#include "shared/event.hpp"
#include "shared/target.hpp"
#include "shared/planning.hpp"
#include "shared/queue.hpp"
#include "shared/sound_play.hpp"
#include "shared/random2.hpp"
// @ref ??0TargetClass@@QAE@PAVAbstractClass@@@Z=006b54a0
// @ref ?Planning_Active@@YA_NXZ=00614840
// @ref ?Unknown_006F6670@@YA_NXZ=006f6670
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?Voc_Play@@YIPAUAudioEvent@@HMHPAUAudioEventHandle@@@Z=00713db0
// @ref ?unknown_random_839218@@3VRandom2Class@@A=00839218
// @ref ?unknown_sound_enabled_7d88d6@@3_NA=007d88d6

bool Planning_Active();
bool Unknown_006F6670();

bool TechnoClass::unknown_slot200(int mission, AbstractClass *target, int destination, int follow)
{
    bool special = Unknown_006F6670() && unknown_slot275();
    if ((mission == 2 || mission == 1) && special) {
        mission = 0x1D;
    }
    if (Planning_Active()) {
        EventClass event(unknown_player_a35db4->ArrayIndex, TargetClass(this), (unsigned char)mission, target, (AbstractClass *)destination, (AbstractClass *)follow);
        Planning_Send_Event(event);
        return false;
    }
    if (unknown_sound_enabled_7d88d6) {
        if (mission == 1) {
            unknown_slot198();
        } else if (mission == 2) {
            unknown_slot197();
        } else if (mission == 7) {
            if (unknown_slot32()->VoiceEnter != -1) {
                Voc_Play(unknown_slot32()->VoiceEnter, 1.0f, 0x2000, 0);
            } else {
                unknown_slot197();
            }
        } else if (mission == 8) {
            if (unknown_slot32()->VoiceCapture != -1) {
                Voc_Play(unknown_slot32()->VoiceCapture, 1.0f, 0x2000, 0);
            } else if (unknown_slot32()->VoiceEnter != -1) {
                Voc_Play(unknown_slot32()->VoiceEnter, 1.0f, 0x2000, 0);
            } else {
                unknown_slot197();
            }
        } else if (unknown_slot32()->VoiceSpecialAttack.Count() > 0) {
            DynamicVectorClass<int> &sounds = unknown_slot32()->VoiceSpecialAttack;
            unsigned random = unknown_random_839218();
            Voc_Play(sounds[random % sounds.Count()], 1.0f, 0x2000, 0);
        }
    }
    {
        TargetClass destination_target((AbstractClass *)destination);
        TargetClass target_target(target);
        Queue_Mission(TargetClass(this), mission, target_target, destination_target);
    }
    return true;
}
