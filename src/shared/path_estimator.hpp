// The path estimator at 0x008315C8 (moved out of shared/foot.hpp so the map
// units can use it without the FootClass layout).
#ifndef RA2_SHARED_PATH_ESTIMATOR_HPP
#define RA2_SHARED_PATH_ESTIMATOR_HPP

#include "shared/coord.hpp"
#include "shared/rect.hpp"
#include "shared/vector_class.hpp"

class FootClass;
class ObjectClass;

// A node of the subzone search (16 bytes; the +0x64 pool holds 10000; Tiberian Sun's
// AStarHierarchicalNode).
struct UnknownPathHierNode {
    int ParentIndex;                        // +0x00 (the pool index of the parent, -1 at the start)
    int SubzoneID;                          // +0x04
    float Score;                            // +0x08
    int Depth;                              // +0x0C

    float Get_Score() const { return Score; }
};

// A 0x14-byte block that owns an array at +0x08 (freed first); the
// constructor 0x00427FB0 builds two (+0x14 with 0x10000 entries, +0x68 with 0x2710).
struct UnknownPathEstimatorBlock {
    int unknown_00;                         // +0x00 (highest entry in use; Clear zeroes up to it)
    int unknown_04;                         // +0x04 (last index)
    char *unknown_08;                       // +0x08 (the array)
    int unknown_0c;                         // +0x0C
    int unknown_10;                         // +0x10 (-1)

    UnknownPathEstimatorBlock(int max)
    {
        unknown_0c = 0;
        unknown_10 = -1;
        unknown_00 = 0;
        unknown_04 = max;
        unknown_08 = (char *)new int[max + 1];
        for (int index = 0; index <= unknown_04; index++) {
            ((int *)unknown_08)[index] = 0;
        }
    }
    void Clear()
    {
        for (int index = 0; index <= unknown_00; index++) {
            ((int *)unknown_08)[index] = 0;
        }
        unknown_00 = 0;
    }
    // The +0x68 block is the subzone search's priority queue (Tiberian Sun's PriorityQueueClass:
    // unknown_00 the count, unknown_04 the size, unknown_08 the heap from slot 1, unknown_0c/unknown_10
    // the highest and lowest node addresses queued).
    UnknownPathHierNode **Hier_Heap() const { return (UnknownPathHierNode **)unknown_08; }
    bool Insert(UnknownPathHierNode &node)
    {
        unsigned index = unknown_00 + 1;
        unsigned parent = index >> 1;
        float score = node.Score;
        if (index >= (unsigned)unknown_04) {
            return false;
        }
        while (index > 1) {
            if (Hier_Heap()[parent]->Score <= score) {
                break;
            }
            Hier_Heap()[index] = Hier_Heap()[parent];
            index = parent;
            parent = index >> 1;
        }
        Hier_Heap()[index] = &node;
        unknown_00++;
        if ((unsigned)&node > (unsigned)unknown_0c) {
            unknown_0c = (int)&node;
        }
        if ((unsigned)&node < (unsigned)unknown_10) {
            unknown_10 = (int)&node;
        }
        return true;
    }
    UnknownPathHierNode *Extract_Min()
    {
        if (unknown_00 == 0) {
            return 0;
        }
        UnknownPathHierNode *min = Hier_Heap()[1];
        Hier_Heap()[1] = Hier_Heap()[unknown_00];
        Hier_Heap()[unknown_00] = 0;
        unknown_00--;
        Heapify(1);
        return min;
    }
    // Out-of-line copy 0x0042B560.
    void Heapify(int index)
    {
        int left = index << 1;
        int right = (index << 1) + 1;
        int smallest = left <= unknown_00 && Hier_Heap()[left]->Get_Score() < Hier_Heap()[index]->Get_Score() ? left : index;
        smallest = right <= unknown_00 && Hier_Heap()[right]->Get_Score() < Hier_Heap()[smallest]->Get_Score() ? right : smallest;
        while (smallest != index) {
            UnknownPathHierNode *temp = Hier_Heap()[index];
            Hier_Heap()[index] = Hier_Heap()[smallest];
            Hier_Heap()[smallest] = temp;
            index = smallest;
            left = index << 1;
            right = (index << 1) + 1;
            smallest = left <= unknown_00 && Hier_Heap()[left]->Get_Score() < Hier_Heap()[index]->Get_Score() ? left : index;
            smallest = right <= unknown_00 && Hier_Heap()[right]->Get_Score() < Hier_Heap()[smallest]->Get_Score() ? right : smallest;
        }
    }
};

class CellClass;

