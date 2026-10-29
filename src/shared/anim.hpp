// AnimClass: a playing animation on the map (Anim.cpp, members
// 0x00420110-0x00423F62; RTTI vtables 0x0079C084 primary (118 slots),
// 0x0079C068 IRTTITypeInfo at +4, 0x0079C060 INoticeSink, 0x0079C058
// INoticeSource; bases ObjectClass and StageClass at +0x98).
//
// Layout (from the constructors 0x00420110 and 0x004208E0, the destructor
// 0x00420A90, Load 0x00422C30, Compute_CRC 0x00422DB0; names are
// hypotheses unless they follow an AnimTypeClass key):
//   +0x000  ObjectClass (0x98)
//   +0x098  StageClass: int Stage, CDTimerClass<FrameTimerClass> StageTimer
//           (+0x9C), int Rate (+0xA8)
//           int Step (+0xAC: frame step, 1; -1 for Reverse types)
//   +0x0B0  AnimTypeClass *Class  (swizzled; slot 33 returns it)
//   +0x0B4  ObjectClass *unknown_b4   the object the animation is attached
//           to (swizzled; Detach clears it)
//   +0x0B8  int unknown_b8 (-1), +0x0BC int unknown_bc, +0x0C0 int unknown_c0 (-1)
//   +0x0C4  PaletteName Palette (32 bytes; Load resolves it through
//           PaletteName::Load 0x00603380)
//   +0x0E4  int unknown_e4 (1000), +0x0E8 int ZAdjust, +0x0EC int YSortAdjust
//   +0x0F0  CoordStruct unknown_f0
//   +0x108  UnknownBounce unknown_108 (0x30 bytes; init 0x00436DC0)
//   +0x138, +0x148  UnknownQuaternion (4 floats; constructor 0x00622160)
//   +0x15C  AbstractClass *unknown_15c (swizzled; Detach clears it)
//   +0x164  int LoopDelay, +0x168 double unknown_168, +0x170 int unknown_170
//   +0x174..+0x17E  bool flags (+0x175 Loops count byte)
//   +0x180, +0x194  UnknownAudioController
//   size 0x1A8
// Every animation is added to Anims (0x00A40960).
#ifndef RA2_SHARED_ANIM_HPP
#define RA2_SHARED_ANIM_HPP

#include "shared/unknown_globals.hpp"
#include "shared/bounce.hpp"
#include "shared/anim_type.hpp"
#include "shared/cd_timer.hpp"
#include "shared/stage.hpp"
#include "shared/palette_name.hpp"

// UnknownBounce (the 0x30-byte bounce state at +0x108; 0x00436DC0 starts
// it) is shared with VoxelAnimClass: shared/bounce.hpp.

// UnknownQuaternion (four floats, out-of-line constructor 0x00622160): shared/bounce.hpp.

// Entries of the list at 0x00AB6EF8 (type unknown); AnimClass saves the
// index of the entry whose +0x30C value equals its unknown_bc.
struct UnknownAB6EF8Entry {
    char unknown_000[0x30C];
    int unknown_30c;                        // +0x30C
};
extern DynamicVectorClass<UnknownAB6EF8Entry *> unknown_list_ab6ef8;   // 0x00AB6EF8

// What PaletteName::Load returns, as AnimClass::Load uses it (hypothesis: a
// palette collection; virtual slot 6 looks up an entry of the 0x00AB6EF8
// kind).
class UnknownPaletteSource {
public:
    virtual void unknown_slot0();
    virtual void unknown_slot1();
    virtual void unknown_slot2();
    virtual void unknown_slot3();
    virtual void unknown_slot4();
    virtual void unknown_slot5();
    virtual UnknownAB6EF8Entry *unknown_slot6(int arg1);
};

extern "C" GUID const CLSID_AnimClass;      // 0x007A1BE0

class AnimClass : public ObjectClass, public StageClass {
public:
    AnimClass(AnimTypeClass *type, CoordStruct const &coord, int loop_delay, int loops, int flags, int zadjust);   // 0x00420110
    AnimClass();                                                        // 0x004208E0
    AnimClass(NoInitClass const &noinit) :                              // inline (Load)
        ObjectClass(noinit), StageClass(noinit), unknown_108(noinit), unknown_138(noinit), unknown_148(noinit) {}
    virtual ~AnimClass();                                               // 0x00420A90

