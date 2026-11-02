// static void __fastcall OverlayTypeClass::Init(int theater) (0x005DC960)
// Loads the images of the overlays that are not demand-loaded for a
// theater (theater-named, else generic), and frees the theater images of
// the demand-loaded ones.
#include "shared/overlay_type.hpp"
// @ref ??_C@_04BOIE@?4SHP?$AA@=007ced14
#include "shared/cc_file_class.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/anim_type.hpp"
// @ref ?Theaters@@3PAUTheaterTypeStruct@@A=0079ab68
// @ref ?Retrieve@MixFileClass@@SIPBXPBD@Z=005956c0
// @ref ?Theater_Naming_Convention@ObjectTypeClass@@SIXPADH@Z=005d7bd0
// @ref ?Generic_Naming_Convention@ObjectTypeClass@@SIXPAD@Z=005d7c20
// @ref __makepath=007831f0
// @ref ??3@YAXPAX@Z=00781d3b

void __fastcall OverlayTypeClass::Init(int theater)
{
    for (int index = 0; index < OverlayTypes.Count(); index++) {
        OverlayTypeClass *overlay = OverlayTypes[index];
        if (!overlay->DemandLoad) {
            char fullname[512];
            if (overlay->unknown_1fc) {
                _makepath(fullname, 0, 0, overlay->unknown_1c8, Theaters[theater].Suffix);
                overlay->unknown_a4 = (void *)MixFileClass::Retrieve(fullname);
                if (overlay->unknown_a4 == 0) {
                    Generic_Naming_Convention(fullname);
                    overlay->unknown_a4 = (void *)MixFileClass::Retrieve(fullname);
                }
            } else if (overlay->unknown_207) {
                _makepath(fullname, 0, 0, overlay->unknown_1c8, ".SHP");
                Theater_Naming_Convention(fullname, theater);
                overlay->unknown_a4 = (void *)MixFileClass::Retrieve(fullname);
                if (overlay->unknown_a4 == 0) {
                    Generic_Naming_Convention(fullname);
                    overlay->unknown_a4 = (void *)MixFileClass::Retrieve(fullname);
                }
            }
        } else if ((overlay->unknown_1fc || overlay->unknown_207) && overlay->unknown_a4 != 0 && overlay->unknown_a8) {
            operator delete(overlay->unknown_a4);
            overlay->unknown_a4 = 0;
            overlay->unknown_a8 = false;
        }
    }
}
