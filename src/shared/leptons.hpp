// Leptons: a distance in leptons (256 per cell), a class holding an int
// (hypothesis; the name follows YRpp's Leptons).
//
// Evidence: TechnoTypeClass::GuardRange (+0x504), which Read_INI reads with
// CCINIClass::Get_Lepton, is constructed as a class member: the constructor
// 0x006D9B40 schedules the arguments of the following Prerequisite list
// constructor exactly as a member with an inline constructor among the
// preceding initializers requires (as a plain int the pushes land one store
// earlier). AirRangeBonus (+0x5B4), also read with Get_Lepton, is a plain
// int: as a class member it moves the cameo name code instead. The INI reader
// and writer take and return plain ints (0x00469AE0, 0x00469B20); users
// read and write Value (Read_INI's assignment through a conversion would
// change its code).
#ifndef RA2_SHARED_LEPTONS_HPP
#define RA2_SHARED_LEPTONS_HPP

class Leptons {
public:
    Leptons() {}
    Leptons(int value) : Value(value) {}

    int Value;
};

#endif
