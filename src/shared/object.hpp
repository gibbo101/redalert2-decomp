// ObjectClass: the base of every map object (Object.cpp, 0x005D22E0-
// 0x005D555B; RTTI vtables 0x007A7498 primary (116 slots), 0x007A747C
// IRTTITypeInfo at +4, 0x007A7474 INoticeSink, 0x007A746C INoticeSource).
//
// Layout (from the constructor 0x005D22E0, destructor 0x005D2530 and Load
// 0x005D4760; names are hypotheses unless stated):
//   +0x00  AbstractClass (0x24; its +0x18 is a pointer swizzled by Load)
//   +0x24  int unknown_24, +0x28 int unknown_28, +0x2C int unknown_2c   0
//   +0x30  ObjectClass *unknown_30 (swizzled; cleared by the destructor)
//   +0x34  void *unknown_34, +0x38 void *unknown_38   (swizzled)
//   +0x3C  UnknownAudioController unknown_3c   (0x14 bytes)
//   +0x50  UnknownAudioController unknown_50
//   +0x64  int unknown_64      -1 (0x005D5520 sets it; -1 resets unknown_50)
//   +0x68  bool unknown_68
//   +0x6C  int Strength (health), +0x70 int unknown_70   0xFF
//   +0x74  bool unknown_74 ("on map"? slots 20/21 test it), +0x75 bool
//   +0x76  bool unknown_76     true
//   +0x77..+0x7C  bool         false
//   +0x7D  bool unknown_7d     true; slot 17 returns !unknown_7d
//   +0x80  int unknown_80      -1
//   +0x84  bool unknown_84, +0x85 bool unknown_85 (true)
//   +0x88  CoordStruct Coord   slot 18 (Center_Coord) returns it
//   +0x94  LineTrail *unknown_94   released by the destructor
//   size 0x98
// Every object is added to four global object lists (0x00A40368, 0x00AC0D60,
// 0x00AC0CB0, 0x00AC0C58) and removed from those and 0x00AC0CD8 when
// destroyed.
#ifndef RA2_SHARED_OBJECT_HPP
#define RA2_SHARED_OBJECT_HPP

#include "shared/unknown_globals.hpp"
#include "shared/abstract_type.hpp"
#include "shared/rgb_class.hpp"
class HouseClass;
class BuildingClass;

class ObjectClass;
class ObjectTypeClass;
class WarheadTypeClass;
class TechnoTypeClass;
class Rect;
class AircraftTypeClass;
class BuildingTypeClass;
class RadioClass;
class AnimTypeClass;
struct Point2D;
class WarheadTypeClass;
class ParticleSystemTypeClass;
class CellClass;
struct UnknownFacingDir;

// The 0x14-byte sound handle of the game objects, UnknownAudioController:
// shared/sound_play.hpp.
#include "shared/sound_play.hpp"

// The object at +0x34: TagClass (shared/tag.hpp).
#include "shared/tag.hpp"

// Three words cleared together when an object is constructed.
struct UnknownTriple {
    UnknownTriple() : unknown_00(0), unknown_04(0), unknown_08(0) {}
    UnknownTriple(NoInitClass const &noinit) {}
    int unknown_00;
    int unknown_04;
    int unknown_08;
};

// The object at +0x38: a bomb planted on the object (Bomb.cpp, unit 0x00435970:
// BombClass 0x00435BE0-0x004361EF and BombListClass; RTTI vtables 0x0079CA08
// primary (24 slots), 0x0079C9EC IRTTITypeInfo, 0x0079C9E4, 0x0079C9DC).
// Every bomb is in the unit's list 0x0084EB78. Field names are hypotheses.
class TechnoClass;
extern "C" GUID const CLSID_BombClass;          // 0x007A1E00
class BombClass : public AbstractClass {
public:
    BombClass();                                                        // 0x00435BE0
    BombClass(NoInitClass const &noinit);                               // 0x00435D00
    virtual ~BombClass();                                               // 0x00435C80

