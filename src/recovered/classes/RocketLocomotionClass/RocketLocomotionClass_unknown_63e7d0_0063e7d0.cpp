// void RocketLocomotionClass::unknown_63e7d0() (0x0063E7D0)
// Detonates the rocket at its nose: leaves the tracker, picks the warhead
// and damage of its kind (V3Rocket for its type, else DMisl; the elite ones
// when the launcher +0x23C is elite), plays the damage animation, the
// explosion effects and the area damage there, then removes the rocket
// (slot 60).
#include "shared/rocket_locomotion.hpp"
#include "shared/rules.hpp"
#include "shared/cell_class.hpp"
#include "shared/anim.hpp"
#include "shared/aircraft.hpp"
#include "shared/infantry.hpp"
#include "shared/techno.hpp"

// The land type of a cell (local helper).
static inline int Land_Type_At(Cell const &cell)
{
    return Map[cell].unknown_ec;
}

void RocketLocomotionClass::unknown_63e7d0()
{
    unknown_tracker_839ea0.Unknown_00413310(LinkedTo);
    TechnoClass *spawner = static_cast<TechnoClass *>(LinkedTo->unknown_23c);
    bool elite = spawner != 0 && spawner->unknown_118.unknown_713420();
    RocketStruct const *rocket;
    WarheadTypeClass *warhead;
    if (((AircraftClass *)LinkedTo)->Type == Rules->V3Rocket.Type) {
        rocket = &Rules->V3Rocket;
        warhead = elite ? Rules->V3EliteWarhead : Rules->V3Warhead;
    } else {
        rocket = &Rules->DMisl;
        warhead = elite ? Rules->DMislEliteWarhead : Rules->DMislWarhead;
    }
    CoordStruct coord = unknown_63dbe0(rocket->BodyLength);
    Cell cell = Coord_Cell(coord);
    int damage = elite ? rocket->EliteDamage : rocket->Damage;
    new AnimClass(Select_Damage_Anim(damage, warhead, Land_Type_At(cell), &coord), coord, 0, 1, 0x2600, Unknown_0047FCC0(coord));
    Unknown_0047F600(coord, damage, warhead, 0, 0);
    Unknown_0047E2C0(coord, damage, LinkedTo, warhead, true);
    LinkedTo->unknown_slot60();
}
