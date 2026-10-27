// TagTypeClass::TagTypeClass(char const *ini_name) (0x006B4570)
// A volatile tag with no triggers, named after its ID; registered in the tag
// type list (its index) and the abstract list.
#include "shared/object.hpp"
// @ref ??0AbstractTypeClass@@QAE@PBD@Z=00410580
// @ref ?unknown_TagTypeClass_list_00abfea0@@3V?$DynamicVectorClass@PAVTagTypeClass@@@@A=00abfea0
// @ref ?unknown_objects_ac0cb0@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0cb0
// @ref _strncpy=007823d0

TagTypeClass::TagTypeClass(char const *ini_name) :
    AbstractTypeClass(ini_name),
    ArrayIndex(-1),
    Persistence(0),
    Triggers(0)
{
    Name = FixedString<49>(ID);
    ArrayIndex = unknown_TagTypeClass_list_00abfea0.Count();
    unknown_TagTypeClass_list_00abfea0.Add(this);
    unknown_objects_ac0cb0.Add(this);
}