    void Unknown_00435D30();            // 0x00435D30 (sets the bomb off at once: DETONATE events)
    void Unknown_00435FB0();            // 0x00435FB0 (disarms: lets go of the target, the owner and the sound)
    int Unknown_00436000() const;       // 0x00436000 (the flicker frame, 0..11; 12 for a type 1 bomb)
    int Unknown_00435FF0() const;       // 0x00435FF0 (the bomb type, +0x30; TechnoClass slot 28)
    bool Unknown_00436070() const;      // 0x00436070 (a timed bomb, type 0, whose delay has passed)

    virtual HRESULT __stdcall GetClassID(GUID *clsid);                  // 0x00436100 slot 3
    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x00436140 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x004361D0 slot 6
    virtual int Kind_Of() const { return 0x44; }                        // 0x004369E0 slot 11 (inline)
    virtual int Size_Of() const { return sizeof(BombClass); }           // 0x004369D0 slot 12 (inline)
    virtual void Compute_CRC(WWCRCEngine &crc) const;                   // 0x00436090 slot 13

    TechnoClass *Owner;                 // +0x24 (the planting unit)
    HouseClass *unknown_28;             // +0x28 (the planting house; BuildingClass slot 78)
    ObjectClass *Target;                // +0x2C (the object the bomb sits on; its +0x38)
    int Type;                           // +0x30 (0 a timed bomb)
    int unknown_34;                     // +0x34 (the frame it was planted; the flicker counts from it)
    int unknown_38;                     // +0x38 (the frame it goes off)
    UnknownAudioController unknown_3c;  // +0x3C (the ticking sound)
    int unknown_50;                     // +0x50 (Rules BombTickingSound)
    int unknown_54;                     // +0x54
    bool unknown_58;                    // +0x58 (disarmed or gone off)
};

// Every bomb (0x0084EB78; defined by the Bomb unit).
extern DynamicVectorClass<BombClass *> unknown_BombClass_list_0084eb78;

// The planted bombs and the units whose type has BombSight (the object at
// 0x008322E0; TechnoClass slots 52 and 53 leave and join the second list).
class BombListClass {
public:
    void Unknown_004361F0();                                    // 0x004361F0 (the per-frame update; not recovered)
    void Add_Bomb(TechnoClass *owner, ObjectClass *target);     // 0x00436470 (an infantry plants a timed bomb on target)
    void Unknown_00436630(BombClass *bomb);                     // 0x00436630 (Bombs.Add)
    void Unknown_00436680(TechnoClass *techno);                 // 0x00436680 (joins the BombSight list)
    void Unknown_004366D0(TechnoClass *techno);                 // 0x004366D0 (leaves it)
    void Clear();                                               // 0x00436710 (both lists emptied at their size; +0x30 = 45)
    void Detach(AbstractClass *target);                         // 0x00436750 (drops the bomb, or the owner from every bomb)
    HRESULT Save(IStream *stream);                              // 0x004367C0 (both lists as a count and pointers)

    DynamicVectorClass<BombClass *> Bombs;                      // +0x00
    DynamicVectorClass<TechnoClass *> unknown_18;               // +0x18 (BombSight units)
    int unknown_30;                                             // +0x30 (45 when cleared, 1 when a bomb is planted)
};

// The trail at +0x94: shared/line_trail.hpp.
#include "shared/line_trail.hpp"

// Object.cpp's copies of the geometry header statics: the zero coordinate
// unknown_geometry_l (0x00A72F00), unknown_geometry_g (0x00A72F40) and
// unknown_geometry_j (0x00A72F30).

// The rules object (0x00839848) is `Rules`, a RulesClass: shared/rules.hpp.
#include "shared/rules.hpp"

// A game-mode value (0x00A3D298); Compute_CRC adds two flags for 0 and 5.
// Slot 76 passes the player's house (unknown_player_a35db4, shared/house.hpp)
// to slot 49.

// The type of ObjectClass::unknown_slot64's function-local static: a cell
// with a user-declared destructor (its first use registers an exit thunk,
// 0x005D44F0, which the geometry header's Cell statics do not; name
// hypothesis).
struct UnknownStaticCell {
    // Uninitialized lists (IsometricTileTypeClass slot 36's 129 cells).
    UnknownStaticCell() {}
    UnknownStaticCell(Cell const &cell) : Cell(cell) {}
    ~UnknownStaticCell() {}
    ::Cell Cell;
};

