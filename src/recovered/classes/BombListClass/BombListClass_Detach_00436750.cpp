// void BombListClass::Detach(AbstractClass *target) (0x00436750): drops
// target from the bombs and from the owner of every bomb.
#include "shared/object.hpp"
#include "shared/techno.hpp"

void BombListClass::Detach(AbstractClass *target)
{
    Bombs.Delete((BombClass *)target);
    for (int index = 0; index < Bombs.Count(); index++) {
        BombClass *bomb = Bombs[index];
        if (bomb != 0 && bomb->Owner == target) {
            bomb->Owner = 0;
        }
    }
}