    virtual HRESULT __stdcall GetClassID(GUID *clsid)                   // 0x00423E80 slot 3 (inline)
    {
        if (clsid == 0) {
            return E_POINTER;
        }
        *clsid = CLSID_AnimClass;
        return S_OK;
    }
    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x00422C30 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x00422D50 slot 6
    virtual void Detach(AbstractClass *target, bool all = true);        // 0x00422B20 slot 10
    virtual int Kind_Of() const { return 4; }                           // 0x00423EC0 slot 11 (inline)
    virtual int Size_Of() const { return sizeof(AnimClass); }           // 0x00423E70 slot 12 (inline)
    virtual void Compute_CRC(WWCRCEngine &crc) const;                   // 0x00422DB0 slot 13
    virtual CoordStruct Center_Coord() const;                           // 0x00420D90 slot 18
    virtual void AI();                                                  // 0x00421710 slot 23
    virtual int unknown_slot29() const;                                 // 0x004226A0 (layer)
    virtual ObjectTypeClass *Class_Of() const;                          // 0x00422EC0 slot 33
    virtual int unknown_slot45() const;                                 // 0x00420D70
    virtual bool unknown_slot52();                                       // 0x00422ED0
    virtual void unknown_slot60();                                      // 0x00423070
    virtual bool unknown_slot63(Rect *bounds, bool arg2, bool arg3);    // 0x00420E20
    virtual Cell const *unknown_slot64(int arg1);                 // 0x00421520 (no cell: a local static)
    virtual void unknown_slot67(int arg1, int arg2);                    // 0x00420E50
    virtual bool unknown_slot71(int arg1);                              // 0x00421500
    virtual int unknown_slot110() const;                                // 0x004230E0
    virtual int unknown_slot116();                                      // 0x00421580 (new: bounce step)
    virtual int unknown_slot117() const;                                // 0x00422EB0 (new: Class->End)

    void Attach_To(ObjectClass *object);                                // 0x00422540 (name hypothesis)
    void unknown_func_4226d0();                                         // 0x004226D0 (start)
    CoordStruct unknown_func_4237b0();                                  // 0x004237B0 (a place to come down)
    bool unknown_func_423b90(Cell const &cell);                   // 0x00423B90 (can it land in cell?)
    void unknown_func_4228f0();                                         // 0x004228F0 (scorch / crater)
    void unknown_func_422f50();                                         // 0x00422F50 (vein damage)
    void unknown_func_422680(AbstractClass *value);                     // 0x00422680 (sets unknown_15c)
    void unknown_func_422690(int value); // original DWORD store to existing +0x160, RET4
    void unknown_func_422c10();                                         // 0x00422C10 (unknown_17e = true)
    void unknown_func_422c20();                                         // 0x00422C20 (unknown_17e = false)

    AnimTypeClass *Class;                   // +0x0B0
    ObjectClass *unknown_b4;                // +0x0B4
    int unknown_b8;                         // +0x0B8
    int unknown_bc;                         // +0x0BC
    int unknown_c0;                         // +0x0C0
    PaletteName Palette;                    // +0x0C4 (Load resolves it through 0x00603380)
    int unknown_e4;                         // +0x0E4
    int ZAdjust;                            // +0x0E8
    int YSortAdjust;                        // +0x0EC
    CoordStruct unknown_f0;                 // +0x0F0
    int unknown_fc;                         // +0x0FC
    bool unknown_100;                       // +0x100
    bool unknown_101;                       // +0x101
    bool unknown_102;                       // +0x102
    bool unknown_103;                       // +0x103
    int unknown_104;                        // +0x104
    UnknownBounce unknown_108;              // +0x108
    UnknownQuaternion unknown_138;          // +0x138
    UnknownQuaternion unknown_148;          // +0x148
    bool unknown_158;                       // +0x158
    bool unknown_159;                       // +0x159
    AbstractClass *unknown_15c;             // +0x15C
    int unknown_160;                        // +0x160
    int LoopDelay;                          // +0x164
    double unknown_168;                     // +0x168
    int unknown_170;                        // +0x170
    bool unknown_174;                       // +0x174
    unsigned char Loops;                    // +0x175
    bool unknown_176;                       // +0x176
    bool unknown_177;                       // +0x177
    bool unknown_178;                       // +0x178
    bool unknown_179;                       // +0x179
    bool unknown_17a;                       // +0x17A
    bool unknown_17b;                       // +0x17B
    bool unknown_17c;                       // +0x17C
    bool unknown_17d;                       // +0x17D
    bool unknown_17e;                       // +0x17E
    UnknownAudioController unknown_180;     // +0x180
    UnknownAudioController unknown_194;     // +0x194
};

// The cell at 0x00548000 as AnimClass uses it: its first object (+0xE4)
// and the flags it clears (+0x140; hypothesis: CellClass's flag word).
struct UnknownAnimCell {
    char unknown_000[0x24];
    Cell unknown_24;                  // +0x24 the cell's own position
    char unknown_028[0x44 - 0x28];
    int unknown_44;                         // +0x44 (0x7E: veins)
    char unknown_048[0xE4 - 0x48];
    ObjectClass *unknown_e4;                // +0xE4 first object in the cell (linked through +0x30)
    char unknown_0e8[0xEC - 0xE8];
    int unknown_ec;                         // +0xEC land type (3, 4, 10 refuse; hypothesis)
    char unknown_0f0[0x10A - 0xF0];
    short unknown_10a;                      // +0x10A (a tiberium anim takes it as unknown_e4)
    char unknown_10c[0x11B - 0x10C];
    signed char unknown_11b;                // +0x11B height level
    bool unknown_11c;                       // +0x11C
    char unknown_11d;
    unsigned char unknown_11e;              // +0x11E (overlay data: vein / tiberium amount?)
    char unknown_11f[0x124 - 0x11F];
    unsigned char unknown_124;              // +0x124 (bits 0xE0: occupied?)
    char unknown_125[0x128 - 0x125];
    unsigned char unknown_128;              // +0x128 (bits 0xE0)
    char unknown_129[0x140 - 0x129];

