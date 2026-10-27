// TagTypeClass *__fastcall TagTypeClass::From_Name(char const *name) (0x006B4880)
// The tag type whose ID or name matches, or 0.
#include "shared/object.hpp"

TagTypeClass *__fastcall TagTypeClass::From_Name(char const *name)
{
    if (name != 0) {
        for (int index = 0; index < unknown_TagTypeClass_list_00abfea0.Count(); index++) {
            TagTypeClass *type = unknown_TagTypeClass_list_00abfea0[index];
            if (!_stricmp(type->ID, name) || !_stricmp(type->Name, name)) {
                return type;
            }
        }
    }
    return 0;
}
