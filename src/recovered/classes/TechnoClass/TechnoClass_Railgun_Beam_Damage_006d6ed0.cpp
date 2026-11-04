// CoordStruct TechnoClass::Railgun_Beam_Damage(CoordStruct const &coord, AbstractClass *abstract, WeaponTypeClass *weapon) (0x006D6ED0)
// Damages what stands near the beam from coord to the center of abstract (Rules radius, abstract always) and
// returns where the beam stopped: blocking ground, which may collapse a cliff, else the center (TibSun
// Railgun_Beam_Damage). `techno` is left unset on a null object, the shared form of this flag test (0x00471660).
#include "shared/techno.hpp"
#include "shared/techno_map.hpp"
#include "shared/gscreen.hpp"
#include "shared/rules.hpp"
#include "shared/weapon_type.hpp"
#include "shared/vector3.hpp"
#include "shared/vector_class.hpp"
#include "shared/id_source.hpp"
#include "shared/cell_class.hpp"
#include "shared/crt_math.hpp"
#include "shared/fast_math.hpp"
// @ref ??0?$VectorClass@PAVObjectClass@@@@QAE@IPBQAVObjectClass@@@Z=004bfbd0
// @ref ??_7?$DynamicVectorClass@PAVObjectClass@@@@6B@=0079db7c
// @ref ??_7?$VectorClass@PAVObjectClass@@@@6B@=0079a91c
// @ref ?Collapse_Cliff@MapClass@@QAEXPAVCellClass@@@Z=00562f50
// @ref __real@4@3ff9a72f050000000000=007ad030
// @ref ?Lerp@@YI?AUCoordStruct@@ABU1@0M@Z=007220c0

CoordStruct __fastcall Lerp(CoordStruct const &from, CoordStruct const &to, float t);   // 0x007220C0

inline float Vector_Length(Vector3 const &v)
{
    double y = v.Y;
    double z = v.Z;
    double x = v.X;
    return (float)Fast_Sqrt(x * x + y * y + z * z);
}

inline bool Percent_Chance(int percent)
{
    return Random_Pick(0, 99) < percent;
}

inline Vector3 operator-(Vector3 const &a, Vector3 const &b)
{
    return Vector3(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
}

inline float operator*(Vector3 const &a, Vector3 const &b)
{
    return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
}

CoordStruct TechnoClass::Railgun_Beam_Damage(CoordStruct const &coord, AbstractClass *abstract, WeaponTypeClass *weapon)
{
    CoordStruct center = abstract->Center_Coord();
    bool target_found = false;
    Cell final_cell = Cell(coord);
    Vector3 start(coord.X, coord.Y, coord.Z);
    Vector3 end(center.X, center.Y, center.Z);
    CoordStruct final_impact = coord;
    Vector3 delta = end - start;
    DynamicVectorClass<ObjectClass *> targets;

    for (int i = 0; i < 50; i++) {
        final_impact = Lerp(coord, center, i * (1.0f / 49));
        if (Cell(final_impact) != final_cell) {
            final_cell = Cell(final_impact);
            CellClass *cptr = &Map[final_cell];
            ObjectClass *optr;
            if (cptr->unknown_140 & 0x100 && final_impact.Z >= (cptr->unknown_11b + 4) * unknown_geometry_g) {
                optr = cptr->AltOccupierPtr;
            } else {
                optr = cptr->OccupierPtr;
            }
            while (optr != 0) {
                if (optr != this) {
                    if (optr == abstract) {
                        target_found = true;
                    }
                    bool techno;
                    if (optr != 0) {
                        techno = optr->AbstractFlags.IsTechno;
                    }
                    if (optr != 0 && techno) {
                        float distance = 0.0f;
                        if (optr->Kind_Of() != 6) {
                            CoordStruct obj_coord = optr->Coord;
                            Vector3 obj(obj_coord.X, obj_coord.Y, obj_coord.Z);
                            Vector3 off = obj - start;
                            Vector3 cross = Vector3::Cross_Product(off, delta);
                            Vector3 perp = Vector3::Cross_Product(cross, delta);
                            distance = (float)fabs((perp * off) / Vector_Length(perp));
                        }
                        if (distance < Rules->RailgunDamageRadius || optr == abstract) {
                            if (targets.Count() == 0 || targets.ID(optr) == -1) {
                                targets.Add(optr);
                            }
                        }
                    }
                }
                optr = optr->unknown_30;
            }
            if (Map.Unknown_0055A280(final_impact) > final_impact.Z) {
                if (Map[final_impact].unknown_47bb10()) {
                    if (Percent_Chance(Rules->unknown_140c)) {
                        Map.Collapse_Cliff(&Map[final_impact]);
                    }
                }
                return final_impact;
            }
        }
    }
    if (!target_found && abstract != 0 && abstract->AbstractFlags.IsObject) {
        ObjectClass *obj = (ObjectClass *)abstract;
        if (targets.Count() == 0 || targets.ID(obj) == -1) {
            targets.Add(obj);
        }
    }
    for (int j = 0; j < targets.Count(); j++) {
        int damage = weapon->unknown_98;
        targets[j]->unknown_slot86(&damage, 0, weapon->Warhead, this, false, 0);
    }
    if (abstract->Kind_Of() == 11 && ((CellClass *)abstract)->unknown_47bb10()) {
        if (Percent_Chance(Rules->unknown_140c)) {
            Map.Collapse_Cliff((CellClass *)abstract);
        }
    }
    return center;
}
