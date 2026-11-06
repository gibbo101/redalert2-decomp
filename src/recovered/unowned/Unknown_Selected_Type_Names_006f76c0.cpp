// DynamicVectorClass<char const *> *Unknown_006F76C0() (0x006F76C0)
// The distinct type names (ID, +0x24 of the object's type) of the selected objects (0x00A40C60),
// in order of first appearance, in a new list. The name search is the inline strcmp loop of
// 0x006F6C90.
// @ref ?unknown_objects_a40c60@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00a40c60
#include "shared/uicmnds.hpp"
#include "shared/crt_string.hpp"
#include "shared/object_type.hpp"

int __fastcall unknown_find_name_index(DynamicVectorClass<char const *> const &names, char const *name);

DynamicVectorClass<char const *> *Unknown_006F76C0()
{
    DynamicVectorClass<char const *> *names = new DynamicVectorClass<char const *>(0, 0);
    int count = unknown_objects_a40c60.Count();
    for (int index = 0; index < count; index++) {
        char const *name = unknown_objects_a40c60[index]->Class_Of()->ID;
        if (unknown_find_name_index(*names, name) == -1) {
            names->Add(name);
        }
    }
    return names;
}
