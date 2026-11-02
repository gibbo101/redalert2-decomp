// DynamicVectorClass<char const *> *__fastcall Unknown_Type_Names_006F84A0(DynamicVectorClass<ObjectClass *> const &objects) (0x006F84A0)
// The distinct type names (ID, +0x24 of the object's type) of a list of
// objects, in order of first appearance, in a new list (0x006F76C0 for any
// list; here the name search and the add are expanded inline). No callers
// in the image.
#include "shared/uicmnds.hpp"
#include "shared/crt_string.hpp"
#include "shared/object_type.hpp"

int __fastcall unknown_find_name_index(DynamicVectorClass<char const *> const &names, char const *name);

DynamicVectorClass<char const *> *__fastcall Unknown_Type_Names_006F84A0(DynamicVectorClass<ObjectClass *> const &objects)
{
    DynamicVectorClass<char const *> *names = new DynamicVectorClass<char const *>(0, 0);
    int count = objects.Count();
    for (int index = 0; index < count; index++) {
        char const *name = objects[index]->Class_Of()->ID;
        if (unknown_find_name_index(*names, name) == -1) {
            names->Add(name);
        }
    }
    return names;
}
