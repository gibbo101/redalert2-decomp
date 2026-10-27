// WeaponTypeClass::Load (0x00733C90)
// Clears the sound list, loads the base object, restores the weapon type in
// place, rebuilds both lists from their saved counts and entries, and swizzles
// the projectile, warhead, attached particle system, assault animation and the
// animation list entries.
#include "shared/weapon_type.hpp"
// @ref ?Load@AbstractClass@@UAGJPAUIStream@@@Z=00410120

HRESULT __stdcall WeaponTypeClass::Load(IStream *stream)
{
    unknown_bc.Clear();
    HRESULT result = AbstractClass::Load(stream);
    if (FAILED(result)) {
        return result;
    }
    new (this) WeaponTypeClass(NoInitClass());
    Anim.Load(stream);
    unknown_bc.Load(stream);
    Swizzle_Pointer(Warhead);
    Swizzle_Pointer(Projectile);
    Swizzle_Pointer(unknown_f8);
    Swizzle_Pointer(unknown_f4);
    for (int index = 0; index < Anim.Count(); index++) {
        Swizzle_Pointer(Anim[index]);
    }
    return S_OK;
}
