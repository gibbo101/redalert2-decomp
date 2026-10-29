// float HouseClass::unknown_func_4f5a20(TechnoTypeClass *type) (0x004F5A20)
// The owner country's multiplier for the type's kind (infantry, vehicle or
// aircraft; FootClass 0x004C9B10 reads it); 1 otherwise.
// @ref __real@4@3fff8000000000000000=0079b7f8
#include "shared/techno.hpp"
#include "shared/house_views.hpp"

float HouseClass::unknown_func_4f5a20(TechnoTypeClass *type)
{
    switch (type->Kind_Of()) {
    case 16:
        return Type->unknown_0x128;
    case 40:
        return Type->unknown_0x12C;
    case 3:
        return Type->unknown_0x130;
    }
    return 1.0f;
}
