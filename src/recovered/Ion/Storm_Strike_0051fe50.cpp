// 0x0051FE50: a lightning bolt strikes the cell under coord: a random
// WeatherConBolts anim at the cell's centre joins the bolt list, a random
// LightningSounds sound plays, the LightningWarhead's damage anim, explosion
// and LightningDamage hit the cell's ground coordinate, and unless an object
// of kind 15 stands there, 2-4 MetallicDebris anims fly when the cell's
// building, occupant or level changed or its land type is 1, 3, 4 or 11.
#define VECTOR_IMPLEMENT_ALL
#include "shared/vector_class.hpp"
#include "shared/lightning_storm.hpp"
#include "shared/anim.hpp"
#include "shared/cell.hpp"
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"
#include "shared/rules.hpp"
#include "shared/sound_play.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?StormBoltsPresent@@3V?$DynamicVectorClass@PAVAnimClass@@@@A=00a518c8
// @ref _unknown_geometry_g=00a51930
// @ref _unknown_geometry_j=00a51920
// @ref _unknown_geometry_l=00a518e0
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ??RRandom2Class@@QAEHXZ=00638840
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
// @ref ??AMapClass@@QAEAAVCellClass@@ABUCoordStruct@@@Z=00548000
// @ref ??0AnimClass@@QAE@PBVAnimTypeClass@@ABUCoordStruct@@HHHH@Z=00420110
// @ref ??2@YAPAXI@Z=00782017
// @ref ?unknown_4717b0@CellClass@@QBEPAVObjectClass@@XZ=004717b0
// @ref ?unknown_475d60@CellClass@@QBE?AUCoordStruct@@XZ=00475d60
// @ref ?unknown_471660@CellClass@@QBEPAVObjectClass@@ABUPoint2D@@_NPAV2@@Z=00471660
// @ref ?Unknown_0047F600@@YIXUCoordStruct@@HPAVWarheadTypeClass@@HH@Z=0047f600
// @ref ?Unknown_0047FCC0@@YGHUCoordStruct@@@Z=0047fcc0
// @ref ?Unknown_0047E2C0@@YIXABUCoordStruct@@HHPAVWarheadTypeClass@@H@Z=0047e2c0
// @ref ?Voc_Play_At@@YIPAUAudioEvent@@HABUCoordStruct@@PAUAudioEventHandle@@@Z=00713e60

void __fastcall Storm_Strike_0051FE50(CoordStruct coord)
{
    CellClass &cellptr = Map[coord];
    CoordStruct center = CoordStruct(cellptr.unknown_475d60());
    int pick = unknown_id_source_a3d290->Random()();
    AnimTypeClass *type = Rules->WeatherConBolts[(unsigned)pick % Rules->WeatherConBolts.Count()];
    AnimClass *bolt = new AnimClass(type, center, 0, 1, 0x600, 0);
    StormBoltsPresent.Add(bolt);

    Cell cell = cellptr.MapCoords;
    int level = cellptr.unknown_11b;
    CoordStruct where(cell.X * 256 + 128, cell.Y * 256 + 128,
        ((cellptr.unknown_140 & 0x100) ? unknown_geometry_j : 0) + level * unknown_geometry_g);
    if (where == unknown_geometry_l) {
        return;
    }
    if (Rules->LightningSounds.Count() > 0) {
        int sound = unknown_id_source_a3d290->Random()();
        Voc_Play_At(Rules->LightningSounds[(unsigned)sound % Rules->LightningSounds.Count()], where, 0);
    }
    int land = cellptr.unknown_ec;
    int damage = Rules->LightningDamage;
    AnimTypeClass *anim = Select_Damage_Anim(damage, Rules->LightningWarhead, land, &where);
    new AnimClass(anim, where, 0, 1, 0x2600, Unknown_0047FCC0(where));

    bool changed = false;
    ObjectClass *building = cellptr.unknown_4717b0();
    ObjectClass *object = cellptr.unknown_471660(Point2D(0, 0), false, 0);
    bool sheltered = object != 0 && object->Kind_Of() == 15;
    if (building == 0 && object == 0) {
        switch (cellptr.unknown_ec) {
        case 1:
        case 3:
        case 4:
        case 11:
            changed = true;
            break;
        }
    }
    Unknown_0047F600(where, damage, Rules->LightningWarhead, 0, 0);
    Unknown_0047E2C0(where, damage, 0, Rules->LightningWarhead, 1);
    if (building != cellptr.unknown_4717b0() || object != cellptr.unknown_471660(Point2D(0, 0), false, 0)
        || cellptr.unknown_11b != level) {
        changed = true;
    }
    if (!sheltered && changed) {
        int count = Random_Pick(2, 4);
        for (int index = 0; index < count; index++) {
            new AnimClass(Rules->MetallicDebris[Random_Pick(0, Rules->MetallicDebris.Count() - 1)], where, 0, 1, 0x600, 0);
        }
    }
}
