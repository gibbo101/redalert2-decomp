// SuperWeaponTypeClass *__fastcall SuperWeaponTypeClass::From_Action(int action) (0x0069F7E0)

SuperWeaponTypeClass *__fastcall SuperWeaponTypeClass::From_Action(int action)
{
    for (int index = 0; index < SuperWeaponTypes.Count(); index++) {
        if (SuperWeaponTypes[index]->Action == action) {
            return SuperWeaponTypes[index];
        }
    }
    return 0;
}
