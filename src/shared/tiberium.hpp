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

// A spread or growth candidate: a cell and its priority (8 bytes; TS's MapSurfaceData).
struct MapSurfaceData {
    MapSurfaceData() {}
    Cell Position;      // +0x00
    float Score;        // +0x04
};

// A binary heap of entry pointers ordered by Score, lowest first (TS/YR's
// PriorityQueueClass): Nodes[1..Count]; LMost and RMost are the highest and
// lowest entry addresses inserted (bounds of the entry array in use).
template <class T>
class PriorityQueueClass {
public:
    PriorityQueueClass(int size) : LMost(0), RMost((T *)-1)
    {
        Count = 0;
        Size = size;
        Nodes = new T *[size + 1];
        for (int index = 0; index <= Size; index++) {
            Nodes[index] = 0;
        }
    }
    ~PriorityQueueClass() { delete[] Nodes; }
    // Adds node, sifting it up past the entries with a higher score; false when full.
    bool Insert(T *node)
    {
        unsigned index = Count + 1;
        unsigned parent = index >> 1;
        float score = node->Score;
        if (index >= (unsigned)Size) {
            return false;
        }
        while (index > 1 && Nodes[parent]->Score > score) {
            Nodes[index] = Nodes[parent];
            index = parent;
            parent >>= 1;
        }
        Nodes[index] = node;
        Count++;
        if (node > LMost) {
            LMost = node;
        }
        if (node < RMost) {
            RMost = node;
        }
        return true;
    }
    void Clear()
    {
        for (int index = 0; index <= Count; index++) {
            Nodes[index] = 0;
        }
        Count = 0;
    }

    int Count;          // +0x00
    int Size;           // +0x04
    T **Nodes;          // +0x08
    T *LMost;           // +0x0C
    T *RMost;           // +0x10
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
    TiberiumClass(NoInitClass const &noinit) : AbstractTypeClass(noinit), SpreadTimer(0), GrowthTimer(0) {}
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

    // The spread and growth queues (names hypotheses after TS's Tiberium.cpp).
    // Each type whose timer ran out spreads (growths) once and restarts its timer at its Spread
    // (Growth) rate; only while the scenario allows it (+0x222A).
    static void Spread_AI();                                    // 0x006E9490
    static void Growth_AI();                                    // 0x006E9F20
    void Process_Spread();                                      // 0x006E9720
    void Process_Growth();                                      // 0x006EA1E0
    static void Init_Spread();                                  // 0x006E9520 (all types, the current map)
    void Init_Spread_Queue();                                   // 0x006E9A50 (this type)
    void Init_Growth_Queue();                                   // 0x006EA540 (this type)
    void Rebuild_Spread();                                      // 0x006E9B90 (queues every cell of this type)
    static void Init_Growth();                                  // 0x006E9FE0
    void Rebuild_Growth();                                      // 0x006EA680
    // Queue one cell (the cell code calls these when ore appears or changes).
    void Add_Spread_Cell(Cell const &cell);                     // 0x006E9DD0
    void Add_Growth_Cell(Cell const &cell);                     // 0x006EA880
    static void __fastcall Clear_Spread_Cell(Cell const &cell); // 0x006E9D90 (in every type)

    // Fields merged with build/class-work/Cell/shared/tiberium.hpp's view
    // (ArrayIndex, Value, Image, NumFrames, NumImages; names hypotheses).
    int ArrayIndex;                                 // +0x098
    int Spread;                                     // +0x09C frames between spreads
    double unknown_a0;                              // +0x0A0 [SpreadPercentage] (0.1)
    int Growth;                                     // +0x0A8 frames between growths
    int unknown_ac;                                 // +0x0AC
    double unknown_b0;                              // +0x0B0 [GrowthPercentage] (0.1)
    int Value;                                      // +0x0B8 (credits per stage; hypothesis)
    int Power;                                      // +0x0BC
    int unknown_c0;                                 // +0x0C0 [Color] (a colour scheme index)
    TypeList<AnimTypeClass *> Debris;               // +0x0C4 (vtable 0x007A3B3C)
    OverlayTypeClass *Image;                        // +0x0E0
    int unknown_e4;                                 // +0x0E4
    int NumFrames;                                  // +0x0E8
    int NumImages;                                  // +0x0EC
    int SpreadCount;                                // +0x0F0 SpreadData entries in use
    PriorityQueueClass<MapSurfaceData> *SpreadQueue;   // +0x0F4
    bool *SpreadMap;                                // +0x0F8 per cell: queued for spread
    MapSurfaceData *SpreadData;                     // +0x0FC
    CDTimerClass<FrameTimerClass> SpreadTimer;      // +0x100
    int GrowthCount;                                // +0x10C GrowthData entries in use
    PriorityQueueClass<MapSurfaceData> *GrowthQueue;   // +0x110
    bool *GrowthMap;                                // +0x114 per cell: queued for growth
    MapSurfaceData *GrowthData;                     // +0x118
    CDTimerClass<FrameTimerClass> GrowthTimer;      // +0x11C
};

#endif
