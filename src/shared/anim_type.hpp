// AnimTypeClass: the INI-defined animation types (AnimType.cpp, members
// 0x00424E30-0x0042690F; RTTI vtables 0x0079C318 primary (41 slots),
// 0x0079C2EC IRTTITypeInfo at +4, 0x0079C310 INoticeSink, 0x0079C308
// INoticeSource).
//
// Layout (from the constructor 0x00424E30, Read_INI 0x00425690 whose INI
// keys name the members, Compute_CRC 0x00426300 and Load 0x00426140):
//   +0x000  ObjectTypeClass (0x264)
//   +0x264  int ArrayIndex        -1, then the index in AnimTypes (slot 16)
//   +0x268  int unknown_268       largest frame area (slot 40; hypothesis)
//   +0x26C  int unknown_26c (never initialized; /Zp4 would put a double here)
//   +0x270  double Damage
//   +0x278  int Rate              1; "Rate=" stores 900 / value
//   +0x27C  int Start, +0x280 LoopStart, +0x284 LoopEnd, +0x288 End,
//   +0x28C  int LoopCount
//   +0x290  AnimTypeClass *Next   (swizzled; cleared by Detach)
//   +0x294  int DetailLevel, +0x298 int TranslucencyDetailLevel
//   +0x29C  int RandomLoopDelay min / +0x2A0 max
//   +0x2A4  int RandomRate min / +0x2A8 max (900 / value)
//   +0x2AC  int Translucency
//   +0x2B0  AnimTypeClass *Spawns (swizzled), +0x2B4 int SpawnCount
//   +0x2B8  int StartSound (-1; "Report=" fallback), +0x2BC int StopSound (-1)
//   +0x2C0  AnimTypeClass *BounceAnim, +0x2C4 ExpireAnim, +0x2C8 TrailerAnim
//   +0x2CC  int TrailerSeperation
//   +0x2D0  double Elasticity (.8f), +0x2D8 double MinZVel (3.5),
//   +0x2E0  double unknown_2e0 (3.5, not read), +0x2E8 double MaxXYVel (15)
//   +0x2F0  WarheadTypeClass *Warhead (swizzled), +0x2F4 int DamageRadius
//   +0x2F8  OverlayTypeClass *TiberiumSpawnType (swizzled)
//   +0x2FC  int TiberiumSpreadRadius, +0x300 YSortAdjust, +0x304 YDrawOffset,
//   +0x308  int ZAdjust, +0x30C int RunningFrames
//   +0x310..+0x31E  bool flags, +0x320 int Layer (3), +0x324..+0x32F bools
//   size 0x330 (Size_Of; operator new in Find_Or_Make)
// Kind_Of, slot 16, Size_Of and slots 32/35 are inline (emitted at the end
// of AnimType.cpp, after its .cpp members).
// Every type is added to AnimTypes (0x008661E0) and to the list at
// 0x00AC0CB0 and removed from both when destroyed.
#ifndef RA2_SHARED_ANIM_TYPE_HPP
#define RA2_SHARED_ANIM_TYPE_HPP

#include "shared/warhead_type.hpp"
#include "shared/object_type.hpp"
#include "shared/type_list.hpp"

class AnimTypeClass;
class OverlayTypeClass;

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

// The theater whose images are loaded (0x007D88DC) and a flag that forces
// a reload (0x00A40D13); names hypotheses.
extern int unknown_loaded_theater_7d88dc;
extern bool unknown_a40d13;

extern "C" GUID const CLSID_AnimTypeClass;    // 0x007A1B90

void *__fastcall Load_Alloc_Data(class FileClass &file);            // 0x00495230
#include "shared/debug_printf.hpp"

#include "shared/voc_class.hpp"


#include "shared/overlay_type.hpp"

class AnimTypeClass : public ObjectTypeClass {
public:
    AnimTypeClass(char const *ini_name);                                // 0x00424E30
    AnimTypeClass(NoInitClass const &noinit);                           // 0x00425140
    virtual ~AnimTypeClass();                                           // 0x00425170

    static void __fastcall Init(int theater);                           // 0x00425230
    static char const *__fastcall Name_From(int index);                 // 0x00425620
    static int __fastcall From_Name(char const *name);                  // 0x00425640
    static AnimTypeClass *__fastcall Find_Or_Make(char const *name);    // 0x004264A0
    void unknown_func_426700();                                         // 0x00426700 (frees a demand-loaded image)

