// float __fastcall Percent_Value(char const *text) (0x007200C0)
#include "shared/warhead_type.hpp"

// The abstract list every warhead type joins; declared here because
// object.hpp declares it with element type ObjectClass * and WarheadType.cpp
// does not include object.hpp (0x00AC0CB0; RTTI element type
// AbstractClass *, declared as ObjectClass * in object.hpp).
extern DynamicVectorClass<AbstractClass *> unknown_objects_ac0cb0;


float __fastcall Percent_Value(char const *text)
{
    if (strchr(text, '%')) {
        return atoi(text) * 0.01;
    }
    return atof(text);
}
