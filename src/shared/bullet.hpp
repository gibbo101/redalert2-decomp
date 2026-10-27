// BulletClass: a projectile in flight (Bullet.cpp, 0x0045F120-0x004642E9;
// RTTI vtables 0x0079D374 primary (119 slots), 0x0079D358 IRTTITypeInfo at
// +4, 0x0079D350 INoticeSink, 0x0079D348 INoticeSource).
//
// Layout (from the constructor 0x0045F3B0, Construct 0x0045F4F0, the
// destructor 0x0045F590 and Load 0x004637B0; names follow the YRpp
// BulletClass where the evidence agrees and are hypotheses):
//   +0x000  ObjectClass (0x98)
//   +0x098  BulletTypeClass *Type          (swizzled; slot 33 returns it)
//   +0x09C  TechnoClass *Owner             (swizzled)
//   +0x0A0  bool unknown_a0
//   +0x0A4  UnknownBulletData Data (0x28: two frame timers, four ints;
//           default constructor out of line 0x004CEDF0)
//   +0x0CC  bool Bright
//   +0x0D0  BulletVelocity Velocity (three doubles; operator+= 0x004642A0)
//   +0x0E8  int unknown_e8, +0x0EC bool unknown_ec (true), +0x0ED bool (true)
//   +0x0F0  int unknown_f0
//   +0x0F4  AbstractClass *Target          (swizzled; slot 117 sets it)
//   +0x0F8  int Speed, +0x0FC int InheritedColor (-1), +0x100 int
//   +0x108  double unknown_108 (0)
//   +0x110  WarheadTypeClass *WH           (swizzled)
//   +0x114  unsigned char AnimFrame, +0x115 unsigned char AnimRateCounter
//   +0x118  WeaponTypeClass *WeaponType    (swizzled; 0x00463BA0/0x00463BB0)
//   +0x11C  CoordStruct SourceCoords, +0x128 CoordStruct TargetCoords
//   +0x134  Cell LastMapCoords (-1, -1)
//   +0x138  int DamageMultiplier (0x100 after Construct)
//   +0x13C  AnimClass *NextAnim            (swizzled)
//   +0x140  bool SpawnNextAnim, +0x144 int Range
//   size 0x148 (slot 12)
// Every bullet is added to Bullets (0x00A40CE8) and removed when destroyed.
#ifndef RA2_SHARED_BULLET_HPP
#define RA2_SHARED_BULLET_HPP

#include "shared/unknown_globals.hpp"
#include "shared/object.hpp"
#include "shared/cd_timer.hpp"
#include "shared/win32_api.hpp"

class BulletTypeClass;
class CellClass;
class HouseClass;
// Whether a path between two cells is blocked for a bullet type (0x004BBAF0,
// __fastcall: the source and target cells in ECX/EDX; hypothesis).
int __fastcall Unknown_004BBAF0(CellClass *source, CellClass *target, CellClass *last, CoordStruct coord, BulletTypeClass *type, HouseClass *house);
// The height of one cell level in leptons (0x00850348; hypothesis).
extern int unknown_level_height_850348;
// A coordinate moved a random distance away (0x00491750, __fastcall; the
// result through ECX; hypothesis: Westwood's Coord_Scatter).
CoordStruct __fastcall Coord_Scatter(CoordStruct const &coord, int distance, bool lock);


class BulletTypeClass;
class WarheadTypeClass;
class WeaponTypeClass;
class AnimClass;

// Two frame timers and four words (0x28 bytes; hypothesis: the bullet's
// arming/timing data). The default constructor is out of line elsewhere.
class UnknownBulletData {
public:
    void Initialize_004cee20(CoordStruct const &from, CoordStruct const &to, int arm, int max); // original this+A4, four stack arguments
    UnknownBulletData();                                // 0x004CEDF0
    UnknownBulletData(NoInitClass const &noinit) : unknown_00(0), unknown_0c(0) {}

    CDTimerClass<FrameTimerClass> unknown_00;   // +0x00
    CDTimerClass<FrameTimerClass> unknown_0c;   // +0x0C
    CoordStruct unknown_18;                     // +0x18 a coordinate (BulletClass 0x00461DE0 aims at it unless zero)
    int unknown_24;                             // +0x24
};

// A velocity vector of three doubles.
struct BulletVelocity {
    BulletVelocity &operator+=(BulletVelocity const &other); // 0x004642A0

    double X;       // +0x00
    double Y;       // +0x08
    double Z;       // +0x10
};

