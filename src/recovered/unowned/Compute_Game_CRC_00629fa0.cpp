// void __fastcall Compute_Game_CRC() (0x00629FA0; Red Alert's Compute_Game_CRC).
#include "shared/queue.hpp"
#include "shared/building_class.hpp"
#include "shared/unit.hpp"
#include "shared/infantry.hpp"
#include "shared/display.hpp"
#include "shared/unknown_list_832470.hpp"
#include "shared/id_source.hpp"
#include "shared/winsock_interface.hpp"
// @ref ?GameCRC@@3KA=00a76c74
// @ref ?Frame@@3HA=00a40d2c
// @ref ?Unknown_0062CF40@@YIXH@Z=0062cf40

// A coordinate folded into one CRC word: X / 10 low, Y / 10 shifted up 16.
inline int Coord_CRC(CoordStruct coord)
{
    return coord.X / 10 + (coord.Y / 10 << 16);
}

void __fastcall Compute_Game_CRC()
{
    int i, j;
    InfantryClass *infp;
    UnitClass *unitp;
    BuildingClass *bldgp;
    ObjectClass *objp;

    GameCRC = 0;

    for (i = 0; i < Infantry.Count(); i++) {
        infp = Infantry[i];
        unsigned long val = Coord_CRC(infp->Coord) + Dir_To_256(infp->unknown_2e0.Current());
        Add_CRC(&GameCRC, val);
    }

    for (i = 0; i < Units.Count(); i++) {
        unitp = Units[i];
        unsigned long val = Coord_CRC(unitp->Coord) + Dir_To_256(unitp->unknown_2e0.Current())
            + Dir_To_256(unitp->unknown_2f8.Current());
        Add_CRC(&GameCRC, val);
    }

    for (i = 0; i < unknown_BuildingClass_list_00a40af8.Count(); i++) {
        bldgp = unknown_BuildingClass_list_00a40af8[i];
        unsigned long val = Coord_CRC(bldgp->Coord) + Dir_To_256(bldgp->unknown_2e0.Current());
        Add_CRC(&GameCRC, val);
    }

    // The map layers, then the logic list; an anim (kind 4) with ID -2 is left out.
    for (i = 0; i < 5; i++) {
        for (j = 0; j < DisplayClass::Layer[i].Count(); j++) {
            objp = DisplayClass::Layer[i][j];
            if (objp->Kind_Of() != 4 || objp->Fetch_ID() != -2) {
                unsigned long val = Coord_CRC(objp->Coord) + objp->Kind_Of();
                Add_CRC(&GameCRC, val);
            }
        }
    }

    for (i = 0; i < unknown_list_832470.Count(); i++) {
        objp = unknown_list_832470[i];
        if (objp->Kind_Of() != 4 || objp->Fetch_ID() != -2) {
            unsigned long val = Coord_CRC(objp->Coord) + objp->Kind_Of();
            Add_CRC(&GameCRC, val);
        }
    }

    Add_CRC(&GameCRC, unknown_id_source_a3d290->RandomNumber());
    Unknown_0062CF40(::Frame % 256);
}
