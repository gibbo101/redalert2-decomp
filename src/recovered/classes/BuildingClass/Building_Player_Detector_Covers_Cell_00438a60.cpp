// Test the player's active psychic detectors against an unallied house's cell.
// Free/static source ownership and input constness remain hypotheses.
#include "shared/building.hpp"
#include "shared/house.hpp"
#include "shared/cell.hpp"
// @ref ?unknown_475d60@CellClass@@QBE?AUCoordStruct@@XZ=00475d60
bool __fastcall Building_Player_Detector_Covers_Cell_00438a60(HouseClass const *house, CellClass const *cell)
{
    if (unknown_player_a35db4->Is_Ally(house))
        return false;
    int count = unknown_player_a35db4->unknown_b0.Count();
    for (int index = 0; index < count; ++index) {
        BuildingClass *detector = unknown_player_a35db4->unknown_b0[index];
        if (detector->unknown_slot195()) {
            CoordStruct position = detector->Center_Coord();
            CoordStruct other = cell->unknown_475d60();
            CoordStruct d((int)((unsigned)position.X-(unsigned)other.X),(int)((unsigned)position.Y-(unsigned)other.Y),(int)((unsigned)position.Z-(unsigned)other.Z));
            int distance = (int)unknown_sqrt_4ba410((double)d.X*d.X+(double)d.Y*d.Y+(double)d.Z*d.Z);
            int radius = (int)((unsigned int)detector->Type->PsychicDetectionRadius << 8);
            if (distance <= radius)
                return true;
        }
    }
    return false;
}
