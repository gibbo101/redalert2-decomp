#include "shared/particle_system.hpp"
#include "shared/map_cell_view.hpp"
// @ref _unknown_geometry_g=00a76524
// @ref __real@8@00000000000000000000=0079b610
// @ref __real@8@3ff9a3d70a3d70a3d800=007a7f30
static inline ObjectClass *Fire_Content_At_Height(CellClass &cell, CoordStruct coord) { if (coord.Z >= (cell.unknown_11b + 4) * unknown_geometry_g) return cell.AltOccupierPtr; return cell.OccupierPtr; }
static inline int Particle_Distance(CoordStruct const &delta) { return (int)unknown_sqrt_4ba410((double)delta.Y * delta.Y + (double)delta.Z * delta.Z + (double)delta.X * delta.X); }
void ParticleClass::unknown_func_609970()
{
    if (Velocity > 0.0) {
    float jitter = (unknown_id_source_a3d290->Random()() % 10 - 5) * 0.02 + 1.0;
    Vector3 step(unknown_fc.X * jitter, unknown_fc.Y * jitter, unknown_fc.Z * jitter);
    int dx = (int)(step.X * Velocity);
    int dy = (int)(step.Y * Velocity);
    int dz = (int)(step.Z * Velocity);
    unknown_f0 = CoordStruct(dx, dy, dz);
    if (unknown_11e < Class->EndStateAI) {
        if ((Fetch_ID() + (Class->MaxEC - Lifetime)) % ((Fetch_ID() & 1) + unknown_11c) == 0) {
            ++unknown_11e;
            if (unknown_11e == Class->Translucent25State) unknown_11f = 25;
            if (unknown_11e == Class->Translucent50State) unknown_11f = 50;
        }
        if (unknown_11e == Class->EndStateAI && Class->DeleteOnStateLimit) {
            goto particle_done;
        }
    }
    Velocity -= Class->Deacc;
    unknown_11a--;
    if (unknown_11a == 0 && Class->Damage != 0 && unknown_11e <= Class->FinalDamageState) {
        unknown_11a = (short)Class->MaxDC;
        CellClass &cell = Map[CoordStruct(Coord)];
        ObjectClass *target;
        if (cell.unknown_140 & 0x100) target = Fire_Content_At_Height(cell, Coord);
        else target = cell.OccupierPtr;
        while (target) {
            CoordStruct delta = target->Coord;
            delta = Center_Coord() - delta;
            int distance = Particle_Distance(delta);
            int damage = Class->Damage;
            if (target->Strength > 0 && target->unknown_7d && target != System->Owner) {
                target->unknown_slot86(&damage, distance / 10, Class->Warhead, 0, false, 0);
            }
            target = target->unknown_30;
        }
    }
        return;
    }
    Velocity = 0;
particle_done:
    unknown_121 = true;
}
