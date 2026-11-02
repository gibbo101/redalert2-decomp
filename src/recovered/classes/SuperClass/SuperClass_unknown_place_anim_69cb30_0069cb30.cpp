// void SuperClass::unknown_place_anim_69cb30(CoordStruct coord) (0x0069CB30)
// Replaces the super weapon's animation with Rules->ChronoPlacement 5 leptons
// above coord and joins the animated supers (hypothesis: the chronosphere's
// placement marker).
// @ref ?unknown_abstracts_ac0bf8@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0bf8
// @ref ??0AnimClass@@QAE@PAVAnimTypeClass@@ABUCoordStruct@@HHHH@Z=00420110
// @ref ??2@YAPAXI@Z=00782017

void SuperClass::unknown_place_anim_69cb30(CoordStruct coord)
{
    unknown_69ca70();
    AnimClass *anim = new AnimClass(Rules->ChronoPlacement, coord + CoordStruct(0, 0, 5), 0, 1, 0x600, 0);
    if (anim != 0) {
        Anim = anim;
        unknown_abstracts_ac0bf8.Add(this);
    }
}
