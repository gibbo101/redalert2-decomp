// IonBlastClass::IonBlastClass(CoordStruct) (0x00521270): a new blast at
// coord (TibSun ionblast.cpp) joins the list of blasts in progress.
IonBlastClass::IonBlastClass(CoordStruct coord) :
    Coord(coord),
    Lifetime(0),
    unknown_10(0)
{
    IonBlasts.Add(this);
}
