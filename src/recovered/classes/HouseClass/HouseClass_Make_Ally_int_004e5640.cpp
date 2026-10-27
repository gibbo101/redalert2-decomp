// void HouseClass::Make_Ally(int house, bool announce) (0x004E5640)
#include "shared/techno.hpp"

void HouseClass::Make_Ally(int house, bool announce)
{
    Make_Ally(Houses[house], announce);
}