// The cell containing a coordinate (256 leptons per cell).
inline Cell Coord_Cell(CoordStruct const &coord)
{
    Cell cell;
    cell.X = (short)(coord.X / 256);
    cell.Y = (short)(coord.Y / 256);
    return cell;
}

// A cell as the placement tests read it (view of CellClass at Map[cell]).
class UnknownPlacementCellView {
public:
    // Whether the cell can be entered (0x00478760; hypothesis: Is_Clear_To_Move).
    bool Unknown_00478760(int speed, bool arg2, bool arg3, int arg4, int arg5, int arg6, bool arg7);
    // Whether a building of the type may be placed in the cell for the house
    // (0x004718B0; hypothesis).
    bool Unknown_004718B0(int speed, class TechnoTypeClass const *type, HouseClass *house);
    // The nearest free infantry spot in the cell around a coordinate, or the
    // invalid coordinate (0x00A41170) when the cell is full (0x004764B0;
    // hypothesis: Closest_Free_Spot; argument names hypotheses).
    CoordStruct Closest_Free_Spot(CoordStruct const &coord, bool any = false, bool alt = false) const;
};

// The map (0x008324E0) is `Map`, a MouseClass: shared/map_view.hpp.

class UnknownCellClass;

class ObjectClass : public AbstractClass {
public:
    ObjectClass();                                                         // 0x005D22E0
    ObjectClass(NoInitClass const &noinit);                                // 0x005D2500
    virtual ~ObjectClass();                                                // 0x005D2530

    // The direction from this object toward target (0x005D2730; hypothesis).
    UnknownFacingDir Direction_To(AbstractClass const *target) const;
    // The distance from this object to target (0x005D4CE0; hypothesis).
    int Distance_To(AbstractClass const *target) const;

    virtual HRESULT __stdcall Load(IStream *stream);                       // 0x005D4760
    virtual void Detach(AbstractClass *target, bool all = true);           // 0x005D3BD0
    virtual void Compute_CRC(WWCRCEngine &crc) const;                      // 0x005D4B10
    virtual bool unknown_slot17() const;                                   // 0x005D4F10
    virtual CoordStruct Center_Coord() const;                              // 0x005D4E40
    virtual bool unknown_slot20() const;                                   // 0x005D53E0
    virtual bool unknown_slot21() const;                                   // 0x005D5410
    virtual void AI();                                                     // 0x005D27F0

