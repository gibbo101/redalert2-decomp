// void HouseClass::Make_Enemy(int house, bool announce) (0x004E5A50)
#include "shared/techno.hpp"

void HouseClass::Make_Enemy(int house, bool announce)
{
    Make_Enemy(Houses[house], announce);
}
