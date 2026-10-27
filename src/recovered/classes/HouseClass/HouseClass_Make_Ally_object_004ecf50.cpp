// void HouseClass::Make_Ally(ObjectClass *object, bool announce) (0x004ECF50)
#include "shared/techno.hpp"

void HouseClass::Make_Ally(ObjectClass *object, bool announce)
{
    if (object != 0) {
        Make_Ally(object->Owning_House(), announce);
    }
}
