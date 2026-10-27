// void *AnimTypeClass::unknown_slot39() const (0x00426550)
// The image, demand-loading it from its file (theater-named, else generic)
// on first use.
#include "shared/anim_type.hpp"
#include "shared/cc_file_class.hpp"
// @ref ??0CCFileClass@@QAE@PBD@Z=00468f50
// @ref ?Load_Alloc_Data@@YIPAXAAVFileClass@@@Z=00495230
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0

void *AnimTypeClass::unknown_slot39() const
{
    AnimTypeClass *self = (AnimTypeClass *)this;
    if (unknown_a4 == 0 && DemandLoad) {
        Debug_Printf("Demand loading image for %s\n", (char const *)Name);
        char fullname[512];
        _makepath(fullname, 0, 0, unknown_1c8[0] != 0 ? (char const *)unknown_1c8 : (char const *)ID, ".SHP");
        if (unknown_1fc) {
            _makepath(fullname, 0, 0, ID, Theaters[unknown_id_source_a3d290->Theater].Suffix);
        } else if (unknown_207) {
            Theater_Naming_Convention(fullname, unknown_id_source_a3d290->Theater);
        }
        CCFileClass file(fullname);
        self->unknown_a4 = Load_Alloc_Data(file);
        if (unknown_a4 != 0) {
            self->unknown_a8 = true;
        } else {
            Generic_Naming_Convention(fullname);
            CCFileClass generic(fullname);
            self->unknown_a4 = Load_Alloc_Data(generic);
            if (unknown_a4 != 0) {
                self->unknown_a8 = true;
            }
        }
        self->unknown_slot40(unknown_id_source_a3d290->Theater);
        return unknown_a4;
    }
    return unknown_a4;
}
