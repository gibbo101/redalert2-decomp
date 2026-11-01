#pragma once
// UnitTrackerClass (the unit at 0x0070C440-0x0070C60F): per-type counts a
// house keeps for internet game statistics (Westwood UTRACKER). In this game
// the counts are a fixed 512-entry array inside the object (0x808 bytes;
// house.hpp still names the six HouseClass members UnknownHouseTracker).
class UnitTrackerClass {
public:
    UnitTrackerClass();                                 // 0x0070C440
    ~UnitTrackerClass();                                // 0x0070C480

    void Increment_Unit_Total(int unit_type);           // 0x0070C490
    void Decrement_Unit_Total(int unit_type);           // 0x0070C4B0
    void Set_Unit_Count(int count);                     // 0x0070C4D0 (clears all 512, then limits the count)
    int Get_All_Totals_Sum();                           // 0x0070C510
    int *Get_All_Totals();                              // 0x0070C530
    void Clear_Unit_Total();                            // 0x0070C540
    void To_Network_Format();                           // 0x0070C570
    void To_PC_Format();                                // 0x0070C5C0

    int UnitTotals[512];                                // +0x000
    int UnitCount;                                      // +0x800
    int InNetworkFormat;                                // +0x804
};
