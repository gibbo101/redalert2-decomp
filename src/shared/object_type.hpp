// ObjectTypeClass: the base of the map-object types (ObjectType.cpp,
// members 0x005D57F0-0x005D800B; RTTI vtables 0x007A76F8 primary (40
// slots), 0x007A76DC IRTTITypeInfo at +4, 0x007A76D4 INoticeSink,
// 0x007A76CC INoticeSource).
//
// Layout (from the constructor 0x005D57F0, the NoInitClass constructor
// 0x005D5A80 and the destructor 0x005D5B60; names are hypotheses):
//   +0x000  AbstractTypeClass (0x98)
//   +0x098  bool unknown_98, unknown_99, unknown_9a
//   +0x09C  int unknown_9c, +0x0A0 int MaxStrength
//   +0x0A4  void *unknown_a4   (slot 39 returns it; freed when unknown_a8)
//   +0x0A8  bool unknown_a8    unknown_a4 is owned
//   +0x0AC  int unknown_ac
//   +0x0B0, +0x0B8, +0x0C0  UnknownObjectPair (8 bytes each)
//   +0x0C8  UnknownObjectPair unknown_c8[15]
//   +0x140  UnknownObjectPair unknown_140[15]
//   +0x1B8  bool, +0x1BC int, +0x1C0 int (-1), +0x1C4 int (-1)
//   +0x1C8  FixedString<25> unknown_1c8      the ID when constructed
//   +0x1E1  bool, +0x1E2 bool
//   +0x1E3  FixedString<25> unknown_1e3      from the string at 0x0083C55C
//   +0x1FC..+0x20A  bools (0x1FE, 0x200, 0x201, 0x205 true)
//   +0x20B..+0x20D  unsigned char (0x80)
//   +0x210  int unknown_210 (0x10)
//   +0x214, +0x228, +0x23C, +0x250  UnknownBuffer (0x14 bytes each)
//   size 0x264
// Every type is added to ObjectTypes (0x00A72F90) and removed when destroyed.
#ifndef RA2_SHARED_OBJECT_TYPE_HPP
#define RA2_SHARED_OBJECT_TYPE_HPP

#include "shared/object.hpp"
#include "shared/rgb_class.hpp"

// Two owned pointers released together (hypothesis: a voxel and its motion
// library; the destructor 0x005D4A60 destroys them with 0x007190C0 and
// 0x0059EBA0).
class FileClass;

#include "shared/unknown_pair_first.hpp"
#include "shared/unknown_pair_second.hpp"

class UnknownObjectPair {
public:
    UnknownObjectPair() : unknown_00(0), unknown_04(0) {}
    UnknownObjectPair(NoInitClass const &noinit) {}
    ~UnknownObjectPair();               // 0x005D4A60

    UnknownPairFirst *unknown_00;
    UnknownPairSecond *unknown_04;
};

// A heap block with a size and a flag (0x14 bytes; hypothesis); released
// and cleared when destroyed.
class UnknownBuffer {
public:
    // Index nodes are eight bytes: signed key at +0 and an opaque voxel-cache value at +4.
    struct NodeElement {
        NodeElement() {} // Reference node lifetime: default construction deliberately leaves both fields unset.
        bool operator==(NodeElement const &other) const { return ID==other.ID; }
        bool operator<(NodeElement const &other) const { return ID<other.ID; }
        int ID;
        void *Data;
    };
    void * const &operator[](int const &id) const;
    bool Add_Index(int const &id, void * const &data);
    void Invalidate_Archive() const;
    void Set_Archive(NodeElement const *node) const;
    bool Increase_Size_006d97c0(int amount); // cache-node capacity growth, original0x006D97C0
    bool Is_Present_0070a350(int const &id) const; // ECX owner, RET4, AL bool; sorts and updates archive.
    bool Is_Archive_Same_0070a3f0(int const &id) const; // ECX owner, RET4, AL bool.
    NodeElement const *Search_For_Node_006d9850(int const &id) const; // ECX owner, RET4; sorts before signed-key binary search.
    static int __cdecl Compare_Nodes_006d98d0(void const *left,void const *right)
        {
            if (*static_cast<int const *>(left)==*static_cast<int const *>(right)) return 0;
            if (*static_cast<int const *>(left)<*static_cast<int const *>(right)) return -1;
            return 1;
        }
    UnknownBuffer() : unknown_00(0), unknown_04(0), unknown_08(0), unknown_0c(false), unknown_10(0) {}
    ~UnknownBuffer()
    {
        operator delete(unknown_00);
        unknown_00 = 0;
        unknown_04 = 0;
        unknown_08 = 0;
        unknown_0c = false;
        unknown_10 = 0;
    }

