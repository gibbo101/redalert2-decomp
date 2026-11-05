// Releases the attached unit onto an available cell; original00607440.
#include "shared/foot.hpp"
#include "shared/cell.hpp"
#include "shared/techno_type.hpp"
#include "shared/weapon_type.hpp"
#include "shared/house.hpp"
#include "shared/team.hpp"
#include "shared/map_view.hpp"
#include "shared/parasite.hpp"
#include "shared/house_adjacent.hpp"
#include "shared/unknown_geometry.hpp"
// @ref _unknown_geometry_l=00a76468
// @ref _unknown_geometry_k=00a76448
// @ref ?AdjacentCell@@3QBUCell@@B=00851a70
void ParasiteClass::Unknown_00607440()
{
    bool naval = Owner->unknown_slot32()->Naval;
    int facing = Dir_To_8(unknown_28->unknown_2e0.Current());
    UnknownFacingDir exit_dir;
    if (facing >= 0 && facing <= 2) {
        exit_dir = UnknownFacingDir((unsigned short)(unknown_28->unknown_2e0.Current().Raw + 0x3fff));
    } else {
        exit_dir = UnknownFacingDir((unsigned short)(unknown_28->unknown_2e0.Current().Raw - 0x3fff));
    }
    Cell cell;
    if (naval) {
        cell = Adjacent_Cell(unknown_28->unknown_slot104(), (FacingType)Dir_To_8(exit_dir));
    } else if (unknown_2c.Value() == 0) {
        cell = unknown_28->unknown_slot104();
    } else {
        Owner->Strength = 0;
        unknown_28->unknown_58c = CDTimerClass<FrameTimerClass>(0);
        unknown_28->unknown_580 = 0;
        Owner->unknown_slot60();
        unknown_28 = 0;
        return;
    }
    CellClass &target_cell = Map[cell];
    if (!target_cell.unknown_478760(Owner->unknown_slot32()->SpeedType, false, false,
        Map.Zone(cell, Owner->unknown_slot32()->MovementZone, false),
        Owner->unknown_slot32()->MovementZone, -1, true)) {
        cell = unknown_28->unknown_6cf130(0);
    }
    CoordStruct coord = unknown_geometry_l;
    if (cell != unknown_geometry_k) {
        coord = Map[cell].Center_Coord();
    }
    bool can_exit = false;
    if (cell != unknown_geometry_k && coord != unknown_geometry_l && unknown_28 != 0 && !unknown_28->unknown_slot21()) {
        if (Owner->unknown_slot32()->Naval) {
            can_exit = true;
        } else if (!(Owner != 0 && Owner->Kind_Of() == 1 && ((CellClass *)unknown_28->unknown_slot105())->Cell_Terrain() != 0)) {
            int land = ((CellClass *)unknown_28->unknown_slot105())->unknown_ec;
            if (land != 2 && land != 6 && land != 3) can_exit = true;
        }
    }
    if (can_exit && Owner->unknown_slot53(&coord, Dir_To_256(exit_dir))) {
        if (Owner->unknown_381 && Owner->House->Unknown_004F52B0()) {
            Owner->unknown_381 = false;
            Owner->unknown_slot80();
        }
        if (Owner->unknown_384 != 0) {
            ((TeamClass *)Owner->unknown_384)->unknown_func_6b8cc0(Owner);
        }
        if (!Owner->unknown_slot270()) {
            Owner->unknown_6d6e50(0);
            Owner->unknown_slot220(0);
            Owner->unknown_slot260(0, 1);
        }
        Owner->unknown_slot261(false, true);
        Owner->unknown_slot262(false, false, false, 0);
        Owner->unknown_58c = CDTimerClass<FrameTimerClass>(Owner->unknown_slot231(0)->WeaponType->unknown_b0 * 3);
        Unknown_006064C0();
    } else {
        Owner->Strength = 0;
        Owner->unknown_slot60();
    }
    unknown_28->unknown_280 = 0.0f;
    unknown_28->unknown_58c = CDTimerClass<FrameTimerClass>(0);
    unknown_28->unknown_580 = 0;
    unknown_28 = 0;
}