    unsigned long Flags;                    // +0x140

    int Unknown_0047A220();                 // 0x0047A220 the cell's tiberium index (-1: none; hypothesis)
    void Unknown_00472540(int value);       // 0x00472540
    void Unknown_00475DB0(int value);       // 0x00475DB0 (AnimClass scorch/crater: 6)
    UnknownAnimCell *Unknown_00476AC0(int facing);   // 0x00476AC0 the adjacent cell (hypothesis)
};

// TechnoClass and TechnoTypeClass as the vein damage (0x00422F50) uses them
// (views; shared/techno.hpp is not included by this unit).
class UnknownAnimTechno : public ObjectClass {
public:
    bool Unknown_006D7910(int value);       // 0x006D7910
};
struct UnknownAnimTechnoType {
    char unknown_000[0xA9D];
    bool ImmuneToVeins;                     // +0xA9D
};

// A tiberium type as the chain reaction (0x004226D0) uses it (view of the
// list at 0x00AC0B30; shared/house.hpp's TiberiumClass list).
struct UnknownAnimTiberium {
    char unknown_000[0xC0];
    int unknown_c0;                                 // +0xC0 index in the 0x00AB6EF8 list
    DynamicVectorClass<AnimTypeClass *> unknown_c4; // +0xC4 explosion animations
};
extern DynamicVectorClass<UnknownAnimTiberium *> unknown_tiberiums_ac0b30;   // 0x00AC0B30

// Damage around a coordinate (0x0047E2C0, __fastcall; hypothesis).
void __fastcall Unknown_0047E2C0(CoordStruct const &coord, int damage, int arg3, WarheadTypeClass *warhead, int arg5);
// An explosion's effects at a coordinate (0x0047F600, __fastcall: the
// coordinate by value on the stack, damage in ECX, warhead in EDX;
// VoxelAnimClass::AI after Unknown_0047E2C0; hypothesis).
void __fastcall Unknown_0047F600(CoordStruct coord, int damage, WarheadTypeClass *warhead, int arg4, int arg5);
// The animation a warhead leaves where it hits (0x0047F4D0, defined in
// unowned/Select_Damage_Anim_0047f4d0.cpp).
AnimTypeClass *__fastcall Select_Damage_Anim(int damage, WarheadTypeClass *warhead, int land, CoordStruct *coords);
// Returns -15 for any coordinate (0x0047FCC0; a height adjustment for new
// animations, hypothesis).
int __stdcall Unknown_0047FCC0(CoordStruct position);

// The overlay types (AnimClass 0x00423B90): shared/overlay_view.hpp.
#include "shared/overlay_view.hpp"

// Called from the bullets' AI (0x00422BA0; arg1 is not read): damages the
// center of cell and, in game mode 0, has 0x004955D0
// schedule unknown_481fb0 (hypotheses).
void __fastcall Unknown_00422BA0(int arg1, Cell const &cell);
// Gives every animated-tiberium animation the palette entry of its cell's
// tiberium (0x00423C70; name hypothesis).
void __fastcall Unknown_00423C70();
// Unknown_004955D0 and unknown_palette_837e10 are in shared/unknown_globals.hpp.
void unknown_481fb0();                              // 0x00481FB0 (shared/ms_engine.hpp)

// The cell offsets of the eight facings (0x00851A70; shared/aircraft.hpp
// declares the same table as AdjacentCell).
extern Cell const unknown_adjacent_851a70[8];

// The distance of a cell offset (AnimClass 0x004237B0; hypothesis for the
// helper's form).
inline int Cell_Distance(int dx, int dy)
{
    double y = dy;
    double x = dx;
    return (int)unknown_sqrt_4ba410(x * x + y * y);
}

// Scorch and crater marks at a coordinate (0x00688460, 0x00688750,
// __fastcall; argument names hypotheses).
void __fastcall Unknown_00688460(CoordStruct const &coord, int width, int height, bool force);
void __fastcall Unknown_00688750(CoordStruct const &coord, int width, int height, bool force);

// Voc_Play_At (0x00713E60): shared/sound_play.hpp.

extern DynamicVectorClass<AnimClass *> Anims;     // 0x00A40960
// A second animation list (0x00A35E60): the destructor removes an
// animation whose ID is -2 from it instead of Anims (hypothesis).
extern DynamicVectorClass<AnimClass *> unknown_anims_a35e60;

// The index of the animation type with this ID; -1 for none or "<none>"
// (0x00420CD0; name hypothesis).
int __fastcall Anim_From_Name(char const *name);
// Stops the looping of every animation attached to an object (0x00420D30;
// name hypothesis).
void __fastcall Unknown_00420D30(ObjectClass *object);

#endif
