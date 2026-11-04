// bool HouseClass::AI_Build_Defense(int node, DynamicVectorClass<Cell> *cells) (0x004F1190, 3,264 B, no padding)
// TibSun AI_Build_Defense: sums the defenses of the base by quadrant, picks the weakest quadrant
// (one holding threat cells when a list is given), then the category the defenses lack most, and
// puts a defense of that category on the node, or queues it on the next node when the node
// already has a type. `lowest` is not in TibSun: an alias that names best_value before best in
// the IL, which sets the reload order ahead of the quadrant loop. Each named `dy` is needed in
// both loops for the add order in the first inlined Add.
// @ref ??0?$DynamicVectorClass@VCell@@@@QAE@IPBV1@@Z=0042ce60
// @ref ??0?$VectorClass@VCell@@@@QAE@IPBV1@@Z=0042d4a0
// @ref ?Increase_Table_Size@?$IndexClass@HVCell@@@@QAE_NH@Z=004f8c60
// @ref ?search_compfunc@?$IndexClass@HVCell@@@@CAHPBX0@Z=004f8cf0
// @ref ?unknown_451710@BuildingClass@@QAEHXZ=00451710
// The local distribution's vector instantiation (COMDAT copies of the accepted members and vtables):
// @ref ?Fetch@?$VectorClass@V?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@@@UBE?AV?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@H@Z=004f6ec0
// @ref ??8?$VectorClass@V?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@@@UBE_NABV0@@Z=004f80a0
// @ref ?Resize@?$VectorClass@V?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@@@UAE_NHPBV?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@@Z=004f8100
// @ref ?Clear@?$VectorClass@V?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@@@UAEXXZ=004f8210
// @ref ?ID@?$VectorClass@V?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@@@UAEHABV?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@@Z=004f8250
// @ref ?ID@?$VectorClass@V?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@@@UAEHPBV?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@@Z=004f82a0
// @ref ?Clear@?$DynamicVectorClass@V?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@@@UAEXXZ=004f6e60
// @ref ?ID@?$DynamicVectorClass@V?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@@@UAEHPBV?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@@Z=004f6ea0
// @ref ?Resize@?$DynamicVectorClass@V?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@@@UAE_NHPBV?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@@Z=004f82c0
// @ref ??1?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@QAE@XZ=004f83e0
// @ref ?Add@?$DynamicVectorClass@V?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@@@QAE_NABV?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@@Z=004f83f0
// @ref ?ID@?$DynamicVectorClass@V?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@@@UAEHABV?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@@Z=004f8450
// @ref ??_G?$VectorClass@V?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@@@UAEPAXI@Z=004f8800
// @ref ??_E?$VectorClass@V?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@@@UAEPAXI@Z=004f8800
// @ref ??_E?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@QAEPAXI@Z=004f8860
// @ref ??_G?$DynamicVectorClass@V?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@@@UAEPAXI@Z=004f88a0
// @ref ??_E?$DynamicVectorClass@V?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@@@UAEPAXI@Z=004f88a0
// @ref ??_7?$VectorClass@V?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@@@6B@=007a2fac
// @ref ??_7?$DynamicVectorClass@V?$DistributionObject@PAVBuildingTypeClass@@@?$DiscreteDistributionClass@VBuildingTypeClass@@@@@@6B@=007a2fcc
#include "shared/building_class.hpp"
#include "shared/building_type_class.hpp"
#include "shared/building_type_list.hpp"
#include "shared/rules.hpp"
#include "shared/base.hpp"
#include "shared/rect.hpp"
#include "shared/facing.hpp"
#include "shared/fast_math.hpp"
#include "shared/crt_memory.hpp"
#include "shared/discrete_distribution.hpp"
#include "shared/id_source.hpp"
#include "shared/ini_class.hpp"

extern double const unknown_facing_scale_79b628;
extern double const unknown_facing_origin_79b630;

inline int Dir_To_4(UnknownFacingDir const &dir)
{
    return (((*(unsigned const *)&dir >> 13) + 1) >> 1) & 3;
}