// An entry of the +0x0C table (12 bytes; 0x00427D40 fills one per search node).
struct UnknownPathEntry {
    CellClass **unknown_00;                 // +0x00 (the cell; hypothesis: a slot of the map's cell array)
    int unknown_04;                         // +0x04 (the level; +4 on a bridge deck)
    UnknownPathEntry *unknown_08;           // +0x08 (the parent entry, or null)
};
// A search node of the +0x10 table (16 bytes).
struct UnknownPathNode {
    UnknownPathEntry *unknown_00;           // +0x00
    float unknown_04;                       // +0x04 (cost so far)
    float unknown_08;                       // +0x08 (cost so far plus the straight-line estimate)
    int unknown_0c;                         // +0x0C (depth; 1 at the start)
};
// The +0x0C table: 0x20000 entries then the count in use (+0x180000).
struct UnknownPathEntryTable {
    UnknownPathEntryTable() { count = 0; }
    UnknownPathEntry entries[0x20000];
    int count;                              // +0x180000
};
// The +0x10 table: 0x10000 nodes then the count in use (+0x100000).
struct UnknownPathNodeTable {
    UnknownPathNodeTable()
    {
        for (int index = 0; index < 0x10000; index++) {
            nodes[index].unknown_0c = 0;
            nodes[index].unknown_08 = 0;
            nodes[index].unknown_04 = 0;
        }
        count = 0;
    }
    UnknownPathNode nodes[0x10000];
    int count;                              // +0x100000
};

// The path a search returns (0x20 bytes; FootClass 0x004C3000 copies it whole to slot 305; hypothesis:
// Westwood's PathType). 0x00428370 fills a function-local static one; its destructor is empty (the
// static's atexit entry 0x004284D0 only returns).
struct UnknownPathType {
    ~UnknownPathType() {}
    Cell Start;                             // +0x00
    int Cost;                               // +0x04 (nonzero: a path was found)
    int Length;                             // +0x08 facings in the buffer
    int *Command;                           // +0x0C the facings (-1 after the last)
    int *Overlap;                           // +0x10 (null; names from Tiberian Sun's PathStruct)
    int *Height;                            // +0x14 the level of each step
    Cell LastOverlap;                       // +0x18
    Cell LastFixup;                         // +0x1C
};

// Layout from the constructor 0x00427FB0 and the destructor 0x004281E0
// (size not established beyond +0xBC).
struct UnknownPathEstimator {
    void Apply_Path_Collision_Avoidance_004285d0(FootClass *foot);
    // Runs hierarchical and regular searches, retrying blocked corridors (0x0042A1D0).
    UnknownPathType *Find_Path_0042a1d0(Cell const &from, Cell const &to, FootClass *foot, int *moves, int max_loops, int zone, int avoidance);
    // Searches the cells within the selected corridor (0x00427370).
    UnknownPathType *Find_Path_Regular_00427370(Cell const &from, Cell const &to, FootClass *foot, int *moves, int max_loops, bool with_hs);
    UnknownPathEstimator();                 // 0x00427FB0
    ~UnknownPathEstimator();                // 0x004281E0
    // Searches the subzone graph from one cell to another for a movement zone (0x00429B60; TS Find_Path_Hierarchical).
    bool Unknown_00429B60(Cell const &from, Cell const &to, int zone, FootClass *foot);
    // Writes the two-leg straight path from from to the cell offset to into moves when foot can walk it
    // (0x004296F0; TS Plot_Straight_Line).
    bool Unknown_004296F0(int *moves, int move_count, Cell const &from, Cell const &to, FootClass *foot, int level, bool fearless);
    // The length of a path between two cells for a unit (0x0042AA30; hypothesis).
    int Unknown_0042AA30(Cell const &from, Cell const &to, FootClass *foot, bool from_bridge, bool to_bridge, int arg6);
    // Resets the estimator (0x00429A90; MapClass 0x00563D40 after rebuilding the subzones).
    void Unknown_00429A90();
    // Sizes the estimator for the map rectangle (0x004284E0; MapClass 0x005499C0).
    void Unknown_004284E0(Rect const &size);
    // Takes the next node and entry for cell, reached from parent (null at the start) at step cost
    // (0x00427D40).
    UnknownPathNode *Unknown_00427D40(UnknownPathNode *parent, CellClass **cell, Cell const &target, float cost);
    // The path from the search's start to node, its facings written to buffer (0x00428370).
    UnknownPathType *Unknown_00428370(UnknownPathNode *node, int *buffer);
    // Walks facings back from index to stop (opposite facings, -2 skipped) and stops one step after the
    // walk, having moved away from its start, comes back: the index and cell there (stop and the walked
    // cell when it never does) (0x00429570).
    void Unknown_00429570(int const *facings, int index, int stop, int *out_index, Cell *cell);
    // Records the subzone pairs around the start cell +0x70 in each layer's +0x74 list (0x0042A590).
    void Unknown_0042A590(int arg);
    // (0x0042A840).
    void Unknown_0042A840(unsigned subzone, int layer);
#ifdef RA2_PATH_OPTIMIZE_MOVES
    // Replaces wandering runs of a found path by straight lines where foot can walk them, then packs out
    // the emptied moves (0x004290C0; TS Optimize_Moves).
    void Unknown_004290C0(UnknownPathType *path, FootClass *foot);
#endif
    // Straightens the path's corners where the diagonal is clear (0x00428AE0).
    void Unknown_00428AE0(UnknownPathType *path, FootClass *foot);
    // Replaces a corner of two legs from facings by a diagonal when it can; the facings consumed
    // (0x00428CF0).
    int Unknown_00428CF0(FootClass *foot, int *facings, int *heights, int first_length, int second_length, Cell &corner);
    // Starts a new search: empties both blocks and the table sentinels and bumps the generation +0x28
    // (clearing the marks when it wraps) (0x00427E90).
    void Unknown_00427E90();
    // Whether the cell index is marked in the current generation, in the +0x18 marks or the +0x1C ones
    // (0x00427F70; the first argument is unused).
    bool Unknown_00427F70(int unused, bool first, int index);
    // The cell one step from cell toward facing; facing 8 is the exit of the tube that starts at the cell
    // ((0,0) when none) (out-of-line copy 0x0042AD50).
    static Cell __fastcall Unknown_0042AD50(Cell const &cell, int facing);
    // The cell reached from start by count steps along the facings (0x00427060).
    static Cell __fastcall Unknown_00427060(Cell const &start, int count, int const *facings);
    // The moving object in the 5x5 cells around cell (the bridge occupiers when the cell is a bridge more
    // than two levels from level) whose locomotor is moving to the cell's centre at level's height, or
    // null (0x00428950; this is unused).
    ObjectClass *Unknown_00428950(Cell const &cell, int level);
    // The facing from one cell to an adjacent one (8 when not adjacent) (0x00428320).
    static int __fastcall Unknown_00428320(Cell const &from, Cell const &to);
    // Whether the subzone pair is recorded in layer's +0x74 list (0x0042A770).
    bool Unknown_0042A770(unsigned short first, unsigned short second, int layer);
    // Records the subzone pair (smaller one in the high word) in layer's +0x74 list (0x0042A7D0).
    void Unknown_0042A7D0(unsigned first, unsigned second, int layer);

