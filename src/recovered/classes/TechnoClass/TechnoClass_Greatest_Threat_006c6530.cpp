// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
// @ref ?Aircraft@@3V?$DynamicVectorClass@PAVAircraftClass@@@@A=00a40398
// @ref ?Has_Turret_Weapons@TechnoTypeClass@@QBE_NXZ=006df680
// @ref ?Is_Ally@HouseClass@@QBE_NPBV1@@Z=004e5540
// @ref ?Is_Ally@HouseClass@@QBE_NPBVTechnoClass@@@Z=004e5580
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Technos@@3V?$DynamicVectorClass@PAVTechnoClass@@@@A=00a40c20
// @ref ?Unknown_0054AAB0@MapClass@@QAE_NABVCell@@@Z=0054aab0
// @ref ?Zone@MapClass@@QAEHABVCell@@H_N@Z=0054f8f0
// @ref ?unknown_6c16f0@TechnoClass@@QAEHH@Z=006c16f0
// @ref ?unknown_6c5570@TechnoClass@@QAE_NHHHPAVObjectClass@@PAHHPBUCoordStruct@@@Z=006c5570
// @ref ?unknown_6c6130@TechnoClass@@QAE_NHHPBVCell@@HPAPAVObjectClass@@PAHH@Z=006c6130
// @ref ?unknown_6c6350@TechnoClass@@QAEHPBVCell@@@Z=006c6350
// @ref ?unknown_cell_ac0148@@3VCell@@A=00ac0148
// @ref ?unknown_func_4f52f0@HouseClass@@QAE_NXZ=004f52f0
// @ref ?unknown_tracker_839ea0@@3UUnknownTracker839EA0@@A=00839ea0
// Target scan: original Techno primary slot219. Flags are retained as target values.
#include "shared/techno.hpp"
#include "shared/aircraft.hpp"
#include "shared/infantry.hpp"
#include "shared/infantry_type.hpp"
#include "shared/house.hpp"
#include "shared/map_view.hpp"
#include "shared/cell.hpp"
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#include "shared/vector_class.hpp"
extern int unknown_target_scan_a40be4;
extern CoordStruct unknown_coord_ac0188;
// @ref ?unknown_target_scan_a40be4@@3HA=00a40be4
// @ref ?unknown_coord_ac0188@@3UCoordStruct@@A=00ac0188
// @ref ?Unknown_004128A0@UnknownTracker839EA0@@QAEXPAVCellClass@@H@Z=004128a0
// @ref ?Fetch_Next_004134e0@UnknownTracker839EA0@@QAEPAVTechnoClass@@XZ=004134e0
AbstractClass *TechnoClass::unknown_slot219(int method, CoordStruct const *coord, bool only_enemy)
{
    ObjectClass *best_object=0;
    int best_value=-1;
    int zone=-1;
    ++unknown_target_scan_a40be4;
    if (unknown_slot32()->NoAutoFire && House->unknown_func_4f52f0()) return 0;
    if (!(method&1) && Kind_Of()!=6 && Kind_Of()!=2) {
        zone=Map.Zone(Cell(Center_Coord()),unknown_slot32()->MovementZone,true);
    }
    if (Kind_Of()==15) {
        if (unknown_6c16f0(-1)<0) method=(method&3)|0x4008;
        else if (static_cast<InfantryClass *>(this)->Type->Engineer) method&=~0x18;
    } else if (Kind_Of()==1) {
        if (unknown_6c16f0(-1)<0) method=(method&3)|0x4010;
    }
    int mask=0;
    if (method&0x100) mask=0x8042;
    if (method&4) mask|=4;
    if (method&0x1ba60) mask|=0x40;
    if (method&8) mask|=0x8000;
    if (method&0x50) mask|=2;
    if (unknown_slot32()->DistributedFire) {
        unknown_3a8.Clear();
        unknown_390.Clear();
    }
    if (method&3) {
        int range=0;
        if (method&1) range=unknown_slot188(0);
        else if (method&2) {
            if (Mission==25) range=unknown_slot188(2);
            else range=unknown_slot188(1);
        }
        if (unknown_6c16f0(-1)<0 && Mission==5) range=512;
        int cell_range=range/256;
        if (!range) {
            if (unknown_slot32()->Has_Turret_Weapons()) cell_range=unknown_slot85(unknown_10c)/256;
            else if (unknown_slot32()->Underwater && unknown_slot32()->Organic && unknown_slot32()->SelfHealing) cell_range=unknown_slot32()->GuardRange.Value/256;
            else cell_range=((unknown_slot85(0)>unknown_slot85(1)) ? unknown_slot85(0):unknown_slot85(1))/256;
            ++cell_range;
            cell_range+=unknown_slot32()->AirRangeBonus/256;
        }
        Cell center(*coord);
        if (method&4) {
            int air_mask=mask|0x8002;
            unknown_tracker_839ea0.Unknown_004128A0(&Map[center],cell_range);
            TechnoClass *object=unknown_tracker_839ea0.Fetch_Next_004134e0();
            while (object) {
                int value=0;
                if (!House->Is_Ally(object) && (!(method&0x4000) || House->Is_Ally(object->House)) && object->unknown_74 && object->unknown_slot29()!=2 && (!only_enemy || object->House->ArrayIndex==House->unknown_54f0) && unknown_6c5570(method,air_mask,range,object,&value,-1,&unknown_coord_ac0188)) {
                    if (unknown_slot32()->DistributedFire) {
                        unknown_3a8.Add(object);
                        unknown_390.Add(value);
                    }
                    if (value>best_value) { best_object=object;best_value=value; }
                }
                object=unknown_tracker_839ea0.Fetch_Next_004134e0();
            }
        }
        if (method&0x10) mask|=4;
        if (!(method^5)) return best_object;
        {
            Cell best_cell(0,0);
            int best_cell_value=0;
            ObjectClass *object;
            int value;
            for (int radius=0;radius<cell_range;++radius) {
                for (int x=-radius;x<=radius;++x) {
                    Cell scan=center+Cell(x,-radius);
                    if (Map.Unknown_0054AAB0(scan)) {
                        if (unknown_6c6130(method,mask,&scan,range,&object,&value,zone) && object && (!only_enemy || static_cast<TechnoClass *>(object)->House->ArrayIndex==House->unknown_54f0) && (!(method&0x4000) || House->Is_Ally(static_cast<TechnoClass *>(object)->House))) {
                            if (unknown_slot32()->DistributedFire) { unknown_3a8.Add(object);unknown_390.Add(value); }
                            if (best_value<value) { best_object=object;best_value=value; }
                        }
                        if (!best_object) {
                            value=unknown_6c6350(&scan);
                            if (best_cell_value<value) {best_cell_value=value;best_cell=scan;}
                        }
                    }
                    scan=center+Cell(x,radius);
                    if (Map.Unknown_0054AAB0(scan)) {
                        if (unknown_6c6130(method,mask,&scan,range,&object,&value,zone) && object && (!only_enemy || static_cast<TechnoClass *>(object)->House->ArrayIndex==House->unknown_54f0) && (!(method&0x4000) || House->Is_Ally(static_cast<TechnoClass *>(object)->House))) {
                            if (unknown_slot32()->DistributedFire) { unknown_3a8.Add(object);unknown_390.Add(value); }
                            if (best_value<value) { best_object=object;best_value=value; }
                        }
                        if (!best_object) {
                            value=unknown_6c6350(&scan);
                            if (best_cell_value<value) {best_cell_value=value;best_cell=scan;}
                        }
                    }
                }
                for (int y=1-radius;y<radius;++y) {
                    Cell scan=center+Cell(-radius,y);
                    if (Map.Unknown_0054AAB0(scan)) {
                        if (unknown_6c6130(method,mask,&scan,range,&object,&value,zone) && object && (!only_enemy || static_cast<TechnoClass *>(object)->House->ArrayIndex==House->unknown_54f0) && (!(method&0x4000) || House->Is_Ally(static_cast<TechnoClass *>(object)->House))) {
                            if (unknown_slot32()->DistributedFire) { unknown_3a8.Add(object);unknown_390.Add(value); }
                            if (best_value<value) { best_object=object;best_value=value; }
                        }
                        if (!best_object) {
                            value=unknown_6c6350(&scan);
                            if (best_cell_value<value) {best_cell_value=value;best_cell=scan;}
                        }
                    }
                    scan=center+Cell(radius,y);
                    if (Map.Unknown_0054AAB0(scan)) {
                        if (unknown_6c6130(method,mask,&scan,range,&object,&value,zone) && object && (!only_enemy || static_cast<TechnoClass *>(object)->House->ArrayIndex==House->unknown_54f0) && (!(method&0x4000) || House->Is_Ally(static_cast<TechnoClass *>(object)->House))) {
                            if (unknown_slot32()->DistributedFire) { unknown_3a8.Add(object);unknown_390.Add(value); }
                            if (best_value<value) { best_object=object;best_value=value; }
                        }
                        if (!best_object) {
                            value=unknown_6c6350(&scan);
                            if (best_cell_value<value) {best_cell_value=value;best_cell=scan;}
                        }
                    }
                }
                if (best_object) {
                    if (radius==cell_range/4 || radius==cell_range/2) return best_object;
                }
                if (best_cell!=unknown_cell_ac0148) return &Map[best_cell];
            }
        }
    } else {
        int index;
        if (mask&4) {
            for (index=0;index<Aircraft.Count();++index) {
                TechnoClass *object=Aircraft[index];
                int value=0;
                if (!House->Is_Ally(object) && (!only_enemy || object->House->ArrayIndex==House->unknown_54f0) && (!(method&0x4000) || House->Is_Ally(object->House)) && unknown_6c5570(method,mask,-1,object,&value,-1,&unknown_coord_ac0188) && value>best_value) { best_object=object;best_value=value; }
            }
        }
        if (method&0x10) mask|=4;
        for (index=0;index<Technos.Count();++index) {
            TechnoClass *object=Technos[index];
            int value=0;
            if ((!House->Is_Ally(object) || unknown_6c16f0(-1)<0 || (!House->unknown_func_4f52f0() && this && Kind_Of()==15 && (this && Kind_Of()==15 ? static_cast<InfantryClass *>(this):0)->Type->Engineer)) && object->unknown_80==2 && (!only_enemy || object->House->ArrayIndex==House->unknown_54f0) && (!(method&0x4000) || House->Is_Ally(object->House)) && unknown_6c5570(method,mask,-1,object,&value,zone,coord) && value>best_value) {best_object=object;best_value=value;}
        }
    }
    return best_object;
}