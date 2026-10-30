// void CellClass::unknown_47bc80() (0x0047BC80): Westwood's Fog_Cell. With
// fog of war on, walks the seven cells down the diagonal from this one; each
// whose level (+0x11B) is within two below 1, 3, .., 15 in turn and is not yet
// fogged (+0x140 flag 0x400000) is fogged: its buildings leave fogged copies in
// a new list, other units are unselected.
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/building_class.hpp"
#include "shared/fogged_object.hpp"
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ??_7?$DynamicVectorClass@PAVFoggedObjectClass@@@@6B@=0079d17c
// @ref ??_E?$DynamicVectorClass@PAVFoggedObjectClass@@@@UAEPAXI@Z=00454850
// @ref ?Resize@?$DynamicVectorClass@PAVFoggedObjectClass@@@@UAE_NHPBQAVFoggedObjectClass@@@Z=004543d0
// @ref ?Clear@?$DynamicVectorClass@PAVFoggedObjectClass@@@@UAEXXZ=00453d80
// @ref ?ID@?$DynamicVectorClass@PAVFoggedObjectClass@@@@UAEHABQAVFoggedObjectClass@@@Z=00454480
// @ref ?ID@?$DynamicVectorClass@PAVFoggedObjectClass@@@@UAEHPBQAVFoggedObjectClass@@@Z=00453db0
// @ref ??_7?$VectorClass@PAVFoggedObjectClass@@@@6B@=0079d19c
// @ref ??_E?$VectorClass@PAVFoggedObjectClass@@@@UAEPAXI@Z=004549e0
// @ref ??8?$VectorClass@PAVFoggedObjectClass@@@@UBE_NABV0@@Z=00454390
// @ref ?Resize@?$VectorClass@PAVFoggedObjectClass@@@@UAE_NHPBQAVFoggedObjectClass@@@Z=004548a0
// @ref ?Clear@?$VectorClass@PAVFoggedObjectClass@@@@UAEXXZ=00454950
// @ref ?ID@?$VectorClass@PAVFoggedObjectClass@@@@UAEHABQAVFoggedObjectClass@@@Z=00454980
// @ref ?ID@?$VectorClass@PAVFoggedObjectClass@@@@UAEHPBQAVFoggedObjectClass@@@Z=004549c0
// @ref ?Fetch@?$VectorClass@PAVFoggedObjectClass@@@@UBEPAVFoggedObjectClass@@H@Z=00453dd0
void CellClass::unknown_47bc80()
{
    if (unknown_id_source_a3d290->unknown_000 & 0x1000) {
        Cell cell = MapCoords;
        for (int level = 1; level <= 15; level += 2) {
            CellClass &other = Map[cell];
            if (other.unknown_11b >= level - 2 && other.unknown_11b <= level) {
                if (!(other.unknown_140 & 0x400000)) {
                    DynamicVectorClass<FoggedObjectClass *> *fogged = new DynamicVectorClass<FoggedObjectClass *>;
                    fogged->Resize(1);
                    fogged->Set_Growth_Step(1);
                    other.unknown_140 |= 0x400000;
                    for (ObjectClass *object = other.OccupierPtr; object != 0; object = object->unknown_30) {
                        int kind = object->What_Am_I();
                        if (kind == 6) {
                            BuildingClass *building = (BuildingClass *)object;
                            building->unknown_slot104();
                            if (building->unknown_452be0()) {
                                bool fade;
                                if (building->unknown_slot31() || building->unknown_5bd == 15) {
                                    fade = false;
                                } else {
                                    fade = true;
                                }
                                building->Create_Fogged_Copy_00452c70(fogged, &other, fade);
                            }
                        } else if (kind == 1 || kind == 2 || kind == 0x0F) {
                            object->unknown_slot81();
                        }
                    }
                    if (fogged->Count() > 0) {
                        other.FoggedObjects = fogged;
                    } else {
                        delete fogged;
                    }
                }
            }
            cell.X++;
            cell.Y++;
        }
    }
}
