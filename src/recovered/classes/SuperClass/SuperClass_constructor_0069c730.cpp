// SuperClass::SuperClass(SuperWeaponTypeClass *type, HouseClass *house) (0x0069C730)
// @ref ?unknown_objects_ac0cb0@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0cb0
// @ref ?unknown_abstracts_ac0d08@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0d08

SuperClass::SuperClass(SuperWeaponTypeClass *type, HouseClass *house) :
    Type(type),
    House(house),
    unknown_0x48(true),
    unknown_0x4A(unknown_cell_abd768),
    Anim(0),
    AnimDetached(false),
    unknown_0x55(false),
    unknown_0x56(false),
    unknown_0x57(false),
    unknown_0x58(false),
    unknown_0x5C(-1),
    unknown_0x60(-1)
{
    Create_ID();
    Supers.Add(this);
    unknown_objects_ac0cb0.Add(this);
    unknown_abstracts_ac0d08.Add(this);
}