// Members of other classes that Bullet.cpp reads, as minimal views until
// their headers exist (offsets from this unit; names are hypotheses).
struct UnknownBulletTypeView {
    char unknown_000[0x271];
    bool unknown_271;                       // +0x271 (no facing frames?)
    char unknown_272[0x279 - 0x272];
    bool unknown_279;                       // +0x279 inherits the owner's color
    char unknown_27a[0x2AC - 0x27A];
    int unknown_2ac;                        // +0x2AC
    char unknown_2b0[0x2B4 - 0x2B0];
    int unknown_2b4;                        // +0x2B4
    char unknown_2b8[0x2BC - 0x2B8];
    bool unknown_2bc;                       // +0x2BC bullets of this type are kept in BulletClass::Array
    char unknown_2bd[0x2C4 - 0x2BD];
    bool unknown_2c4;                       // +0x2C4
    bool unknown_2c5;                       // +0x2C5
    unsigned char unknown_2c6;              // +0x2C6 initial animation rate
    bool unknown_2c7;                       // +0x2C7

    void Unknown_00465150(int value);       // 0x00465150 (sets +0x2B8)
};
struct UnknownHouseView {
    char unknown_00000[0x15F40];
    int unknown_15f40;                      // +0x15F40 (color scheme; hypothesis)
};
struct UnknownTechnoView {
    char unknown_000[0x1B4];
    UnknownHouseView *House;                // +0x1B4
};
inline UnknownBulletTypeView *Type_View(BulletTypeClass *type) { return (UnknownBulletTypeView *)type; }
inline UnknownTechnoView *Techno_View(TechnoClass *techno) { return (UnknownTechnoView *)techno; }

// The cell containing a coordinate, built with Cell's constructor
// (expanded out of line in Detach, 0x0042AD30; hypothesis for the header
// helper's form).
inline Cell Coord_Cell_Of(CoordStruct const &coord)
{
    return Cell(coord.X / 256, coord.Y / 256);
}

double __cdecl unknown_math_4ba600(double y, double x);  // 0x004BA600 (atan2-like; hypothesis)
// Fast_Sin / Fast_Cos (shared/fast_math.hpp) declared returning double, as
// shared/unknown_geometry.hpp declares their neighbours (BulletClass 0x00463C50).
double __cdecl unknown_sin_4ba480(double angle);    // 0x004BA480
double __cdecl unknown_cos_4ba4d0(double angle);    // 0x004BA4D0 (two names with fast_math.hpp's float Fast_Cos: carried)
// A 16-bit direction in a 4-byte value (hypothesis: Westwood's DirStruct).
struct UnknownDirStruct {
    UnknownDirStruct(unsigned short raw) : Raw(raw) {}
    unsigned short Raw;
    unsigned short Padding;
};
// The nearest of 32 facings.
inline int Dir_Facing32(UnknownDirStruct dir)
{
    return (((unsigned)dir.Raw >> 10) + 1 >> 1) & 0x1F;
}

// Shape frame of each of 32 facings (0x007ACAB0: 28, 27, ... 0, 31, 30, 29).
extern int unknown_facing_frames_7acab0[32];

extern "C" GUID const CLSID_BulletClass;    // 0x007A1C50

class BulletClass : public ObjectClass {
public:
    BulletClass();                                                      // 0x0045F3B0
    BulletClass(NoInitClass const &noinit) :                            // inline (Load)
        ObjectClass(noinit), Data(noinit) {}
    virtual ~BulletClass();                                             // 0x0045F590

    virtual unsigned long __stdcall AddRef();                           // 0x00463910 slot 1
    virtual unsigned long __stdcall Release();                          // 0x00463930 slot 2
    virtual HRESULT __stdcall GetClassID(GUID *clsid)                   // 0x00463EA0 slot 3 (inline)
    {
        if (clsid == 0) {
            return E_POINTER;
        }
        *clsid = CLSID_BulletClass;
        return S_OK;
    }
    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x004637B0 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x004638F0 slot 6
    virtual void Detach(AbstractClass *target, bool all = true);        // 0x00461520 slot 10
    virtual int Kind_Of() const { return 8; }                           // 0x00463E90 slot 11 (inline)
    virtual int Size_Of() const { return sizeof(BulletClass); }         // 0x00463E80 slot 12 (inline)
    virtual void AI();                                                  // 0x0045F710 slot 23
    virtual int unknown_slot29() const;                                 // 0x00461BF0 (layer)
    virtual ObjectTypeClass *Class_Of() const { return (ObjectTypeClass *)Type; }   // 0x00463EF0 slot 33 (inline)
    virtual Cell const *unknown_slot64(int arg1);                 // 0x0045F690
    virtual void unknown_slot67(int arg1, int arg2);                    // 0x004610D0
    virtual bool unknown_slot71(int arg1);                              // 0x0045F6F0
    virtual int unknown_slot116();                                      // 0x00461040 (new: shape frame)
    virtual void Set_Target(AbstractClass *target) { Target = target; } // 0x00463EE0 slot 117 (inline, new)
    virtual bool unknown_slot118(CoordStruct const &coord, BulletVelocity const &velocity);   // 0x004616B0 (new: place and launch; false if it cannot be placed)

