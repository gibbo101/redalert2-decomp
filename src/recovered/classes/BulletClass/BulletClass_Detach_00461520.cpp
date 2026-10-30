// void BulletClass::Detach(AbstractClass *target, bool all) (0x00461520)
// Forgets a target that is being removed: the owner, the target (re-aimed at the
// cell under it when it is a plain object), the type, weapon and next animation;
// a bullet being removed with all is also dropped from the bullet list.
#include "shared/bullet.hpp"
#include "shared/bullet_type.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/unknown_static_rect.hpp"
#define SHAPE_FILE_EMPTY_RECT unknown_static_rect
#include "shared/techno.hpp"
#include "shared/anim.hpp"
#include "shared/weapon_type.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
// @ref ?Detach@ObjectClass@@UAEXPAVAbstractClass@@_N@Z=005d3bd0

// The cell under an object's centre (inline; its Cell construction sits three
// levels deep in Detach, where /Ob2's divided budget leaves 0x0042AD30 out of
// line as in the original; Inline248).
inline Cell Cell_Of(AbstractClass *object)
{
    return Coord_Cell_Of(object->Center_Coord());
}

// Re-aims a bullet whose target is going away at the cell under that target,
// or clears it (inline helper of Detach).
inline void Retarget(BulletClass *self)
{
    Cell cell = Cell_Of(self->Target);
    if (unknown_a40774 == 0 && !self->Target->unknown_slot21() && cell != unknown_geometry_k) {
        self->Target = &Map[cell];
    } else {
        self->Target = 0;
    }
}

void BulletClass::Detach(AbstractClass *target, bool all)
{
    ObjectClass::Detach(target, all);
    if (Owner == target) {
        Owner = 0;
    }
    if (Target == target) {
        Retarget(this);
    }
    if (Type == target) {
        Type = 0;
    }
    if (WeaponType == target) {
        WeaponType = 0;
    }
    if (NextAnim == target) {
        NextAnim = 0;
    }
    if (all && target->Kind_Of() == 8) {
        BulletClass *bullet = (BulletClass *)target;
        if (Type_View(bullet->Type)->unknown_2bc) {
            for (int i = 0; i < Array.Count(); i++) {
                if (bullet == Array[i]) {
                    Array.Delete(bullet);
                    return;
                }
            }
        }
    }
}
