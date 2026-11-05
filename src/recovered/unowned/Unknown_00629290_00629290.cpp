// void __fastcall Unknown_00629290(int start, int count) (0x00629290; RA2 only, no TibSun twin)
// Spreads a run of identical megamissions aimed at one cell: the foot units of events start..start+count are ordered
// by distance from the unit nearest their centre; the first keeps the cell, every later one walks from it along its
// offset from that unit for up to six cells, and its event gets the first free, level-compatible cell of the same
// movement zone. Units sharing a cell get the same destination. Purpose and names are hypotheses.
#include "shared/queue.hpp"
#include "shared/building_class.hpp"
#include "shared/unit.hpp"
#include "shared/map_view.hpp"
#include "shared/cell_class.hpp"
#include "shared/path_estimator.hpp"
#include "shared/techno_type.hpp"
#include "shared/ini_class.hpp"
#include "shared/unknown_vector3.hpp"
#include "shared/vector3.hpp"
#include "shared/fast_math.hpp"
// @ref ??8?$VectorClass@PAVObjectClass@@@@UBE_NABV0@@Z=0040cbc0
// @ref ??_G?$VectorClass@PAVObjectClass@@@@UAEPAXI@Z=0040ce20
// @ref ?Clear@?$DynamicVectorClass@PAVObjectClass@@@@UAEXXZ=0040cb60
// @ref ?Clear@?$VectorClass@PAVObjectClass@@@@UAEXXZ=0040ccb0
// @ref ?Fetch@?$VectorClass@PAVObjectClass@@@@UBEPAVObjectClass@@H@Z=0040cbb0
// @ref ?ID@?$DynamicVectorClass@PAVObjectClass@@@@UAEHABQAVObjectClass@@@Z=0040cdf0
// @ref ?ID@?$DynamicVectorClass@PAVObjectClass@@@@UAEHPBQAVObjectClass@@@Z=0040cb90
// @ref ?ID@?$VectorClass@PAVObjectClass@@@@UAEHABQAVObjectClass@@@Z=0040cce0
// @ref ?ID@?$VectorClass@PAVObjectClass@@@@UAEHPBQAVObjectClass@@@Z=0040cd20
// @ref ?Resize@?$DynamicVectorClass@PAVObjectClass@@@@UAE_NHPBQAVObjectClass@@@Z=0040cd40
// @ref ?Resize@?$VectorClass@PAVObjectClass@@@@UAE_NHPBQAVObjectClass@@@Z=0040cc00
// @ref ??8?$VectorClass@VCell@@@@UBE_NABV0@@Z=0042ce10
// @ref ??_E?$DynamicVectorClass@VCell@@@@UAEPAXI@Z=0042d3e0
// @ref ??_E?$VectorClass@VCell@@@@UAEPAXI@Z=0042d390
// @ref ?Clear@?$DynamicVectorClass@VCell@@@@UAEXXZ=0042cc10
// @ref ?Clear@?$VectorClass@VCell@@@@UAEXXZ=0042cfb0
// @ref ?Fetch@?$VectorClass@VCell@@@@UBE?AVCell@@H@Z=0042cc60
// @ref ?ID@?$DynamicVectorClass@VCell@@@@UAEHABVCell@@@Z=0042d120
// @ref ?ID@?$DynamicVectorClass@VCell@@@@UAEHPBVCell@@@Z=0042cc40
// @ref ?ID@?$VectorClass@VCell@@@@UAEHABVCell@@@Z=0042cfe0
// @ref ?ID@?$VectorClass@VCell@@@@UAEHPBVCell@@@Z=0042d030
// @ref ?Resize@?$DynamicVectorClass@VCell@@@@UAE_NHPBVCell@@@Z=0042d050
// @ref ?Resize@?$VectorClass@VCell@@@@UAE_NHPBVCell@@@Z=0042cee0
// @ref ??8?$VectorClass@_N@@UBE_NABV0@@Z=004f7e40
// @ref ??_E?$DynamicVectorClass@_N@@UAEPAXI@Z=004f87b0
// @ref ??_E?$VectorClass@_N@@UAEPAXI@Z=004f8760
// @ref ??_G?$DynamicVectorClass@_N@@UAEPAXI@Z=004f87b0
// @ref ??_G?$VectorClass@_N@@UAEPAXI@Z=004f8760
// @ref ?Clear@?$DynamicVectorClass@_N@@UAEXXZ=004f6e00
// @ref ?Clear@?$VectorClass@_N@@UAEXXZ=004f7f30
// @ref ?Fetch@?$VectorClass@_N@@UBE_NH@Z=004f6e50
// @ref ?ID@?$DynamicVectorClass@_N@@UAEHAB_N@Z=004f8070
// @ref ?ID@?$DynamicVectorClass@_N@@UAEHPB_N@Z=004f6e30
// @ref ?ID@?$VectorClass@_N@@UAEHAB_N@Z=004f7f60
// @ref ?ID@?$VectorClass@_N@@UAEHPB_N@Z=004f7fa0
// @ref ?Resize@?$DynamicVectorClass@_N@@UAE_NHPB_N@Z=004f7fc0
// @ref ?Resize@?$VectorClass@_N@@UAE_NHPB_N@Z=004f7e80
// @ref ??0?$VectorClass@PAVObjectClass@@@@QAE@IPBQAVObjectClass@@@Z=004bfbd0
// @ref ??_7?$DynamicVectorClass@PAVObjectClass@@@@6B@=0079db7c
// @ref ??_7?$VectorClass@PAVObjectClass@@@@6B@=0079a91c
// @ref ??0?$VectorClass@VCell@@@@QAE@IPBVCell@@@Z=0042d4a0
// @ref ??_7?$DynamicVectorClass@VCell@@@@6B@=0079c5a0
// @ref ??_7?$VectorClass@VCell@@@@6B@=0079c5e0
// @ref ??0?$VectorClass@_N@@QAE@IPB_N@Z=004f8d20
// @ref ??_7?$DynamicVectorClass@_N@@6B@=007a2f84
// @ref ??_7?$VectorClass@_N@@6B@=007a2f64
// @ref ?Unknown_005D5010@@YI?AUCoordStruct@@ABV?$DynamicVectorClass@PAVObjectClass@@@@@Z=005d5010
// @ref ?search_compfunc@?$IndexClass@HPAVObjectClass@@@@CAHPBX0@Z=0062ead0