    void Construct(BulletTypeClass *type, AbstractClass *target, TechnoClass *owner,
                   int damage, WarheadTypeClass *warhead, int speed, bool bright);   // 0x0045F4F0
    void unknown_func_461470();                                         // 0x00461470
    // Starts radiation at a cell, or adds to the site already there (no
    // callers: an out-of-line copy; YR names it ApplyRadiationToCell).
    void unknown_func_463720(Cell cell, int spread, int level);  // 0x00463720
    // Whether the bullet must explode where it is (coord receives its
    // position; hypothesis: Westwood's Is_Forced_To_Explode): blocked by
    // cliffs or walls on its path, below the ground, past a flak target's
    // height, on a Level cell that stops it, or near an air target.
    bool Is_Forced_To_Explode_00461c10(CoordStruct &coord);                       // 0x00461C10
    // Where the bullet detonates and the detonation itself (0x00461DE0;
    // hypothesis: Westwood's Detonate/explosion point): at its position, or
    // close targets' centres, then Cluster detonations (0x00462110) scattered
    // around it.
    void unknown_func_461de0(bool forced);                              // 0x00461DE0
    void unknown_func_462110(CoordStruct const &coord);                 // 0x00462110
    void Set_Weapon_Type(WeaponTypeClass *weapon);                      // 0x00463BA0
    WeaponTypeClass *Get_Weapon_Type();                                 // 0x00463BB0
    bool unknown_func_463970();                                         // 0x00463970
    void unknown_func_463bc0();                                         // 0x00463BC0
    void Draw_Voxel_00463a00(class UnknownObjectPair const &voxel, class Matrix3D const &matrix, struct Point2D const &point, class Rect const &window, unsigned frame, unsigned flags, int brightness); // observed ECX receiver/RET28
    void unknown_func_463c50();                                         // 0x00463C50 (drops a NukePayload on the target cell)

    static DynamicVectorClass<BulletClass *> Array;                     // 0x008502F8

    BulletTypeClass *Type;                  // +0x098
    TechnoClass *Owner;                     // +0x09C
    bool unknown_a0;                        // +0x0A0
    UnknownBulletData Data;                 // +0x0A4
    bool Bright;                            // +0x0CC
    BulletVelocity Velocity;                // +0x0D0
    int unknown_e8;                         // +0x0E8
    bool unknown_ec;                        // +0x0EC
    bool unknown_ed;                        // +0x0ED
    int unknown_f0;                         // +0x0F0
    AbstractClass *Target;                  // +0x0F4
    int Speed;                              // +0x0F8
    int InheritedColor;                     // +0x0FC
    int unknown_100;                        // +0x100
    int unknown_104;                        // +0x104
    double unknown_108;                     // +0x108
    WarheadTypeClass *WH;                   // +0x110
    unsigned char AnimFrame;                // +0x114
    unsigned char AnimRateCounter;          // +0x115
    WeaponTypeClass *WeaponType;            // +0x118
    CoordStruct SourceCoords;               // +0x11C
    CoordStruct TargetCoords;               // +0x128
    Cell LastMapCoords;               // +0x134
    int DamageMultiplier;                   // +0x138
    AnimClass *NextAnim;                    // +0x13C
    bool SpawnNextAnim;                     // +0x140
    int Range;                              // +0x144
};

// A new bullet as a COM object (CoCreateInstance of CLSID_BulletClass),
// then Construct; 0 when creation fails (name is a hypothesis).
BulletClass *__fastcall Create_Bullet(BulletTypeClass *type, AbstractClass *target, TechnoClass *owner,
                                      int damage, WarheadTypeClass *warhead, int speed, bool bright);   // 0x00463990

// Every bullet (0x00A40CE8; defined in the globals unit).
extern DynamicVectorClass<BulletClass *> unknown_BulletClass_list_00a40ce8;
// A list of objects with a pending next animation (0x00AC0BF8; hypothesis).

#endif
