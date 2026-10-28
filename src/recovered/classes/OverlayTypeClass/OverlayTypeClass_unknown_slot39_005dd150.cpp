// void *OverlayTypeClass::unknown_slot39() const (0x005DD150)
// The image, demand-loading it from its file (theater-named) on first use.
#include "shared/overlay_type.hpp"
// @ref ??_C@_0BN@LGMO@Demand?5loading?5image?5for?5?$CFs?6?$AA@=007cf014
#include "shared/anim_type.hpp"
#include "shared/cc_file_class.hpp"
// @ref ??0CCFileClass@@QAE@PBD@Z=00468f50
// @ref ??_GCCFileClass@@UAEPAXI@Z=004019a0
// @ref ??_GCDFileClass@@UAEPAXI@Z=00401950
// @ref ?File_Name@RawFileClass@@UBEPBDXZ=00401940
// @ref ?Load_Alloc_Data@@YIPAXAAVFileClass@@@Z=00495230
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ?Theaters@@3PAUTheaterTypeStruct@@A=0079ab68
// @ref ?Theater_Naming_Convention@ObjectTypeClass@@SIXPADH@Z=005d7bd0
// @ref __makepath=007831f0

void *OverlayTypeClass::unknown_slot39() const
{
    OverlayTypeClass *self = (OverlayTypeClass *)this;
    if (unknown_a4 == 0 && DemandLoad) {
        Debug_Printf("Demand loading image for %s\n", (char const *)Name);
        char fullname[512];
        if (unknown_1fc) {
            _makepath(fullname, 0, 0, unknown_1c8, Theaters[unknown_id_source_a3d290->Theater].Suffix);
        } else if (unknown_207) {
            _makepath(fullname, 0, 0, unknown_1c8, ".SHP");
            Theater_Naming_Convention(fullname, unknown_id_source_a3d290->Theater);
        }
        CCFileClass file(fullname);
        self->unknown_a4 = Load_Alloc_Data(file);
        if (unknown_a4 != 0) {
            self->unknown_a8 = true;
        }
        return unknown_a4;
    }
    return unknown_a4;
}
