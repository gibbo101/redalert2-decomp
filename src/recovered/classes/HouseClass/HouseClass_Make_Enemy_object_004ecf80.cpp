// void HouseClass::Make_Enemy(ObjectClass *object, bool announce) (0x004ECF80)
#include "shared/techno.hpp"

void HouseClass::Make_Enemy(ObjectClass *object, bool announce)
{
    if (object != 0) {
        Make_Enemy(object->Owning_House(), announce);
    }
}