    void *unknown_00;
    int unknown_04;
    int unknown_08;
    bool unknown_0c;
    int unknown_10;
};

void operator delete(void *pointer);

// The string ObjectTypeClass copies into unknown_1e3 (0x0083C55C).
extern char unknown_string_83c55c[];
// ObjectType.cpp's copy of a header-computed value (0x00A72FDC).
extern int unknown_a72fdc;
// The shared shape files ObjectTypeClass::One_Time (0x005D5E00) loads:
// PIPBRD.SHP (0x00A72FE0), PIPS.SHP (0x00A72FE4), PIPS2.SHP (0x00A72FE8)
// and TALKBUBL.SHP (0x00A72FEC).
extern void const *unknown_pipbrd_shapes_a72fe0;
extern void const *unknown_pips_shapes_a72fe4;
extern void const *unknown_pips2_shapes_a72fe8;
extern void const *unknown_talkbubl_shapes_a72fec;

class BuildingClass;

class ObjectTypeClass : public AbstractTypeClass {
public:
    ObjectTypeClass(char const *ini_name);                              // 0x005D57F0
    ObjectTypeClass(NoInitClass const &noinit);                         // 0x005D5A80
    virtual ~ObjectTypeClass();                                         // 0x005D5B60

    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x005D7C30
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x005D7E60
    virtual HRESULT __stdcall GetSizeMax(ULARGE_INTEGER *size);         // 0x005D7E80
    virtual bool Read_INI(CCINIClass &ini);                             // 0x005D7810 slot 25

    // Slots 27, 28 and 39 are inline in the original header. The kept
    // copies of 27 and 39 come from AircraftType.cpp (0x0041C2E0,
    // 0x0041C300, the first type unit in link order); 28 from AnimType.cpp
    // (0x00426760).
    virtual CoordStruct unknown_slot27(CoordStruct const &coord) const { return coord; }  // slot 27
    virtual int unknown_slot28() const;                                  // slot 28 (-1)
    virtual int unknown_slot29() const;                                  // 0x005D5D00 (0)
    virtual CoordStruct unknown_slot30() const;                          // 0x005D5D10 (10, 10, 10)
    virtual CoordStruct unknown_slot31() const;                          // 0x005D5D30
    // Slots 32 and 35 (RA1: Create_And_Place, Create_One_Of; the overrides
    // take two and one stack arguments).
    virtual bool unknown_slot32(Cell const &cell, HouseClass *house) const = 0;   // slot 32
    virtual int unknown_slot33(int arg1) const;                          // 0x005D5D60 (0)
    virtual int unknown_slot34() const;                                  // 0x005D5D70 (0)
    virtual ObjectClass *unknown_slot35(HouseClass *house) const = 0;   // slot 35
    virtual Cell const *unknown_slot36(int arg1) const;            // 0x005D5D90
    // The house's building that can produce this type (RA1:
    // Who_Can_Build_Me): primary factories first, else the last match.
    virtual BuildingClass *Who_Can_Build_Me(bool in_theory, bool legal, bool check_limit, HouseClass *house) const; // 0x005D5FC0 slot 37
    virtual int unknown_slot38() const;                                  // 0x005D5D80 (0)
    virtual void *unknown_slot39() const { return unknown_a4; }          // slot 39

