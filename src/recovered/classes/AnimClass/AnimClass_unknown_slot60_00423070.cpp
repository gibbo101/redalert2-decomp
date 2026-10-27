// void AnimClass::unknown_slot60() (0x00423070)
// Stops the animation's sounds: Attach_To(0), resets the first
// audio controller and, unless unknown_178 is set, plays the type's
// StopSound at the center through the second controller; then the
// ObjectClass slot.
#include "shared/anim.hpp"
// @ref ?unknown_slot60@ObjectClass@@UAEXXZ=005d4e90
// @ref ?Unknown_00406070@UnknownAudioController@@QAEXXZ=00406070
// @ref ?Unknown_00713E60@@YIXHABUCoordStruct@@PAVUnknownAudioController@@@Z=00713e60

void AnimClass::unknown_slot60()
{
    Attach_To(0);
    unknown_180.Unknown_00406070();
    if (!unknown_178 && Class->StopSound != -1) {
        Unknown_00713E60(Class->StopSound, Center_Coord(), &unknown_194);
    }
    ObjectClass::unknown_slot60();
}