    virtual bool unknown_slot24();                                         // slot 24 (+0x60) 0x423d10
    virtual int unknown_slot25(bool arg1, int arg2);                        // slot 25 (+0x64) 0x423d20
    virtual void *unknown_slot26();                                        // slot 26 (+0x68) 0x5d27b0
    virtual int unknown_slot27(Cell const *cell, bool arg2, bool arg3);              // slot 27 (+0x6C) 0x5d2bb0
    virtual int unknown_slot28(ObjectClass *object, bool arg2);                        // slot 28 (+0x70) 0x5d2ba0
    virtual int unknown_slot29() const;                                    // slot 29 (+0x74) 0x5d2bc0
    virtual bool unknown_slot30() const;                                   // slot 30 (+0x78) 0x5d5490
    virtual bool unknown_slot31();                                         // slot 31 (+0x7C) 0x423d30
    virtual TechnoTypeClass *unknown_slot32();                             // slot 32 (+0x80) 0x5d5440 (the techno type; 0 here)
    virtual ObjectTypeClass *Class_Of() const;                             // slot 33 (+0x84) 0x4cddd0
    virtual int unknown_slot34();                                          // slot 34 (+0x88) 0x5d2c00
    virtual wchar_t const *unknown_slot35();                                          // slot 35 (+0x8C) 0x423d40
    virtual bool unknown_slot36();                                         // slot 36 (+0x90) 0x5d2c10
    virtual bool unknown_slot37();                                         // slot 37 (+0x94) 0x5d2c20
    virtual bool unknown_slot38();                                         // slot 38 (+0x98) 0x5d2c30
    virtual bool unknown_slot39();                                         // slot 39 (+0x9C) 0x5d2c40
    virtual CoordStruct unknown_slot40();                                  // slot 40 (+0xA0) 0x41b240
    virtual CoordStruct unknown_slot41(int arg1) const;                    // slot 41 (+0xA4) 0x5d54f0
    virtual CoordStruct unknown_slot42() const;                            // slot 42 (+0xA8) 0x41b270
    virtual CoordStruct unknown_slot43(int arg1);                        // slot 43 (+0xAC) 0x423d50
    virtual CoordStruct unknown_slot44(int arg1);                          // slot 44 (+0xB0) 0x41b2a0 (the center; ret 8)
    virtual int unknown_slot45() const;                                    // slot 45 (+0xB4) 0x5d5450
    virtual bool unknown_slot46(int arg1);                                  // slot 46 (+0xB8) 0x5d52f0
    virtual bool unknown_slot47();                                         // slot 47 (+0xBC) 0x423d90
    virtual bool unknown_slot48();                                         // slot 48 (+0xC0) 0x423da0
    virtual bool unknown_slot49(HouseClass *house);                                 // slot 49 (+0xC4) 0x423db0
    virtual ObjectTypeClass *unknown_slot50(bool arg1);                                  // slot 50 (+0xC8) 0x41b2d0
    virtual HouseClass *unknown_slot51(bool arg1);                                  // slot 51 (+0xCC) 0x41b2e0
    virtual bool unknown_slot52();                                          // slot 52 (+0xD0) 0x5d3700
    virtual bool unknown_slot53(CoordStruct const *coord, int dir);                        // slot 53 (+0xD4) 0x5d3890
    virtual void unknown_slot54(bool arg1);                                  // slot 54 (+0xD8) 0x5d3c10
    virtual void unknown_slot55(TechnoClass *techno);                                 // slot 55 (+0xDC) 0x5d2c50
    virtual bool unknown_slot56(CoordStruct const &coord);                                  // slot 56 (+0xE0) 0x5d4240
    virtual void unknown_slot57();                                         // slot 57 (+0xE4) 0x5d2ac0
    virtual void unknown_slot58(CoordStruct const &coord);                                  // slot 58 (+0xE8) 0x5d4960
    virtual void unknown_slot59(CoordStruct const &coord);                                  // slot 59 (+0xEC) 0x5d49e0
    virtual void unknown_slot60();                                         // slot 60 (+0xF0) 0x5d4e90
    virtual void unknown_slot61();                                         // slot 61 (+0xF4) 0x5d2c60
    virtual int unknown_slot62(TechnoClass *techno);                                  // slot 62 (+0xF8) 0x5d2c70
    virtual bool unknown_slot63(Rect *bounds, bool arg2, bool arg3);       // slot 63 (+0xFC) 0x5d34e0 (draws into bounds; hypothesis)
    virtual Cell const *unknown_slot64(int arg1);                                // slot 64 (+0x100) 0x5d4470
    virtual void unknown_slot65(int arg1, int arg2);                       // slot 65 (+0x104) 0x423dc0
    virtual void unknown_slot66(int arg1, int arg2);                       // slot 66 (+0x108) 0x423dd0
    virtual void unknown_slot67(int arg1, int arg2) {}                     // slot 67 (+0x10C) kept copy 0x595120 (Mission.cpp)
    virtual void unknown_slot68(int arg1, int arg2);                       // slot 68 (+0x110) 0x5d4e70
    virtual void unknown_slot69();                                         // slot 69 (+0x114) 0x5d2c80
    virtual void unknown_slot70(bool arg1, bool arg2);                       // slot 70 (+0x118) 0x5d2c90
    virtual bool unknown_slot71(int arg1);                                 // slot 71 (+0x11C) 0x5d4160 (callers test al: TechnoClass 0x006C2550, BulletClass 0x0045F6F0)
    virtual Rect unknown_slot72();                                         // slot 72 (+0x120) 0x5d3060 (the drawn area without the view offset; ret 4: the Rect comes back through the hidden pointer)
    virtual Rect unknown_slot73();                                         // slot 73 (+0x124) 0x5d31c0 (the drawn area; ret 4)
    virtual void unknown_slot74(int arg1);                                 // slot 74 (+0x128) 0x41b2f0
    virtual void unknown_slot75();                                         // slot 75 (+0x12C) 0x5d36e0
    virtual bool unknown_slot76();                                         // slot 76 (+0x130) 0x5d54b0
    virtual bool unknown_slot77(int arg1, int arg2, int arg3, bool arg4);   // slot 77 (+0x134) 0x5d2cb0
    virtual bool unknown_slot78(int arg1, int arg2, bool arg3);             // slot 78 (+0x138) 0x5d2ca0
    virtual void unknown_slot79(int arg1);                                 // slot 79 (+0x13C) 0x5d2cc0
    virtual bool unknown_slot80();                                         // slot 80 (+0x140) 0x5d2e70
    virtual void unknown_slot81();                                         // slot 81 (+0x144) 0x5d2df0
    virtual void unknown_slot82(int arg1);                                 // slot 82 (+0x148) 0x423de0
    virtual bool unknown_slot83();                                         // slot 83 (+0x14C) 0x41b300
    virtual bool unknown_slot84(CoordStruct const &coord, int weapon);     // slot 84 (+0x150) 0x5d2cd0
    virtual int unknown_slot85(int arg1);                                  // slot 85 (+0x154) 0x5d2ce0
    virtual int unknown_slot86(int *damage, int distance, WarheadTypeClass *warhead, TechnoClass *source, bool forced, int arg6); // slot 86 (+0x158) 0x5d3d20
    virtual void unknown_slot87(CoordStruct const &source, bool forced, bool nokidding);             // slot 87 (+0x15C) 0x5d2cf0
    virtual bool unknown_slot88();                                         // slot 88 (+0x160) 0x5d2d00
    virtual void unknown_slot89();                                         // slot 89 (+0x164) 0x5d2d10
    virtual int unknown_slot90();                                          // slot 90 (+0x168) 0x5d2d20
    virtual int unknown_slot91();                                          // slot 91 (+0x16C) 0x5d2d30
    virtual void unknown_slot92(int arg1);                                 // slot 92 (+0x170) 0x41b310
    virtual void unknown_slot93(int arg1);                                 // slot 93 (+0x174) 0x423df0
    virtual BuildingClass *Who_Can_Build_Me(bool in_theory, bool legal);   // slot 94 (+0x178) 0x5d4500 (RA1 name)
    virtual int unknown_slot95(RadioClass *radio, int message, long &param);              // slot 95 (+0x17C) 0x5d3cb0
    virtual bool unknown_slot96(HouseClass *house);                       // slot 96 (+0x180) 0x5d4230
    virtual void unknown_slot97(int arg1);                                 // slot 97 (+0x184) 0x5d2d40
    virtual void unknown_slot98(int arg1);                                 // slot 98 (+0x188) 0x5d2d50
    virtual void unknown_slot99(int path, char waypoint);                       // slot 99 (+0x18C) 0x5d53d0
    virtual void unknown_slot100(int facing);                              // slot 100 (+0x190) 0x5d2d60
    virtual int unknown_slot101(CellClass *arg1, int arg2, int arg3, int arg4, int arg5); // slot 101 (+0x194) 0x423e00
    virtual int unknown_slot102(UnknownCellClass *from, int facing, int *level, bool *ramp, UnknownCellClass *to); // slot 102 (+0x198) 0x423e10
    virtual void unknown_slot103(CoordStruct const &coord);                // slot 103 (+0x19C) 0x5d51c0
    virtual Cell unknown_slot104() const;                                 // slot 104 (+0x1A0) 0x41b320
    virtual AbstractClass *unknown_slot105();                                        // slot 105 (+0x1A4) 0x5d51e0
    virtual Cell unknown_slot106() const;                                 // slot 106 (+0x1A8) 0x5d5240
    virtual CellClass *unknown_slot107() const;                                   // slot 107 (+0x1AC) 0x5d5290
    virtual int unknown_slot108() const;                                   // slot 108 (+0x1B0) 0x5d4810
    virtual void unknown_slot109(int arg1);                                // slot 109 (+0x1B4) 0x5d4860
    virtual int unknown_slot110() const;                                   // slot 110 (+0x1B8) 0x5d4800
    virtual bool unknown_slot111();                                        // slot 111 (+0x1BC) 0x423e20
    virtual bool unknown_slot112();                                        // slot 112 (+0x1C0) 0x423e30
    virtual bool unknown_slot113();                                        // slot 113 (+0x1C4) 0x423e40
    virtual bool unknown_slot114();                                        // slot 114 (+0x1C8) 0x423e50
    virtual int unknown_slot115();                                         // slot 115 (+0x1CC) 0x423e60

