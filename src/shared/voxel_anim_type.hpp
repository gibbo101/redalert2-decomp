// VoxelAnimTypeClass: the INI-defined voxel animation types
// (VoxelAnimType.cpp, members 0x0070E1A0-0x0070EFBF; RTTI vtables 0x007AE640
// primary (40 slots), 0x007AE624 IRTTITypeInfo at +4, 0x007AE61C
// INoticeSink, 0x007AE614 INoticeSource).
//
// Layout (from the constructor 0x0070E1A0, Read_INI 0x0070E470 whose INI
// keys name the members, Compute_CRC 0x0070EAB0 and Load 0x0070EC30):
//   +0x000  ObjectTypeClass (0x264)
//   +0x264  bool Normalized, +0x265 bool Translucent, +0x266 bool
//           unknown_266 (Share*Data: the voxel pair at +0xB0 is borrowed
//           from "ShareSource" and not freed by the destructor)
//   +0x268  int VoxelIndex, +0x26C int Duration (30)
//   +0x270  double Elasticity (.8f), +0x278 MinAngularVelocity (0),
//   +0x280  MaxAngularVelocity (10 degrees with pi = 3.1415), +0x288 MinZVel (3.5),
//   +0x290  MaxZVel (5), +0x298 MaxXYVel (15)
//   +0x2A0  bool IsMeteor
//   +0x2A4  VoxelAnimTypeClass *Spawns, +0x2A8 int SpawnCount
//   +0x2AC  int StartSound (-1), +0x2B0 int StopSound (-1)
//   +0x2B4  AnimTypeClass *BounceAnim, +0x2B8 ExpireAnim, +0x2BC TrailerAnim
//   +0x2C0  int Damage, +0x2C4 int DamageRadius
//   +0x2C8  WarheadTypeClass *Warhead, +0x2CC ParticleSystemTypeClass *AttachedSystem
//   +0x2D0  bool IsTiberium, +0x2D4 int unknown_2d4 (not initialized)
//   size 0x2D8
// Every type is in the list at 0x00AC0CB0 and in the list at 0x00A40AE0.
#ifndef RA2_SHARED_VOXEL_ANIM_TYPE_HPP
#define RA2_SHARED_VOXEL_ANIM_TYPE_HPP

#include "shared/object_type.hpp"
#include "shared/type_list.hpp"

class AnimTypeClass;
class WarheadTypeClass;
class ParticleSystemTypeClass;
class VoxelAnimTypeClass;

extern "C" GUID const CLSID_VoxelAnimTypeClass;   // 0x007A1D00

class VoxelAnimTypeClass : public ObjectTypeClass {
public:
    VoxelAnimTypeClass(char const *ini_name);                           // 0x0070E1A0
    VoxelAnimTypeClass(NoInitClass const &noinit) : ObjectTypeClass(noinit) {}   // inline (Load)
    virtual ~VoxelAnimTypeClass();                                      // 0x0070E390

#ifdef VOXEL_ANIM_TYPE_DECLARE_NAME_FROM
    // 0070EA40: the ID at an unsigned index; original rejects only index > Count.
    static char const *__fastcall Name_From(unsigned index);
#endif
    static int __fastcall From_Name(char const *name);                  // 0x0070EA60
    static VoxelAnimTypeClass *__fastcall Find_Or_Make(char const *name);   // 0x0070ED80

    virtual HRESULT __stdcall GetClassID(GUID *clsid);                  // 0x0070EBF0 slot 3
    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x0070EC30 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x0070ECF0 slot 6
    virtual void Detach(AbstractClass *target, bool all = true);        // 0x0070ED10 slot 10
    virtual int Kind_Of() const { return 0x2A; }                        // 0x0070EE10 slot 11 (inline)
    virtual int Size_Of() const { return sizeof(VoxelAnimTypeClass); }  // 0x0070EE20 slot 12 (inline)
    virtual void Compute_CRC(WWCRCEngine &crc) const;                   // 0x0070EAB0 slot 13
    virtual bool Read_INI(CCINIClass &ini);                             // 0x0070E470 slot 25
    virtual bool unknown_slot32(Cell const &cell, HouseClass *house) const { return false; }   // 0x0070EE30 (inline)
    virtual ObjectClass *unknown_slot35(HouseClass *house) const { return 0; }   // 0x0070EE40 (inline)

    bool Normalized;                        // +0x264
    bool Translucent;                       // +0x265
    bool unknown_266;                       // +0x266
    int VoxelIndex;                         // +0x268
    int Duration;                           // +0x26C
    double Elasticity;                      // +0x270
    double MinAngularVelocity;              // +0x278
    double MaxAngularVelocity;              // +0x280
    double MinZVel;                         // +0x288
    double MaxZVel;                         // +0x290
    double MaxXYVel;                        // +0x298
    bool IsMeteor;                          // +0x2A0
    VoxelAnimTypeClass *Spawns;             // +0x2A4
    int SpawnCount;                         // +0x2A8
    int StartSound;                         // +0x2AC
    int StopSound;                          // +0x2B0
    AnimTypeClass *BounceAnim;              // +0x2B4
    AnimTypeClass *ExpireAnim;              // +0x2B8
    AnimTypeClass *TrailerAnim;             // +0x2BC
    int Damage;                             // +0x2C0
    int DamageRadius;                       // +0x2C4
    WarheadTypeClass *Warhead;              // +0x2C8
    ParticleSystemTypeClass *AttachedSystem;    // +0x2CC
    bool IsTiberium;                        // +0x2D0
    int unknown_2d4;                        // +0x2D4
};

// The list of voxel animation types (0x00A40AE0; defined by the unit at 0x004D2BA0).
extern DynamicVectorClass<VoxelAnimTypeClass *> VoxelAnimTypes;

// The type with this ID in a list, else a new one; null for "<none>" and
// "none" (0x0070EF40, __fastcall with the list in EDX; the same lookup as
// AnimType.cpp's 0x00426890, likely one template in the original).
VoxelAnimTypeClass *__fastcall Find_Or_Make_Type(char const *name, DynamicVectorClass<VoxelAnimTypeClass *> &list);

#endif
