// void DisplayClass::One_Time() (0x00498B70, slot 5)
// Loads the placement and shadow shapes and sizes the tactical view.
#include "shared/display.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/mix_file_class.hpp"
// @ref ?One_Time@MapClass@@UAEXXZ=005480d0
// @ref ?Retrieve@MixFileClass@@SIPBXPBD@Z=005956c0
// @ref ?Unknown_006F1F30@@YI?AVRect@@XZ=006f1f30

void DisplayClass::One_Time()
{
    MapClass::One_Time();
    TransIconset = MixFileClass::Retrieve("PLACE.SHP");
    ShadowShapes = MixFileClass::Retrieve("SHADOW.SHP");
    Rect rect = Unknown_006F1F30();
    unknown_slot42(rect);
}
// @ref ??_C@_09LGJG@PLACE?4SHP?$AA@=007d5d30
// @ref ??_C@_0L@BIBI@SHADOW?4SHP?$AA@=007d5d24