    void unknown_func_5d2710();                                            // 0x005D2710
    bool Attach_Tag(TagClass *tag);                                        // 0x005D4430 (name hypothesis)
    bool operator<(ObjectClass const &other) const;                        // 0x005D4AB0 (by slot 45)
    bool operator>(ObjectClass const &other) const;                        // 0x005D4AE0 (by slot 45)
    bool unknown_func_5d27d0(char const *name) const;                       // 0x005D27D0 (type ID compare)
    int Unknown_005D47D0() const;                                          // 0x005D47D0 (a height level)
    int Distance_Squared(ObjectClass const *other) const;                  // 0x005D4DA0 (x/y; name hypothesis)
    int Distance_Squared(CoordStruct const &coord) const;                  // 0x005D4E00
    void unknown_func_5d4920(int z);                                       // 0x005D4920
    int unknown_5d47d0();                                                  // 0x005D47D0 (the cell level, +4 on a bridge)
    int unknown_5d4c00(AbstractClass *target);                             // 0x005D4C00 (a distance to target; UnitClass slot 304)
    double Health_Ratio() const;                                           // 0x005D4540
    void Set_Health_Ratio(double ratio);                                   // 0x005D4560
    int unknown_func_5d45b0() const;                                       // 0x005D45B0
    int unknown_func_5d4600() const;                                       // 0x005D4600
    int unknown_func_5d4670() const;                                       // 0x005D4670
    int unknown_func_5d46b0() const;                                       // 0x005D46B0 (0, 1 or 2)
    void unknown_func_5d5520(int value);                                   // 0x005D5520

