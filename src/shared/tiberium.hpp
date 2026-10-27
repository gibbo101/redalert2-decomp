// TiberiumClass: an ore/gem type (Tiberium.cpp, 0x006E8920-0x006EAA0D;
// RTTI vtables 0x007AD8B0 primary, 0x007AD894 at +4, 0x007AD88C,
// 0x007AD884). Only the fields the recovered members use are named: a list
// of cells/objects at +0xC4 (saved by Save, pruned by Detach) and a pointer at
// +0xE0 (Image). Kind_Of 0x2E.
#ifndef RA2_SHARED_TIBERIUM_HPP
#define RA2_SHARED_TIBERIUM_HPP

#include "shared/abstract_type.hpp"
#include "shared/cd_timer.hpp"
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#include "shared/type_list.hpp"

class AnimTypeClass;

// The growth/spread queues (hypothesis: a priority queue): Count, Size,
// then the node array that Clear zeroes (entries 0..Count) and the
// destructor frees.
struct TiberiumQueue {
    ~TiberiumQueue() { delete[] Nodes; }
    void Clear()
    {
        for (int index = 0; index <= Count; index++) {
            Nodes[index] = 0;
        }
        Count = 0;
    }
    int Count;          // +0x00
    int Size;           // +0x04
    void **Nodes;       // +0x08
};

class TiberiumClass;
extern DynamicVectorClass<TiberiumClass *> unknown_TiberiumClass_list_00ac0b30;   // 0x00AC0B30
extern DynamicVectorClass<AbstractClass *> unknown_objects_ac0cb0;                 // 0x00AC0CB0
void __fastcall Detach_This_From_All(AbstractClass *object, bool all);             // 0x006ECB90

#ifndef E_POINTER
#define E_POINTER ((HRESULT)0x80004003L)
#endif

extern "C" GUID const CLSID_TiberiumClass;     // 0x007A1E60

class OverlayTypeClass;

class TiberiumClass : public AbstractTypeClass {
public:
    TiberiumClass(char const *ini_name);                        // 0x006E89A0
    TiberiumClass(NoInitClass const &noinit) : AbstractTypeClass(noinit), unknown_100(0), unknown_11c(0) {}
    virtual ~TiberiumClass();                                   // 0x006E8B60

    static bool __fastcall Read_Types(CCINIClass &ini);         // 0x006E8FF0 (the [Tiberiums] list; name hypothesis)

    virtual HRESULT __stdcall GetClassID(GUID *classid);        // 0x006E9120
    virtual HRESULT __stdcall Load(IStream *stream);            // 0x006E9160
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x006E93B0
    virtual HRESULT __stdcall GetSizeMax(ULARGE_INTEGER *size); // 0x006E9380
    virtual void Detach(AbstractClass *target, bool all);       // 0x006E9420
    virtual void Compute_CRC(WWCRCEngine &crc) const;           // 0x006E90A0 slot 13
    virtual int unknown_slot16() const;                         // 0x006EA9E0
    virtual bool Read_INI(CCINIClass &ini);                     // 0x006E8D30 slot 25
    virtual int Kind_Of() const;                                // 0x006EA9D0
    virtual int Size_Of() const;                                // 0x006EA9C0

    // Fields merged with build/class-work/Cell/shared/tiberium.hpp's view
    // (ArrayIndex, Value, Image, NumFrames, NumImages; names hypotheses).
    int ArrayIndex;                                 // +0x098
    int unknown_9c;                                 // +0x09C
    double unknown_a0;                              // +0x0A0 (0.1)
    int unknown_a8;                                 // +0x0A8
    int unknown_ac;                                 // +0x0AC
    double unknown_b0;                              // +0x0B0 (0.1)
    int Value;                                      // +0x0B8 (credits per stage; hypothesis)
    int unknown_bc;                                 // +0x0BC
    int unknown_c0;                                 // +0x0C0
    TypeList<AnimTypeClass *> unknown_c4;           // +0x0C4 (vtable 0x007A3B3C)
    OverlayTypeClass *Image;                        // +0x0E0
    int unknown_e4;                                 // +0x0E4
    int NumFrames;                                  // +0x0E8
    int NumImages;                                  // +0x0EC
    int unknown_f0;                                 // +0x0F0
    TiberiumQueue *unknown_f4;                      // +0x0F4
    void *unknown_f8;                               // +0x0F8
    void *unknown_fc;                               // +0x0FC
    CDTimerClass<FrameTimerClass> unknown_100;      // +0x100
    int unknown_10c;                                // +0x10C
    TiberiumQueue *unknown_110;                     // +0x110
    void *unknown_114;                              // +0x114
    void *unknown_118;                              // +0x118
    CDTimerClass<FrameTimerClass> unknown_11c;      // +0x11C
};

#endif
