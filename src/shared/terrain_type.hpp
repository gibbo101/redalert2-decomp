// TerrainTypeClass: the type of a terrain object (trees, rocks, veinholes;
// TerrainType.cpp, members 0x006E5260-0x006E5B6C; RTTI vtables 0x007AD5E0
// primary (40 slots), 0x007AD5C4 IRTTITypeInfo at +4, 0x007AD5BC
// INoticeSink, 0x007AD5B4 INoticeSource).
//
// Layout (from the constructor 0x006E5260, Read_INI 0x006E5630 and
// Compute_CRC 0x006E58C0; INI key names are the original strings):
//   +0x000  ObjectTypeClass (0x264)
//   +0x264  int ArrayIndex             index in TerrainTypes (slot 16)
//   +0x268  int Foundation             "Foundation" (art INI, image section)
//   +0x26C  RGBClass RadarColor        the first frame's colour
//   +0x270  int AnimationRate          "AnimationRate"
//   +0x274  float AnimationProbability "AnimationProbability"
//   +0x278  int TemperateOccupationBits "TemperateOccupationBits" (7)
//   +0x27C  int SnowOccupationBits     "SnowOccupationBits" (7)
//   +0x280  bool WaterBound, +0x281 bool SpawnsTiberium,
//   +0x282  bool IsFlammable, +0x283 bool IsAnimated, +0x284 bool IsVeinhole
//   +0x288  Cell const *OccupyList   the foundation's cell list
//   size 0x28C
// Every type is in TerrainTypes (0x00A40320, a DynamicVectorClass defined
// by the global-list unit at 0x004D2BA0).
#ifndef RA2_SHARED_TERRAIN_TYPE_HPP
#define RA2_SHARED_TERRAIN_TYPE_HPP

#include "shared/object_type.hpp"
#include "shared/rgb_class.hpp"

class TerrainClass;
class TerrainTypeClass;

extern "C" GUID const CLSID_TerrainTypeClass;   // 0x007A1B50

// The type list (0x00A40320; the name is the global-list unit's).
extern DynamicVectorClass<TerrainTypeClass *> TerrainTypes;

// The occupation lists by foundation (0x00AC0430, ten cells each, ended by
// 0x7FFF, 0x7FFF); TerrainType.cpp defines and initializes them
// (0x006E4D60; not recovered).
extern Cell unknown_foundation_lists_ac0430[][10];

class TerrainTypeClass : public ObjectTypeClass {
public:
    TerrainTypeClass(char const *ini_name);                             // 0x006E5260
    TerrainTypeClass(NoInitClass const &noinit);                        // 0x006E53B0
    virtual ~TerrainTypeClass();                                        // 0x006E53E0

    static void __fastcall Init(int theater);                           // 0x006E5460
    static int __fastcall From_Name(char const *name);                  // 0x006E5510
    static TerrainTypeClass *__fastcall Find_Or_Make(char const *name); // 0x006E5A20

    virtual HRESULT __stdcall GetClassID(GUID *clsid);                  // 0x006E59E0 slot 3
    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x006E5950 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x006E59C0 slot 6
    virtual int Kind_Of() const { return 0x25; }                        // 0x006E5AB0 slot 11 (inline)
    virtual int Size_Of() const { return sizeof(TerrainTypeClass); }    // 0x006E5AC0 slot 12 (inline)
    virtual void Compute_CRC(WWCRCEngine &crc) const;                   // 0x006E58C0 slot 13
    virtual int unknown_slot16() const { return ArrayIndex; }           // 0x006E5AD0 (inline)
    virtual bool Read_INI(CCINIClass &ini);                             // 0x006E5630 slot 25
    virtual CoordStruct unknown_slot27(CoordStruct const &coord) const; // 0x006E5850 (not below the ground)
    virtual bool unknown_slot32(Cell const *cell, HouseClass *house);   // 0x006E5560 (creates a terrain object)
    virtual ObjectClass *unknown_slot35(HouseClass *house);             // 0x006E55A0
    virtual Cell const *unknown_slot36(int arg1) const;           // 0x006E55D0 (the occupation list)

    int ArrayIndex;                         // +0x264
    int Foundation;                         // +0x268
    RGBClass RadarColor;                    // +0x26C
    int AnimationRate;                      // +0x270
    float AnimationProbability;             // +0x274
    int TemperateOccupationBits;            // +0x278
    int SnowOccupationBits;                 // +0x27C
    bool WaterBound;                        // +0x280
    bool SpawnsTiberium;                    // +0x281
    bool IsFlammable;                       // +0x282
    bool IsAnimated;                        // +0x283
    bool IsVeinhole;                        // +0x284
    Cell const *OccupyList;           // +0x288
};

#endif
