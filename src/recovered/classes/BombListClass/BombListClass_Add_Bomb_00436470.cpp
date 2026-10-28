// void BombListClass::Add_Bomb(TechnoClass *owner, ObjectClass *target) (0x00436470):
// an infantry (kind 0x0F) plants a timed bomb on a target that has none: the
// bomb goes off IvanTimedDelay frames from now; BombAttachSound plays at the
// target for the owner's house when it is the player's (0x004F52B0).
#include "shared/object.hpp"
#include "shared/techno.hpp"
#include "shared/house.hpp"
// @ref ??2@YAPAXI@Z=00782017
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Frame@@3HA=00a40d2c

void BombListClass::Add_Bomb(TechnoClass *owner, ObjectClass *target)
{
    if (owner != 0 && owner->Kind_Of() == 0x0F && target != 0 && target->unknown_38 == 0) {
        BombClass *bomb = new BombClass;
        bomb->unknown_28 = owner->Owning_House();
        bomb->Owner = owner;
        bomb->Target = target;
        bomb->unknown_34 = Frame;
        bomb->unknown_38 = Rules->IvanTimedDelay + bomb->unknown_34;
        bomb->Type = 0;
        target->unknown_38 = bomb;
        Bombs.Add(bomb);
        unknown_30 = 1;
        if (Rules->BombAttachSound != -1 && owner->House->Unknown_004F52B0()) {
            CoordStruct coord = target->Coord;
            Unknown_00713E60(Rules->BombAttachSound, coord, 0);
        }
    }
}
