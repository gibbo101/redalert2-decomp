// IonBlastClass: an ion cannon ground blast on the map (0x14 bytes, no vtable;
// TibSun ionblast.h's class, IonBlast.cpp unit 0x00520FA0). The constructor
// 0x00521270 stores the coordinate, clears +0x0C and +0x10 and adds the blast
// to IonBlasts (0x00A51F88, DynamicVectorClass<IonBlastClass *> per RTTI).
// Field names after TibSun and YRpp are hypotheses.
#ifndef RA2_SHARED_ION_BLAST_HPP
#define RA2_SHARED_ION_BLAST_HPP

#include "shared/coord.hpp"

template <class T> class DynamicVectorClass;

class IonBlastClass {
public:
    IonBlastClass(CoordStruct coord);       // 0x00521270
    ~IonBlastClass();                       // 0x005212F0

    void AI();                              // 0x00521340
    void Draw_It();                         // 0x00521CE0

    static void Update_All();               // 0x00521A70
    static void One_Time();                 // 0x00521A90
    static void Clear_All();                // 0x00521CB0
    static void Draw_All();                 // 0x00521FB0

    CoordStruct Coord;                      // +0x00 blast centre
    int Lifetime;                           // +0x0C frames since the blast landed (0)
    int unknown_10;                         // +0x10 (0; YRpp DisableIonBeam)

    // Every blast in progress (0x00A51F88). Declared only for IonBlast.cpp
    // (RA2_ION_BLAST_LIST, set by its first source): a class static of a type
    // with a constructor takes _$E initializer numbers in every unit that sees it.
#ifdef RA2_ION_BLAST_LIST
    static DynamicVectorClass<IonBlastClass *> IonBlasts;
#endif
};

#endif
