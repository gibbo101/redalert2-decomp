// WDTState layout shared by the World Domination Tour and WOL callbacks.
#ifndef RA2_SHARED_WDT_STATE_HPP
#define RA2_SHARED_WDT_STATE_HPP
#include "shared/reference_counted.hpp"
#include "shared/vector_class.hpp"
class WDTTerritory;
class WDTState : public ReferenceCounted {
public:
    virtual ~WDTState();    // 0x0072C2D0
    static rc_ptr<WDTState> __fastcall Create(unsigned char *data); // 0x0072BEB0
    bool Is_Valid() const; // 0x0072C390: unknown_44 is non-null
    unsigned char Is_Previous_Cycle() const; // 0x0072C3A0: byte at +0x48

    char *ShortLabel;                         // +0x08
    char *LongLabel;                          // +0x0C
    char *unknown_10;                         // +0x10
    unsigned char unknown_14;                       // +0x14
    int unknown_18;                                 // +0x18
    char unknown_1c[0x20 - 0x1C];
    unsigned unknown_20;                            // +0x20
    unsigned ConflictCount;                         // +0x24
    long unknown_28; // +0x28, added to time(0) by OnWDTState
    DynamicVectorClass<rc_ptr<WDTTerritory> > Territories;  // +0x2C
    void **unknown_44;                              // +0x44
};
#endif