    // Loads the shared pip and talk-bubble shapes once (PIPBRD.SHP,
    // PIPS.SHP, PIPS2.SHP, TALKBUBL.SHP; RA1 name One_Time).
    static void One_Time();                 // 0x005D5E00
    // Frees the 15 + 15 voxel pairs (unknown_c8, unknown_140).
    void unknown_func_5d66a0();             // 0x005D66A0
    // Releases every type's four cached buffers and resets
    // unknown_839aa8 from unknown_839aa4 (name hypothesis).
    static void Clear_Voxel_Indexes();      // 0x005D7EF0
    void unknown_func_5d6730();             // 0x005D6730 (loads the .VXL voxel; hypothesis)
    // Loads the turret and barrel voxels (<image>TUR / <image>BARL .VXL and
    // .HVA) of a turreted unit type into unknown_b8 and unknown_c0.
    void unknown_func_5d72b0();             // 0x005D72B0
    // Loads turret voxel `index` (<image>TUR[n].VXL/.HVA) into
    // unknown_c8[index]; false (and both freed) unless both load.
    bool unknown_func_5d6150(char const *image, int index);    // 0x005D6150
    // The barrel counterpart (<image>BARL[n], unknown_140[index]); a
    // missing .VXL returns true.
    bool unknown_func_5d63f0(char const *image, int index);    // 0x005D63F0
    void unknown_func_5d7630();             // 0x005D7630 (theater image load; hypothesis)
    // Rewrites a file name's second letter for a theater (0x005D7BD0) or to
    // the generic 'G' (0x005D7C20); names hypotheses.
    static void __fastcall Theater_Naming_Convention(char *buffer, int theater);
    // The object type whose ID matches name (case-insensitive), else null.
    static ObjectTypeClass *__fastcall Find_From_Name(char const *name);   // 0x005D7EA0
    static void __fastcall Generic_Naming_Convention(char *buffer);

#ifdef OBJECT_TYPE_DECLARE_OBJECT_TYPES
    // Every type, in creation order (0x00A72F90). A class static member: its atexit destructor
    // 0x005D5790 is guarded (bit 0 of 0x00A72FD9), as VC6 emits for static data members
    // (TibSun objtype.h ObjectTypeClass::ObjectTypes). Guarded: only ObjType.cpp uses it, and the
    // declaration renumbers the _$E initializers of every other unit that includes this header.
    static DynamicVectorClass<ObjectTypeClass *> ObjectTypes;
#endif

    RGBClass RadialColor;                   // +0x098 (RadialColor=)
    int unknown_9c;                         // +0x09C
    int MaxStrength;                         // +0x0A0
    void *unknown_a4;                       // +0x0A4 (the loaded image; hypothesis)
    bool unknown_a8;                        // +0x0A8
    int unknown_ac;                         // +0x0AC
    UnknownObjectPair unknown_b0;           // +0x0B0
    UnknownObjectPair unknown_b8;           // +0x0B8
    UnknownObjectPair unknown_c0;           // +0x0C0
    UnknownObjectPair unknown_c8[15];       // +0x0C8
    UnknownObjectPair unknown_140[15];      // +0x140
    bool unknown_1b8;                       // +0x1B8
    int unknown_1bc;                        // +0x1BC
    int unknown_1c0;                        // +0x1C0
    int unknown_1c4;                        // +0x1C4
    FixedString<25> unknown_1c8;            // +0x1C8 (image name: "Image="; hypothesis)
    bool unknown_1e1;                       // +0x1E1
    bool unknown_1e2;                       // +0x1E2
    FixedString<25> unknown_1e3;            // +0x1E3
    bool unknown_1fc;                       // +0x1FC ("Theater=" in AnimType Read_INI)
    bool unknown_1fd;                       // +0x1FD
    bool unknown_1fe;                       // +0x1FE
    bool unknown_1ff;                       // +0x1FF
    bool unknown_200;                       // +0x200 (ObjectClass slot 76 reads it)
    bool unknown_201;                       // +0x201
    bool unknown_202;                       // +0x202
    bool unknown_203;                       // +0x203
    bool unknown_204;                       // +0x204
    bool unknown_205;                       // +0x205
    bool unknown_206;                       // +0x206
    bool unknown_207;                       // +0x207 ("NewTheater=" in AnimType Read_INI)
    bool unknown_208;                       // +0x208
    bool unknown_209;                       // +0x209
    bool unknown_20a;                       // +0x20A
    RGBClass LineTrailColor;                // +0x20B (LineTrailColor=, art INI)
    int unknown_210;                        // +0x210
    UnknownBuffer unknown_214;              // +0x214
    UnknownBuffer unknown_228;              // +0x228
    UnknownBuffer unknown_23c;              // +0x23C
    UnknownBuffer unknown_250;              // +0x250
};

#ifndef OBJECT_TYPE_DECLARE_OBJECT_TYPES
// The pre-recovery global spelling of ObjectTypeClass::ObjectTypes, still seen by the other units
// that include this header: dropping it changes BaseClass::Read_INI 0x0042C460 (type-count
// sensitivity), so it stays until those units are re-checked. No object has this name.
extern DynamicVectorClass<ObjectTypeClass *> ObjectTypes;
#endif

#endif