template <class T>
DynamicVectorClass<T>::DynamicVectorClass(unsigned size, T const *array)
    : VectorClass<T>(size, array)
{
    GrowthStep = 10;
    ActiveCount = 0;
}
template <class T>
void VectorClass<T>::Clear()
{
    if (Vector && IsAllocated) {
        delete[] Vector;
        Vector = 0;
    }
    IsAllocated = false;
    VectorMax = 0;
}
template <class T>
void DynamicVectorClass<T>::Clear()
{
    ActiveCount = 0;
    VectorClass<T>::Clear();
}
template <class T>
VectorClass<T>::~VectorClass()
{
    VectorClass<T>::Clear();
}

CoordStruct __fastcall Unknown_005D5010(DynamicVectorClass<ObjectClass *> const &objects);
ObjectClass *__fastcall Closest_Object_005d5090(DynamicVectorClass<ObjectClass *> const &objects, CoordStruct const &coord);
void __fastcall Unknown_00629220(int start, int count, TargetClass whom, TargetClass const &target);

inline int Spread_Distance(CoordStruct const &a, CoordStruct b)
{
    UnknownVector3 delta = UnknownVector3(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
    return delta.Length();
}

inline Vector3 Divide(Vector3 const &vector, double divisor)
{
    return Vector3(vector.X / divisor, vector.Y / divisor, vector.Z / divisor);
}

inline Vector3 Normalized(Vector3 const &v)
{
    double length = Fast_Sqrt(v.X * v.X + v.Y * v.Y + v.Z * v.Z);
    if (length != 0.0) {
        return Vector3(v.X / length, v.Y / length, v.Z / length);
    }
    return v;
}

inline Cell Vector_Cell(Vector3 const &v)
{
    return Cell((short)v.X, (short)v.Y);
}

// Readable names for this row's constants.
enum {
    KIND_CELL = 0x0B,
    CELL_FLAG_TAKEN = 0x8000,
    CELL_FLAG_UNDER_BRIDGE = 0x100,
    SPREAD_TRIES = 6,
    SPREAD_KEY_SCALE = 1000,
    SPREAD_LEVEL_SLACK = 2,
};

void __fastcall Unknown_00629290(int start, int count)
{
    if (unknown_event_queue_a35f30[start].TargetAt(0x13).Kind == 0 || unknown_event_queue_a35f30[start].TargetAt(0x13).Kind != KIND_CELL) {
        return;
    }
    CellClass *cptr = unknown_event_queue_a35f30[start].TargetAt(0x13).As_Cell();
    if (cptr == 0 || cptr == &unknown_dummy_cell_a6f9f8) {
        return;
    }
    Cell dest = cptr->MapCoords;
    if (dest == unknown_geometry_k) {
        return;
    }
    DynamicVectorClass<ObjectClass *> list;
    int i;
    for (i = start; i < start + count; i++) {
        TechnoClass *techno = unknown_event_queue_a35f30[i].TargetAt(0x07).As_Techno();
        bool foot = false;
        if (techno != 0) {
            foot = techno->AbstractFlags.IsFoot;
        }
        if (foot && ((FootClass *)techno)->unknown_574 < 0) {
            list.Add(techno);
        }
    }
    if (list.Count() > 0) {
        CoordStruct center = Unknown_005D5010(list);
        ObjectClass *closest = Closest_Object_005d5090(list, center);
        IndexClass<int, ObjectClass *> index;
        for (i = 0; i < list.Count(); i++) {
            int key = Spread_Distance(list[i]->Center_Coord(), closest->Coord) * SPREAD_KEY_SCALE + i;
            index.Add_Index(key, list[i]);
        }
        list.Clear();
        DynamicVectorClass<Cell> cells;
        DynamicVectorClass<bool> done;
        for (i = 0; i < index.Count(); i++) {
            list.Add(index.Fetch_By_Position(i));
            cells.Add(dest);
            done.Add(false);
        }
        Cell origin = closest->unknown_slot104();
        for (i = 0; i < list.Count();) {
            ObjectClass *object = list[i];
            Cell best = dest;
            if (i == 0) {
                Map[dest].unknown_140 |= CELL_FLAG_TAKEN;
                done[0] = true;
            } else if (!done[i]) {
                Cell fallback = dest;
                Cell cell(object->unknown_slot19(0));
                int level = Map[dest].IsUnderBridge * 4 + Map[dest].unknown_11b;
                Vector3 position(dest.X + 0.5, dest.Y + 0.5, 0);
                int offset_x = cell.X - origin.X;
                int offset_y = cell.Y - origin.Y;
                Vector3 step(offset_x, offset_y, 0);
                step = Normalized(step);
                int tries = 0;
                bool detour = false;
                TechnoTypeClass *type = object->unknown_slot32();
                int zone = Map.Zone(dest, type->MovementZone, true);
                bool found = false;
                Cell spot;
                for (; tries < SPREAD_TRIES; tries++) {
                    position = step + position;
                    spot = Cell((short)position.X, (short)position.Y);
                    CellClass *spot_ptr = &Map[spot];
                    if (!Map.Unknown_0055A660(spot, true)) {
                        break;
                    }
                    int spot_zone = Map.Zone(spot, type->MovementZone, spot_ptr->IsUnderBridge);
                    int enter = object->unknown_slot101(spot_ptr, -1, level, 0, 1);
                    if (spot_zone == zone) {
                        int flags = spot_ptr->unknown_140;
                        if (flags & CELL_FLAG_TAKEN) {
                            fallback = spot;
                        } else {
                            if ((flags & CELL_FLAG_UNDER_BRIDGE) && abs(level - spot_ptr->unknown_11b - 4) > SPREAD_LEVEL_SLACK) {
                                break;
                            }
                            if (!(flags & CELL_FLAG_UNDER_BRIDGE) && abs(level - spot_ptr->unknown_11b) > SPREAD_LEVEL_SLACK) {
                                break;
                            }
                            if (enter < 4 || enter == 6) {
                                if (detour) {
                                    int dx = abs(spot.X - dest.X);
                                    int dy = abs(spot.Y - dest.Y);
                                    int range = (dx > dy ? dx : dy) + 3;
                                    // The original stores range, then keeps the fallback either way: VC6 only
                                    // removes this test after the store has survived dead-store removal.
                                    if (unknown_path_estimator_8315c8.Unknown_0042AA30(spot, dest, (FootClass *)object,
                                            Map[spot].IsUnderBridge, Map[dest].IsUnderBridge, -1) > range && range > 0) {
                                        found = false;
                                    }
                                    break;
                                }
                                found = true;
                                break;
                            }
                            detour = true;
                        }
                    } else {
                        detour = true;
                    }
                }
                best = !found ? fallback : Cell((short)position.X, (short)position.Y);
                cells[i] = best;
                TargetClass target(&Map[best]);
                Unknown_00629220(start, count, TargetClass((AbstractClass *)object), target);
                Map[best].unknown_140 |= CELL_FLAG_TAKEN;
                done[i] = true;
            }
            for (int j = i + 1; j < list.Count(); j++) {
                if (!done[j] && object->unknown_slot104() == list[j]->unknown_slot104()) {
                    TargetClass target(&Map[best]);
                    Unknown_00629220(start, count, TargetClass((AbstractClass *)list[j]), target);
                    done[j] = true;
                }
            }
            i++;
        }
        for (i = 0; i < cells.Count(); i++) {
            Map[cells[i]].unknown_140 &= ~CELL_FLAG_TAKEN;
        }
    }
}