    bool unknown_00;                        // +0x00
    bool unknown_01;                        // +0x01
    bool unknown_02;                        // +0x02
    bool unknown_03;                        // +0x03 (true)
    float unknown_04;                       // +0x04 (1.0)
    bool unknown_08;                        // +0x08 (true)
    UnknownPathEntryTable *unknown_0c;      // +0x0C
    UnknownPathNodeTable *unknown_10;       // +0x10
    UnknownPathEstimatorBlock *unknown_14;  // +0x14
    int *unknown_18;                        // +0x18
    int *unknown_1c;                        // +0x1C
    float *unknown_20;                        // +0x20
    float *unknown_24;                        // +0x24
    int unknown_28;                         // +0x28 (-1)
    int unknown_2c;                         // +0x2C (-1)
    char unknown_30[8];                     // +0x30
    bool unknown_38;                        // +0x38 (true)
    int unknown_3c;                         // +0x3C
    int *unknown_40[3];                     // +0x40 (Map.unknown_70[layer] entries each)
    int *unknown_4c[3];                     // +0x4C (Map.unknown_70[layer] entries each)
    int *unknown_58[3];                     // +0x58 (Map.unknown_70[layer] entries each)
    char *unknown_64;                       // +0x64
    UnknownPathEstimatorBlock *unknown_68;  // +0x68
    int unknown_6c;                         // +0x6C (-1)
    Cell unknown_70;                        // +0x70 (the search start; hypothesis)
    DynamicVectorClass<unsigned int> unknown_74[3];     // +0x74 (growth step 10)
    unsigned short unknown_bc[3][500];      // +0xBC a subzone path per layer (cleared by the constructor)
    int unknown_c74[3];                     // +0xC74 the subzones in each +0xBC path
};
extern UnknownPathEstimator unknown_path_estimator_8315c8;     // 0x008315C8
// The cell index offsets of the eight facings for a map of side unknown_map_cell_side_84e804 (0x0084C838).
extern int unknown_path_facing_offsets_84c838[8];
// The level of each step of the path 0x00428370 returns (0x0084C858; size unknown).
extern int unknown_path_levels_84c858[];
// The facing by (dy + 1, dx + 1); -1 at the centre (0x007CF100).
extern int unknown_path_facing_table_7cf100[3][3];

#endif
