// double TechnoClass::unknown_6d7550(ObjectClass *target, CoordStruct const &coord) (0x006D7550)
// The threat value of a target (hypothesis: Westwood's Evaluate_Object):
// the type's coefficients (Rules' Dumb* set for a house without +0x143)
// weigh the target's weapon against this object's armor (negated when the
// target is already aiming at this object), its SpecialThreatValue, the
// enemy-house bonus, this object's weapon against the target's armor, the
// target's health and the distance beyond the weapon's range (from coord,
// or from this object when coord is the zero coordinate).
#include "shared/techno.hpp"
#include "shared/foot.hpp"
#include "shared/rules.hpp"
#include "shared/weapon_type.hpp"
#include "shared/warhead_type.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?unknown_double_79b610@@3NB=0079b610
// @ref _unknown_geometry_l=00ac0188
// @ref ?Health_Ratio@ObjectClass@@QBENXZ=005d4540
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref __real@8@400fc350000000000000=007ad038

double TechnoClass::unknown_6d7550(ObjectClass *target, CoordStruct const &coord)
{
    TechnoTypeClass *type = unknown_slot32();
    if (target->Class_Of() == 0) {
        return unknown_double_79b610;
    }
    double my_effectiveness;
    double target_effectiveness;
    double target_special_threat;
    double target_strength;
    double target_distance;
    if (House->unknown_143) {
        my_effectiveness = type->MyEffectivenessCoefficient;
        target_effectiveness = type->TargetEffectivenessCoefficient;
        target_special_threat = type->TargetSpecialThreatCoefficient;
        target_strength = type->TargetStrengthCoefficient;
        target_distance = type->TargetDistanceCoefficient;
    } else {
        my_effectiveness = Rules->DumbMyEffectivenessCoefficient;
        target_effectiveness = Rules->DumbTargetEffectivenessCoefficient;
        target_special_threat = Rules->DumbTargetSpecialThreatCoefficient;
        target_strength = Rules->DumbTargetStrengthCoefficient;
        target_distance = Rules->DumbTargetDistanceCoefficient;
    }
    int index = unknown_slot174(target);
    WeaponTypeClass *weapon = unknown_slot231(index)->WeaponType;
    double value = 0;
    int kind = target->Kind_Of();
    if ((kind == 6 || kind == 15 || kind == 1 || kind == 2) && target != 0) {
        TechnoClass *techno = (TechnoClass *)target;
        int their_index = techno->unknown_slot174(this);
        WeaponTypeClass *their_weapon = techno->unknown_slot231(their_index)->WeaponType;
        if (their_weapon != 0 && their_weapon->Warhead != 0) {
            if (techno->unknown_228 == this) {
                value = -(target_effectiveness * their_weapon->Warhead->Verses[type->unknown_9c]);
            } else {
                value = target_effectiveness * their_weapon->Warhead->Verses[type->unknown_9c];
            }
        }
        value += target_special_threat * techno->unknown_slot32()->SpecialThreatValue;
        if (House->unknown_54f0 != -1 && House->unknown_54f0 == techno->House->ArrayIndex) {
            value += Rules->EnemyHouseThreatBonus;
        }
    }
    if (weapon != 0 && weapon->Warhead != 0) {
        value += my_effectiveness * weapon->Warhead->Verses[target->Class_Of()->unknown_9c];
    }
    value += target->Health_Ratio() * target_strength;
    int range;
    if (weapon != 0) {
        range = weapon->unknown_b4;
    } else {
        range = unknown_slot32()->GuardRange.Value;
    }
    range /= 256;
    int distance;
    if (coord != unknown_geometry_l) {
        distance = Offset_Length(coord - target->Center_Coord());
    } else {
        distance = Offset_Length(Center_Coord() - target->Center_Coord()) / 256;
    }
    distance -= range;
    distance = distance < 0 ? 0 : distance;
    value += target_distance * distance;
    return value + 100000.0;
}
