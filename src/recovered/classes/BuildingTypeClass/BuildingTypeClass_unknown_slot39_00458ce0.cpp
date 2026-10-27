// void *BuildingTypeClass::unknown_slot39() const (0x00458CE0, slot 39)
// The building's image, demand-loaded from its own image name (unknown_13eb)
// and, failing that, from the name with the generic theater letter.
#include "shared/building_type.hpp"
#include "shared/cc_file_class.hpp"
// @ref ??0CCFileClass@@QAE@PBD@Z=00468f50
// @ref ?Is_Available@CCFileClass@@UAE_NH@Z=004691a0
// @ref ?Load_Alloc_Data@@YIPAXAAVFileClass@@@Z=00495230
// @ref ?Generic_Naming_Convention@ObjectTypeClass@@SIXPAD@Z=005d7c20
// @ref _strncpy=007823d0

void *__fastcall Load_Alloc_Data(FileClass &file);            // 0x00495230

void *BuildingTypeClass::unknown_slot39() const
{
    BuildingTypeClass *self = (BuildingTypeClass *)this;
    if (unknown_a4 == 0 && DemandLoad) {
        if (unknown_13eb[0] != 0) {
            CCFileClass file(unknown_13eb);
            file.Is_Available();
            self->unknown_a4 = Load_Alloc_Data(file);
            if (unknown_a4 != 0) {
                self->unknown_a8 = true;
            } else {
                char name[260];
                strncpy(name, unknown_13eb, 19);
                Generic_Naming_Convention(name);
                CCFileClass generic(name);
                self->unknown_a4 = Load_Alloc_Data(generic);
                if (unknown_a4 != 0) {
                    self->unknown_a8 = true;
                }
            }
        }
        return unknown_a4;
    }
    return unknown_a4;
}
