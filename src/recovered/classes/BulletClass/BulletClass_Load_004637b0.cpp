// HRESULT __stdcall BulletClass::Load(IStream *stream) (0x004637B0, slot 5)
// Loads the object, rebuilds itself in place, re-registers a pending next
// animation and fixes up its pointers.
#include "shared/bullet.hpp"

HRESULT __stdcall BulletClass::Load(IStream *stream)
{
    HRESULT result = ObjectClass::Load(stream);
    if (SUCCEEDED(result)) {
        new (this) BulletClass(NoInitClass());
        if (NextAnim) {
            unknown_abstracts_ac0bf8.Add(this);
        }
        Swizzle_Pointer(Type);
        Swizzle_Pointer(Owner);
        Swizzle_Pointer(WH);
        Swizzle_Pointer(Target);
        Swizzle_Pointer(WeaponType);
        Swizzle_Pointer(NextAnim);
    }
    return result;
}