bool HouseClass::AI_Build_Defense(int node, DynamicVectorClass<Cell> *cells)
{
    int i;
    int best_value;
    int const &lowest = best_value;
    int best = -1;
    best_value = 999999;
    int air_values[4];
    air_values[0] = 0;
    air_values[1] = 0;
    air_values[2] = 0;
    air_values[3] = 0;
    int armor_values[4];
    armor_values[0] = 0;
    armor_values[1] = 0;
    armor_values[2] = 0;
    armor_values[3] = 0;
    int ground_values[4];
    ground_values[0] = 0;
    ground_values[1] = 0;
    ground_values[2] = 0;
    ground_values[3] = 0;
    int totals[4];
    DynamicVectorClass<Cell> quadrants[4];

    int size = unknown_55f0.unknown_54.Width * unknown_55f0.unknown_54.Height;
    int *air_map = new int[size];
    int *armor_map = new int[size];
    int *ground_map = new int[size];
    memset(air_map, 0, size * sizeof(int));
    memset(armor_map, 0, size * sizeof(int));
    memset(ground_map, 0, size * sizeof(int));

    if (cells != 0) {
        for (i = 0; i < cells->Count(); i++) {
            Cell offset = (*cells)[i] - unknown_55f0.unknown_50;
            Point2D delta;
            delta.X = offset.X;
            delta.Y = offset.Y;
            int dy = -delta.Y;
            UnknownFacingDir dir = Offset_Direction(delta.X, dy);
            quadrants[Dir_To_4(dir)].Add((*cells)[i]);
        }
    }

    int count = Buildings.Count();
    for (i = 0; i < count; i++) {
        BuildingClass *building = Buildings[i];
        Cell offset = building->unknown_slot104() - unknown_55f0.unknown_50;
        if (offset.X != 0 || offset.Y != 0) {
            Point2D delta;
            delta.X = offset.X;
            delta.Y = offset.Y;
            int dy = -delta.Y;
            UnknownFacingDir dir = Offset_Direction(delta.X, dy);
            int quadrant = Dir_To_4(dir);
            int air = building->unknown_451710();
            int armor = building->unknown_451760();
            int infantry = building->unknown_4517b0();
            if (air + armor + infantry > 0) {
                air_values[quadrant] += air;
                armor_values[quadrant] += armor;
                ground_values[quadrant] += infantry;
                unknown_func_4f0ff0(building, air, air_map, unknown_55f0.unknown_54);
                unknown_func_4f0ff0(building, armor, armor_map, unknown_55f0.unknown_54);
                unknown_func_4f0ff0(building, infantry, ground_map, unknown_55f0.unknown_54);
            }
        }
    }

    for (i = 0; i < 4; i++) {
        totals[i] = air_values[i] + armor_values[i] + ground_values[i];
        if (totals[i] < best_value && (cells == 0 || quadrants[i].Count() > 0)) {
            best_value = totals[i];
            best = i;
        }
    }

    int air_value = air_values[best];
    int armor_value = armor_values[best];
    int ground_value = ground_values[best];

    Calculate_Enemy_Predictions();

    DynamicVectorClass<BuildingTypeClass const *> owned;
    count = Buildings.Count();
    for (i = 0; i < count; i++) {
        BuildingClass *building = Buildings[i];
        BuildingTypeClass *type = building->Type;
        if (!type->IsBaseDefense && type != Rules->unknown_78c) {
            owned.Add(building->Type);
        }
    }

    int type_id = unknown_55f0.Nodes[node].Type;
    BuildingTypeClass *pending = 0;

    float air_ratio = lowest != 0 ? air_value / (float)best_value : 0.0f;
    float armor_ratio = lowest != 0 ? armor_value / (float)best_value : 0.0f;
    float ground_ratio = lowest != 0 ? ground_value / (float)best_value : 0.0f;
    float air_deficit = unknown_15f80 - air_ratio;
    float armor_deficit = unknown_15f7c - armor_ratio;
    float ground_deficit = unknown_15f84 - ground_ratio;

    DynamicVectorClass<BuildingTypeClass *> air_defenses = Get_Anti_Air_Defense_Buildings_004f1e50(owned);
    DynamicVectorClass<BuildingTypeClass *> armor_defenses = Get_Anti_Armor_Defense_Buildings_004f1ff0(owned);
    DynamicVectorClass<BuildingTypeClass *> ground_defenses = Get_Anti_Ground_Defense_Buildings_004f2190(owned);

    DynamicVectorClass<BuildingTypeClass *> *defenses;
    int category;
    if (air_deficit <= armor_deficit || air_deficit <= ground_deficit) {
        if (armor_deficit > ground_deficit) {
            defenses = &armor_defenses;
            unknown_15f44 = armor_map;
            category = 1;
        } else {
            defenses = &ground_defenses;
            unknown_15f44 = ground_map;
            category = 2;
        }
    } else {
        defenses = &air_defenses;
        unknown_15f44 = air_map;
        category = 0;
    }

    bool success = true;
    if (defenses->Count() == 0) {
        if (armor_defenses.Count() > 0) {
            defenses = &armor_defenses;
            category = 1;
            unknown_15f44 = armor_map;
        } else if (ground_defenses.Count() > 0) {
            defenses = &ground_defenses;
            category = 2;
            unknown_15f44 = ground_map;
        } else if (air_defenses.Count() > 0) {
            defenses = &air_defenses;
            category = 0;
            unknown_15f44 = air_map;
        } else {
            success = false;
        }
    }

    if (success) {
        BuildingTypeClass *choice;
        if (defenses->Count() == 1) {
            choice = (*defenses)[0];
        } else {
            DiscreteDistributionClass<BuildingTypeClass> distribution;
            for (i = 0; i < defenses->Count(); i++) {
                BuildingTypeClass *type = (*defenses)[i];
                int weight = 10000 / type->unknown_slot33((int)this);
                if (category == 2) {
                    weight += type->unknown_11e0;
                } else if (category == 1) {
                    weight += type->unknown_11dc;
                } else {
                    weight += type->unknown_11d8;
                }
                distribution.Add(type, weight);
            }
            choice = distribution.Sample();
        }

        BuildingTypeClass *build_type;
        if (type_id >= 0) {
            build_type = BuildingTypes[type_id];
            pending = choice;
        } else {
            build_type = choice;
        }

        Cell cell(0, 0);
        if (cells != 0) {
            IndexClass<int, Cell> ranking;
            DynamicVectorClass<Cell> sorted;
            sorted.Clear();
            for (i = 0; i < quadrants[best].Count(); i++) {
                Cell threat = quadrants[best][i];
                ranking.Add_Index(House_Facing_Score(this, threat, i, -1), threat);
            }
            for (i = 0; i < ranking.Count(); i++) {
                sorted.Add(ranking.Fetch_By_Position(i));
            }
            cell = sorted[0];
            cells->Delete(cells->ID(cell));
        } else {
            cell = Where_To_Place_Building(build_type, House_Facing_Score, 2 * best);
        }

        if (cell == Cell(0, 0)) {
            success = false;
        } else if (pending != 0) {
            unknown_55f0.Nodes[node].Cell = cell;
            if (unknown_55f0.Nodes[node + 1].Type == -1) {
                unknown_55f0.Nodes[node + 1].Type = pending->ArrayIndex;
                unknown_55f0.Nodes[node + 1].Cell = cell;
                if (cells != 0) {
                    BuildingTypeClass const *wall = unknown_func_4ef600(Rules->ConcreteWalls);
                    for (i = unknown_55f0.Nodes.Count() - 1; i >= 0; i--) {
                        if (unknown_55f0.Nodes[i].Cell == cell && unknown_55f0.Nodes[i].Type == wall->ArrayIndex) {
                            unknown_55f0.Nodes.Delete(i);
                            break;
                        }
                    }
                }
            }
        } else {
            unknown_55f0.Nodes[node].Type = build_type->ArrayIndex;
            unknown_55f0.Nodes[node].Cell = cell;
        }
    }

    delete[] air_map;
    delete[] armor_map;
    delete[] ground_map;
    unknown_15f44 = 0;

    return success;
}
