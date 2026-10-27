// bool TerrainClass::unknown_slot88() (0x006E3D90)
// A burning ordinary terrain object (type kind 6, not a tiberium spawner)
// that is not yet burning starts one of two flame animations 80 leptons
// above its center (one in front of it), and ends in the burning state.
#include "shared/terrain.hpp"
#include "shared/anim.hpp"
#include "shared/rules.hpp"
#include "shared/random.hpp"
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ??RRandom2Class@@QAEHXZ=00638840
// @ref ??2@YAPAXI@Z=00782017
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ??0AnimClass@@QAE@PAVAnimTypeClass@@ABUCoordStruct@@HHHH@Z=00420110
// @ref ?Attach_To@AnimClass@@QAEXPAVObjectClass@@@Z=00422540

bool TerrainClass::unknown_slot88()
{
    if (!unknown_b5 && !unknown_b4 && Class->unknown_9c == 6 && !Class->SpawnsTiberium) {
        int pick = unknown_id_source_a3d290->Random()();
        AnimClass *anim = new AnimClass(Rules->TreeFire[pick & 1], Center_Coord() + CoordStruct(0, 0, 80), 0, 255, 0x600, 0);
        if (anim) {
            anim->Attach_To(this);
        }
        anim->ZAdjust -= 20;
        unknown_b4 = true;
        return true;
    }
    return false;
}
