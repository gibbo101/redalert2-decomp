// void HouseClass::Set_Factory(FactoryClass *factory, int kind, bool naval, int buildcat) (0x004EB8C0)
// Stores the house's factory for an object kind (the slots unknown_func_4eb580
// reads; name after TS's HouseClass::Set_Factory).
#include "shared/techno.hpp"

void HouseClass::Set_Factory(FactoryClass *factory, int kind, bool naval, int buildcat)
{
    switch (kind) {
    case 1:
    case 40:
        if (naval) {
            unknown_52e4 = factory;
        } else {
            unknown_52e0 = factory;
        }
        break;
    case 15:
    case 16:
        unknown_52dc = factory;
        break;
    case 6:
    case 7:
        if (buildcat == 5) {
            unknown_52f8 = factory;
        } else {
            unknown_52e8 = factory;
        }
        break;
    case 2:
    case 3:
        unknown_52d8 = factory;
        break;
    }
}
