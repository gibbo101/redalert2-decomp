// TechnoClass *__fastcall As_Techno_0040dbd0(AbstractClass *object) -- 0x0040DBD0
// TibSun _rtti.cpp Dynamic_Cast<TechnoClass const *>: the object as a techno when its kind is
// one (1, 2, 6, 15), else null; AbstractClass::As_Techno 0x0040DC20 is the non-const twin.
#include "shared/techno.hpp"

TechnoClass *__fastcall As_Techno_0040dbd0(AbstractClass *object)
{
    if (object != 0) {
        switch (object->Kind_Of()) {
        case 1:
        case 2:
        case 6:
        case 15:
            return (TechnoClass *)object;
        }
    }
    return 0;
}
