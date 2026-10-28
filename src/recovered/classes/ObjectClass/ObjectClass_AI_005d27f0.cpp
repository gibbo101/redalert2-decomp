// ObjectClass::AI005D27F0; original709+11.
// Private strict candidate; field/source type hypotheses remain explicit.
// Source types/field meanings remain explicit recovery hypotheses.
#include "shared/object_type.hpp"
#include "shared/anim.hpp"
#include "shared/anim_type.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#include "shared/rules.hpp"
extern double const unknown_falling_decrement_007a7668;
// @ref ?unknown_falling_decrement_007a7668@@3NB=007a7668
// @ref ?Voc_Play_At@@=00713e60
// @ref ?Unknown_00420D30@@=00420d30
// @ref ??0AnimClass@@=00420110

static inline CoordStruct Object_AI_Splash_Coord(ObjectClass const *object)
{
    CoordStruct result = object->Coord;
    result.Z = (int)((unsigned int)result.Z + 3u);
    return result;
}

static inline int Object_AI_Clamped_Speed(int floor, int speed)
{
    return speed > floor ? speed : floor;
}

void ObjectClass::AI()
{
    if (!unknown_76) {
        if (Class_Of() && Class_Of()->unknown_1c4 != -1) {
            CoordStruct current = Coord;
            Voc_Play_At(Class_Of()->unknown_1c4, current, &unknown_3c);
        }
        int sound = unknown_64;
        if (sound != -1) {
            CoordStruct current = Coord;
            Voc_Play_At(sound, current, &unknown_50);
        }
    }
    if (!unknown_7a) return;

    int previous_state = unknown_slot29();
    int new_height = (int)((unsigned int)unknown_slot110() +
                          (unsigned int)unknown_24.unknown_08);
    if (unknown_74) {
        unknown_slot71(0);
        Coord.Z = new_height;
        unknown_slot71(1);
    } else {
        Coord.Z = new_height;
    }
    if (unknown_slot108() <= 0) {
        unknown_slot109(0);
        unknown_7a = false;
        unknown_slot93(2);
        Unknown_00420D30(this);
    }
    if (!unknown_76) {

        int velocity;
        if (unknown_78) velocity = Object_AI_Clamped_Speed(Rules->ParachuteMaxFallRate, (unknown_24.unknown_08 = (int)((unsigned int)unknown_24.unknown_08 - 1u)));
        else velocity = Object_AI_Clamped_Speed(Rules->NoParachuteMaxFallRate, (unknown_24.unknown_08 = (int)((double)unknown_24.unknown_08 - unknown_falling_decrement_007a7668)));
        unknown_24.unknown_08 = velocity;
        if (previous_state != unknown_slot29()) Map.Submit(this);
        if (!unknown_7a) {
        if (unknown_7c && Strength > 0) {
            int damage = Strength;
            unknown_slot86(&damage, 0, Rules->unknown_c74, 0, true, 1);
        }
        if (Kind_Of() == 4) {
            AnimClass *animation = static_cast<AnimClass *>(this);
            if (animation->Class->IsFlamingGuy) {
                animation->unknown_17a = true;
                animation->Set_Rate(1);
                animation->Stage = (int)((unsigned int)animation->Class->RunningFrames * 8u + 1u);
                if (Map[CoordStruct(Coord)].unknown_ec == 2) {
                    // New allocates before evaluating constructor arguments on this target.
                    // The coordinate helper copies after allocation, as the original does.
                    new AnimClass(Rules->SplashList[0], Object_AI_Splash_Coord(this), 0, 1, 0x600, 0);
                }
            }
        }
        }
    } else {
        Map.Remove(this);
    }
}