    virtual HRESULT __stdcall GetClassID(GUID *clsid);                  // 0x004262C0 slot 3
    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x00426140 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x004262A0 slot 6
    virtual void Detach(AbstractClass *target, bool all = true);        // 0x00426530 slot 10
    virtual int Kind_Of() const { return 5; }                           // 0x00426770 slot 11 (inline)
    virtual int Size_Of() const { return sizeof(AnimTypeClass); }       // 0x00426790 slot 12 (inline)
    virtual void Compute_CRC(WWCRCEngine &crc) const;                   // 0x00426300 slot 13
    virtual int unknown_slot16() const { return ArrayIndex; }           // 0x00426780 (inline)
    virtual void unknown_slot24(int theater);                           // 0x004253C0 (theater change)
    virtual bool Read_INI(CCINIClass &ini);                             // 0x00425690 slot 25
    virtual bool unknown_slot32(Cell const &cell, HouseClass *house) const { return false; }   // 0x004267A0 (inline)
    virtual ObjectClass *unknown_slot35(HouseClass *house) const { return 0; }   // 0x004267B0 (inline)
    virtual void *unknown_slot39() const;                               // 0x00426550 (demand-loads the image)
    virtual void unknown_slot40(int theater);                           // 0x00425490 (loads the image)

    int ArrayIndex;                         // +0x264
    int unknown_268;                        // +0x268
    int unknown_26c;                        // +0x26C (not set by the constructor)
    double Damage;                          // +0x270
    int Rate;                               // +0x278
    int Start;                              // +0x27C
    int LoopStart;                          // +0x280
    int LoopEnd;                            // +0x284
    int End;                                // +0x288
    int LoopCount;                          // +0x28C
    AnimTypeClass *Next;                    // +0x290
    int DetailLevel;                        // +0x294
    int TranslucencyDetailLevel;            // +0x298
    int RandomLoopDelayMin;                 // +0x29C ("RandomLoopDelay=" min,max)
    int RandomLoopDelayMax;                 // +0x2A0
    int RandomRateMin;                      // +0x2A4
    int RandomRateMax;                      // +0x2A8
    int Translucency;                       // +0x2AC
    AnimTypeClass *Spawns;                  // +0x2B0
    int SpawnCount;                         // +0x2B4
    int StartSound;                         // +0x2B8
    int StopSound;                          // +0x2BC
    AnimTypeClass *BounceAnim;              // +0x2C0
    AnimTypeClass *ExpireAnim;              // +0x2C4
    AnimTypeClass *TrailerAnim;             // +0x2C8
    int TrailerSeperation;                  // +0x2CC
    double Elasticity;                      // +0x2D0
    double MinZVel;                         // +0x2D8
    double unknown_2e0;                     // +0x2E0
    double MaxXYVel;                        // +0x2E8
    WarheadTypeClass *Warhead;              // +0x2F0
    int DamageRadius;                       // +0x2F4
    OverlayTypeClass *TiberiumSpawnType;    // +0x2F8
    int TiberiumSpreadRadius;               // +0x2FC
    int YSortAdjust;                        // +0x300
    int YDrawOffset;                        // +0x304
    int ZAdjust;                            // +0x308
    int RunningFrames;                      // +0x30C
    bool IsFlamingGuy;                      // +0x310
    bool IsVeins;                           // +0x311
    bool IsMeteor;                          // +0x312
    bool TiberiumChainReaction;             // +0x313
    bool IsTiberium;                        // +0x314
    bool HideIfNoOre;                       // +0x315
    bool Bouncer;                           // +0x316
    bool Tiled;                             // +0x317
    bool ShouldUseCellDrawer;               // +0x318
    bool UseNormalLight;                    // +0x319
    bool DemandLoad;                        // +0x31A
    bool FreeAfterPlaying;                  // +0x31B
    bool IsAnimatedTiberium;                // +0x31C
    bool AltPalette;                        // +0x31D
    bool Normalized;                        // +0x31E
    int Layer;                              // +0x320
    bool Flat;                              // +0x324
    bool Translucent;                       // +0x325
    bool Scorch;                            // +0x326
    bool Flamer;                            // +0x327
    bool Crater;                            // +0x328
    bool ForceBigCraters;                   // +0x329
    bool Sticky;                            // +0x32A
    bool PingPong;                          // +0x32B
    bool Reverse;                           // +0x32C
    bool Shadow;                            // +0x32D
    bool PsiWarning;                        // +0x32E
    bool ShouldFogRemove;                   // +0x32F
};

extern TypeList<AnimTypeClass *> AnimTypes;     // 0x008661E0

// The type with this ID in a list, else a new one (0x00426890; defined in
// AnimType.cpp; a template in the original is likely, since the copy sits
// with the unit's COMDATs, but VC6 expands every template instantiation
// here; name hypothesis).
AnimTypeClass *__fastcall Find_Or_Make_Type(char const *name, TypeList<AnimTypeClass *> &list);

#endif
