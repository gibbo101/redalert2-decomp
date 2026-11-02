// TheaterTypeStruct: the theater description table (moved from shared/anim_type.hpp).
#ifndef RA2_SHARED_THEATER_TYPE_HPP
#define RA2_SHARED_THEATER_TYPE_HPP

// A theater's names (0x68 bytes; the table at 0x0079AB68; field names are
// hypotheses from the data: "TEMPERATE", "Name:Temperate", "TEMPERAT",
// "ISOTEMP", "TEM", "MMT", "T").
struct TheaterTypeStruct {
    char Name[16];          // +0x00
    char UIName[32];        // +0x10
    char Root[10];          // +0x30
    char IsoRoot[10];       // +0x3A
    char Suffix[4];         // +0x44 image file extension
    char MMSuffix[4];       // +0x48
    char Letter[4];         // +0x4C
    float unknown_50;       // +0x50
    float unknown_54;       // +0x54
    double unknown_58;      // +0x58
    int unknown_60;         // +0x60
    int unknown_64;         // +0x64
};
extern TheaterTypeStruct Theaters[];          // 0x0079AB68

#endif