    UnknownTriple unknown_24;               // +0x24
    ObjectClass *unknown_30;                // +0x30
    TagClass *unknown_34;                   // +0x34 (tag hypothesis: Attach_Tag counts on +0x2C)
    BombClass *unknown_38;                  // +0x38
    UnknownAudioController unknown_3c;      // +0x3C
    UnknownAudioController unknown_50;      // +0x50
    int unknown_64;                         // +0x64
    bool unknown_68;                        // +0x68
    int Strength;                           // +0x6C health (0xFF when constructed; hypothesis)
    int unknown_70;                         // +0x70
    bool unknown_74;                        // +0x74
    bool unknown_75;                        // +0x75
    bool unknown_76;                        // +0x76
    bool unknown_77;                        // +0x77
    bool unknown_78;                        // +0x78
    bool unknown_79;                        // +0x79
    bool unknown_7a;                        // +0x7A
    bool unknown_7b;                        // +0x7B
    bool unknown_7c;                        // +0x7C
    bool unknown_7d;                        // +0x7D
    int unknown_80;                         // +0x80
    bool unknown_84;                        // +0x84
    bool unknown_85;                        // +0x85
    // Unadjusted position copy at004F3F5A; nonvirtual dispatch is an inline-only hypothesis.
    CoordStruct Position_Coord_004f3f40() const { return Coord; }
    CoordStruct Coord;                      // +0x88
    LineTrail *unknown_94;                  // +0x94
};

// Global object lists: shared/object_lists.hpp.
#include "shared/object_lists.hpp"
extern DynamicVectorClass<AbstractClass *> unknown_abstracts_ac0bf8;   // 0x00AC0BF8 (TechnoClass +0x108 holders, bullets)
extern DynamicVectorClass<AbstractClass *> unknown_abstracts_ac0d08;   // 0x00AC0D08 (technos, supers)
extern DynamicVectorClass<AbstractClass *> unknown_objects_ac0c58; // 0x00AC0C58 (AbstractClass * by its vtable 0x007A177C)
extern DynamicVectorClass<AbstractClass *> unknown_objects_ac0cd8; // 0x00AC0CD8 (AbstractClass * by its vtable 0x007A177C)
extern DynamicVectorClass<ObjectClass *> unknown_objects_a40c60;   // 0x00A40C60 (objects with unknown_77 set)


#endif
