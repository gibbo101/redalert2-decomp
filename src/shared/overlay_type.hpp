// OverlayTypeClass: the type of an overlay (walls, ore, crates, rocks;
// OverlayType.cpp, members 0x005DC5A0-0x005DD31C; RTTI vtables 0x007A7A08
// primary (41 slots), 0x007A79EC IRTTITypeInfo at +4, 0x007A79E4
// INoticeSink, 0x007A79DC INoticeSource).
//
// Layout (from the constructor 0x005DC5A0, Read_INI 0x005DCAA0, Compute_CRC
// 0x005DCD70 and Load 0x005DCE10; INI key names are the original strings):
//   +0x000  ObjectTypeClass (0x264)
//   +0x264  int ArrayIndex            index in OverlayTypes (slot 16)
//   +0x268  int Land                  "Land" (LandType; 5 for Tiberium)
//   +0x26C  AnimTypeClass *CellAnim   "CellAnim" (swizzled)
//   +0x270  int DamageLevels          "DamageLevels" (art INI image section; 1)
//   +0x274  int Strength              "Strength" (1)
//   +0x278  bool Wall, +0x279 Tiberium, +0x27A Crate, +0x27B CrateTrigger,
//   +0x27C  bool NoUseTileLandType (true), +0x27D IsVeinholeMonster,
//   +0x27E  bool IsVeins, +0x27F DemandLoad (art INI), +0x280 Explodes,
//   +0x281  bool ChainReaction, +0x282 Overrides, +0x283 DrawFlat (true),
//   +0x284  bool IsRubble, +0x285 IsARock
//   size 0x288
// Every type is in OverlayTypes (0x00A35DE8, a DynamicVectorClass defined by
// the global-list unit at 0x004D2BA0).
#ifndef RA2_SHARED_OVERLAY_TYPE_HPP
#define RA2_SHARED_OVERLAY_TYPE_HPP

#include "shared/object_type.hpp"
#include "shared/rgb_class.hpp"

class AnimTypeClass;
class OverlayClass;
class OverlayTypeClass;

extern "C" GUID const CLSID_OverlayTypeClass;   // 0x007A1B70

// The type list (0x00A35DE8; the name is the global-list unit's).
extern DynamicVectorClass<OverlayTypeClass *> OverlayTypes;

class OverlayTypeClass : public ObjectTypeClass {
public:
    OverlayTypeClass(char const *ini_name);                             // 0x005DC5A0
    OverlayTypeClass(NoInitClass const &noinit);                        // 0x005DC700
    virtual ~OverlayTypeClass();                                        // 0x005DC730

    static int __fastcall From_Name(char const *name);                  // 0x005DC7B0
    static void __fastcall Init(int theater);                           // 0x005DC960
    static OverlayTypeClass *__fastcall Find_Or_Make(char const *name); // 0x005DCF70
    RGBClass unknown_func_5dd000(unsigned frame) const;                 // 0x005DD000 (a frame's colour; radar hypothesis)

    virtual HRESULT __stdcall GetClassID(GUID *clsid);                  // 0x005DCF30 slot 3
    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x005DCE10 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x005DCF10 slot 6
    virtual int Kind_Of() const { return 0x15; }                        // 0x005DD260 slot 11 (inline)
    virtual int Size_Of() const { return sizeof(OverlayTypeClass); }    // 0x005DD270 slot 12 (inline)
    virtual void Compute_CRC(WWCRCEngine &crc) const;                   // 0x005DCD70 slot 13
    virtual int unknown_slot16() const { return ArrayIndex; }           // 0x005DD280 (inline)
    virtual bool Read_INI(CCINIClass &ini);                             // 0x005DCAA0 slot 25
    virtual CoordStruct unknown_slot27(CoordStruct const &coord) const; // 0x005DCD50 (the coordinate unchanged)
    virtual bool unknown_slot32(Cell const &cell, HouseClass *house) const;   // 0x005DC870 (places an overlay at the cell)
    virtual ObjectClass *unknown_slot35(HouseClass *house) const;       // 0x005DC8B0 (an unplaced overlay)
    virtual Cell const *unknown_slot36(int arg1) const;           // 0x005DC800 (one cell)
    virtual void *unknown_slot39() const;                               // 0x005DD150 (demand-loads the image)
    virtual void unknown_slot40(Point2D const *point, Rect const *window, int frame);   // 0x005DC8E0 (draws a frame at a tactical point; new slot)

    int ArrayIndex;                         // +0x264
    int Land;                               // +0x268
    AnimTypeClass *CellAnim;                // +0x26C
    int DamageLevels;                       // +0x270
    int Strength;                           // +0x274
    bool Wall;                              // +0x278
    bool Tiberium;                          // +0x279
    bool Crate;                             // +0x27A
    bool CrateTrigger;                      // +0x27B
    bool NoUseTileLandType;                 // +0x27C
    bool IsVeinholeMonster;                 // +0x27D
    bool IsVeins;                           // +0x27E
    bool DemandLoad;                        // +0x27F
    bool Explodes;                          // +0x280
    bool ChainReaction;                     // +0x281
    bool Overrides;                         // +0x282
    bool DrawFlat;                          // +0x283
    bool IsRubble;                          // +0x284
    bool IsARock;                           // +0x285
};

#endif
