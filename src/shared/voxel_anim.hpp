// VoxelAnimClass: a voxel animation (debris and the like) on the map
// (VoxelAnim.cpp, members 0x0070C800-0x0070DFAE; RTTI vtables 0x007AE428
// primary (116 slots), 0x007AE40C IRTTITypeInfo at +4, 0x007AE404
// INoticeSink, 0x007AE3FC INoticeSource).
//
// Layout (from the constructors 0x0070C800 and 0x0070CD20, the destructor
// 0x0070CE40, Load 0x0070DDB0 and Compute_CRC 0x0070DE70; names are
// hypotheses):
//   +0x000  ObjectClass (0x98)
//   +0x098  BounceClass base (0x50; original RTTI)
//   +0x0E8  int unknown_e8 (-1)
//   +0x0EC  VoxelAnimTypeClass *Class (swizzled; Class_Of returns it)
//   +0x0F0  ObjectClass *unknown_f0 (swizzled; ended by the destructor)
//   +0x0F4  HouseClass *unknown_f4 (swizzled; the constructor's third argument)
//   +0x0F8  bool unknown_f8
//   +0x0FC, +0x110  UnknownAudioController
//   +0x124  bool unknown_124, +0x128 int unknown_128 (the type's +0x26C),
//   +0x12C  int unknown_12c
//   size 0x130
// Every voxel animation is in the list at 0x008399D0.
#ifndef RA2_SHARED_VOXEL_ANIM_HPP
#define RA2_SHARED_VOXEL_ANIM_HPP

#include "shared/unknown_globals.hpp"
#include "shared/object_type.hpp"
#include "shared/bounce.hpp"
#include "shared/voxel_anim_type.hpp"

class VoxelAnimTypeClass;

extern "C" GUID const CLSID_VoxelAnimClass;   // 0x007A1BC0

// A flag (0x00A40958; also shared/ms_message_box.hpp): only while it is set
// does the destructor take the object off the map (slot 52).

class VoxelAnimClass : public ObjectClass, public BounceClass {
public:
    using ObjectClass::Coord;
    VoxelAnimClass();                                                   // 0x0070CD20
    VoxelAnimClass(VoxelAnimTypeClass *type, CoordStruct const &coord, HouseClass *house);   // 0x0070C800
    VoxelAnimClass(NoInitClass const &noinit) : ObjectClass(noinit), BounceClass(noinit) {}   // inline (Load)
    virtual ~VoxelAnimClass();                                          // 0x0070CE40

    virtual HRESULT __stdcall GetClassID(GUID *clsid)                   // 0x0070DF10 slot 3 (inline)
    {
        if (clsid == 0) {
            return E_POINTER;
        }
        *clsid = CLSID_VoxelAnimClass;
        return S_OK;
    }
    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x0070DDB0 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x0070DE50 slot 6
    virtual int Kind_Of() const { return 0x29; }                        // 0x0070DF60 slot 11 (inline)
    virtual int Size_Of() const { return sizeof(VoxelAnimClass); }      // 0x0070DF50 slot 12 (inline)
    virtual void Compute_CRC(WWCRCEngine &crc) const;                   // 0x0070DE70 slot 13
    virtual int unknown_slot29() const;                                 // 0x0070DDA0 (3)
    virtual ObjectTypeClass *Class_Of() const { return Class; }         // 0x0070DF70 slot 33 (inline)
    virtual Cell const *unknown_slot64(int arg1) { return 0; }    // 0x0070DF80 (inline)
    virtual bool unknown_slot63(Rect *bounds, bool arg2, bool arg3);    // 0x0070CF70
    virtual void AI();                                                  // 0x0070D380 slot 23
    static void __cdecl Clear_All();                                    // 0x0070D350 (deletes every voxel animation; name hypothesis)

    int unknown_e8;                             // +0x0E8
    VoxelAnimTypeClass *Class;                  // +0x0EC
    ObjectClass *unknown_f0;                    // +0x0F0
    HouseClass *unknown_f4;                    // +0x0F4
    bool unknown_f8;                            // +0x0F8
    UnknownAudioController unknown_fc;          // +0x0FC
    UnknownAudioController unknown_110;         // +0x110
    bool unknown_124;                           // +0x124
    int unknown_128;                            // +0x128
    int unknown_12c;                            // +0x12C
};

// The list of voxel animations (0x008399D0; defined by the unit at 0x0040EA30).
extern DynamicVectorClass<VoxelAnimClass *> unknown_VoxelAnimClass_list_008399d0;

#endif
