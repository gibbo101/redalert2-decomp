// VeinholeMonsterClass: the veinhole monster and its veins (Veinhole.cpp,
// unit 0x0070F590-0x00712B2F; RTTI vtables 0x007AE7A0 primary, 0x007AE784
// IRTTITypeInfo at +4, 0x007AE77C INoticeSink, 0x007AE774 INoticeSource).
//
// Layout (constructors 0x0070F9B0 and 0x0070F820, destructor 0x0070FDF0, the list loops;
// names are hypotheses):
//   +0x98  int unknown_98
//   +0x9C  int *unknown_9c            heap block; the first word counts (0: dead)
//   +0xA0  void *unknown_a0           heap block
//   +0xA4  CDTimerClass unknown_a4    the rules' VeinholeGrowthRate (constructor 0x0070F9B0)
//   +0xB0  unsigned char *unknown_b0  per-cell bytes (rules +0xD4 * 8 at first)
//   +0xB8  int unknown_b8             state (slot 86 sets 2 or 3)
//   +0xBC  UnknownStage unknown_bc    (shared/stage.hpp; rate 4, step 0, value -1 once placed)
//   +0xD4  CDTimerClass unknown_d4
//   +0xE0  Cell Cell
//   +0xE4  int unknown_e4
//   +0xE8  bool unknown_e8
//   +0xEC  int unknown_ec             vein cells counted by 0x007115B0 / 0x00711AA0
//   size 0xF0 (Size_Of)
// Every monster is in VeinholeMonsterClass::Array (0x00AD0748), a static
// member defined in this unit.
#ifndef RA2_SHARED_VEINHOLE_HPP
#define RA2_SHARED_VEINHOLE_HPP

#include "shared/object.hpp"
#include "shared/cd_timer.hpp"
#include "shared/stage.hpp"
#include "shared/vein_heap.hpp"

extern "C" GUID const CLSID_VeinholeMonsterClass;      // 0x007A1EF0

// The isometric cell number of a cell (0x00428A90; the cell index used by
// per-cell tables; name hypothesis).
int __fastcall unknown_cell_index_428a90(Cell const &cell);

// The byte size of a per-cell table (0x00428AC0; (map width + 4) * height * 2; name hypothesis).
int __fastcall unknown_cells_428ac0();    // __fastcall: Load_All 0x00711E60 copies the result and sets the next Read's lea ecx before its pushes

// The veinhole buffers: a shared per-cell table (0x00AD07A0).
extern unsigned char *unknown_veinhole_buffer_ad07a0;

// Shape file retrieval by name: MixFileClass::Retrieve, shared/mix_file_class.hpp.

// The veinhole shape file (0x00AD079C), loaded for the theater.
extern void const *unknown_veinhole_shape_ad079c;

// The rules' vein node count per monster (RulesClass +0xD4).
inline int Rules_Vein_Node_Count()
{
    return Rules->unknown_d4;
}

// The vein nodes and their heap: shared/vein_heap.hpp.

class VeinholeMonsterClass : public ObjectClass {
public:
    VeinholeMonsterClass(::Cell const *cell);                       // 0x0070F9B0 (a monster at the cell when one may spawn there)
    VeinholeMonsterClass(NoInitClass const &noinit);                // 0x0070F820 (builds the heap and buffers; Load rebuilds objects with it)
#ifdef RA2_VEIN_GROWTH_LIFECYCLE
    static void __cdecl Clear_Global_Data();          // 00711C70
    static void __cdecl Deinit_Vein_Growth_System();  // 007114F0
#endif
    virtual ~VeinholeMonsterClass();                                // 0x0070FDF0

    static VeinholeMonsterClass *__fastcall Find_At(Cell const &cell);   // 0x00710160 (name hypothesis)
    static VeinholeMonsterClass *__fastcall Find_Covering(Cell const &cell);   // 0x007101B0 (the last monster whose +0xB0 table is set at the cell; name hypothesis)
    static void __cdecl All_AI();                                   // 0x007101F0 (AI, then deletes dead ones; near miss)
    static void __cdecl All_Draw();                                 // 0x00710820 (unknown_func_710880 on each)
    void unknown_func_710880();                                     // 0x00710880
    void unknown_func_710bb0();                                     // 0x00710BB0 (grows the vein network: takes 1-5 nodes off the heap)
    void unknown_func_710ff0();                                     // 0x00710FF0 (spreads the veins: takes 1-4 nodes off the heap)
    static void __fastcall unknown_func_711280(bool rebuild);      // 0x00711280 (rebuilds the shared table and, with rebuild, every monster's buffers)
    void unknown_func_7115b0();                                     // 0x007115B0 (marks an unplaced monster's vein cells)
    void unknown_func_711aa0();                                     // 0x00711AA0 (rebuilds a placed monster's node heap)
    void unknown_func_711c90();                                     // 0x00711C90 (frees the heap, nodes and table)
    void unknown_func_711d20();                                     // 0x00711D20 (clears the vein overlay around the hole)
    void unknown_func_712300(CellClass *cell);                      // 0x00712300
    static bool __fastcall Can_Spawn_At(Cell const &cell);       // 0x00710A60 (no monster within 3 cells and a flat 3x3 of equal level; name hypothesis)
    static void __fastcall Load_Shape(int theater);                 // 0x00710840 (VEINHOLE.<theater suffix>; name hypothesis)
    static bool __fastcall Save_All(IStream *stream);               // 0x00712150 (name hypothesis)
    static bool __fastcall Load_All(IStream *stream);              // 0x00711E60 (name hypothesis)
    static void __cdecl Clear_All();                                // 0x00710B50
    static void __cdecl Delete_Dead();                              // 0x00711E20 (near miss)

    virtual HRESULT __stdcall GetClassID(GUID *clsid);              // 0x007126C0 slot 3
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x007122D0 slot 6
    virtual int Kind_Of() const;                                    // 0x00712700 slot 11
    virtual int Size_Of() const;                                    // 0x00712710 slot 12
    virtual void AI();                                              // 0x00710250 slot 23
    virtual int unknown_slot29() const;                             // 0x00712720 (-1)
    virtual ObjectTypeClass *Class_Of() const;                      // 0x007122F0 slot 33
    virtual int unknown_slot86(int *damage, int distance, WarheadTypeClass *warhead, TechnoClass *source, bool forced, int arg6);  // 0x007109C0

    int unknown_98;                 // +0x98
    UnknownVeinHeap *unknown_9c;    // +0x9C
    UnknownVeinNode *unknown_a0;    // +0xA0
    CDTimerClass<FrameTimerClass> unknown_a4;   // +0xA4 (the rules' VeinholeGrowthRate)
    unsigned char *unknown_b0;      // +0xB0
    int unknown_b4;                 // +0xB4
    int unknown_b8;                 // +0xB8
    UnknownStage unknown_bc;        // +0xBC (rate 4, step 0, value -1 once placed)
    CDTimerClass<FrameTimerClass> unknown_d4;   // +0xD4 (set to 120 after damage)
    ::Cell Cell;                // +0xE0
    int unknown_e4;                 // +0xE4
    bool unknown_e8;                // +0xE8
    bool unknown_e9;                // +0xE9
    char unknown_ea[0xEC - 0xEA];
    int unknown_ec;                 // +0xEC (vein cells counted by 0x007115B0 / 0x00711AA0)

    static DynamicVectorClass<VeinholeMonsterClass *> Array;       // 0x00AD0748
};

#endif
