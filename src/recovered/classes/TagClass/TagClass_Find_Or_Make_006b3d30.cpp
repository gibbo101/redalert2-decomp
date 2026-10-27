// TagClass *__fastcall TagClass::Find_Or_Make(TagTypeClass *type) (0x006B3D30)
// The live tag of a type, created when missing.
#include "shared/object.hpp"

TagClass *__fastcall TagClass::Find_Or_Make(TagTypeClass *type)
{
    for (int index = 0; index < unknown_TagClass_list_00abfe48.Count(); index++) {
        TagClass *tag = unknown_TagClass_list_00abfe48[index];
        if (tag->Class == type) {
            return tag;
        }
    }
    return new TagClass(type);
}
