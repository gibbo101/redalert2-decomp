#include "shared/fly_locomotion.hpp"
#include "shared/cell.hpp"
#include "shared/aircraft.hpp"
#include "shared/rules.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?Select_Landing_Destination_004185b0@AircraftClass@@QAEPAVAbstractClass@@PAV2@@Z=004185b0
CoordStruct Fly_Cell_Coord_004bdfb0(Cell const &cell);
void __stdcall FlyLocomotionClass::Stop_Moving()
{
    if (Is_Moving()) {
        Cell cell(Object_Coord(LinkedTo));
        if (!LinkedTo->unknown_32c && !Map.Unknown_0055A660(cell, true) && !LinkedTo->unknown_slot282()) {
            cell = Map.Unknown_005689D0(cell, 1);
        }
        FootClass *linked = LinkedTo;
        if (linked && linked->Kind_Of() == 2) {
            AircraftClass *aircraft = static_cast<AircraftClass *>(linked);
            if (cell == unknown_geometry_k) {
                LinkedTo->unknown_slot86(&LinkedTo->Strength, 0, Rules->unknown_c74, 0, true, 1);
            } else {
                AbstractClass *destination;
                if (LinkedTo->unknown_slot91() == 1) destination = aircraft->unknown_4198b0();
                else destination = aircraft->Select_Landing_Destination_004185b0(&Map[cell]);
                LinkedTo->unknown_slot260(destination, 1);
                return;
            }
        } else {
            Cell nearby = Map.Unknown_005502E0(cell, 1, -1, 9, false, Point2D(1, 1), false, false, false, true, Cell(0, 0), 0);
            if (nearby != unknown_geometry_k) {
                CoordStruct destination = Fly_Cell_Coord_004bdfb0(nearby);
                destination.Z = Map.Unknown_0055A280(destination);
                if ((reinterpret_cast<UnknownLocoCell *>(&Map[nearby])->Flags & 0x100)) destination.Z += unknown_geometry_j;
                LinkedTo->unknown_slot260(&Map[destination], 1);
                if (!unknown_51) LinkedTo->unknown_slot260(&Map[destination], 1);
                return;
            }
            if (LinkedTo->Strength <= 0) return;
            LinkedTo->unknown_slot86(&LinkedTo->Strength, 0, Rules->unknown_c74, 0, true, 1);
        }
        unknown_1c = unknown_geometry_l;
    }
}
