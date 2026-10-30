// The path estimator at 0x008315C8 (moved out of shared/foot.hpp so the map
// units can use it without the FootClass layout).
#ifndef RA2_SHARED_PATH_ESTIMATOR_HPP
#define RA2_SHARED_PATH_ESTIMATOR_HPP

#include "shared/coord.hpp"
#include "shared/rect.hpp"
#include "shared/vector_class.hpp"

class FootClass;
class ObjectClass;

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
};

// The two 0x10000-entry tables (the constructor builds them with new; 4 header bytes).
struct UnknownPathTable16 {
    struct Entry { int unknown_00, unknown_04, unknown_08, unknown_0c; };
    UnknownPathTable16()
    {
        for (int index = 0; index < 0x10000; index++) {
            entries[index].unknown_08 = 0;
            entries[index].unknown_04 = 0;
            entries[index].unknown_00 = 0;
        }
        entries[0xFFFF].unknown_0c = 0;
    }
    int unknown_00;
    Entry entries[0x10000];
};
struct UnknownPathTable24 {
    struct Entry { int unknown_00, unknown_04, unknown_08, unknown_0c, unknown_10, unknown_14; };
    UnknownPathTable24() { entries[0xFFFF].unknown_14 = 0; }
    int unknown_00;
    Entry entries[0x10000];
};

// Layout from the constructor 0x00427FB0 and the destructor 0x004281E0
// (size not established beyond +0xBC).
struct UnknownPathEstimator {
    UnknownPathEstimator();                 // 0x00427FB0
    ~UnknownPathEstimator();                // 0x004281E0
    // The length of a path between two cells for a unit (0x0042AA30; hypothesis).
    int Unknown_0042AA30(Cell const &from, Cell const &to, FootClass *foot, bool from_bridge, bool to_bridge, int arg6);
    // Resets the estimator (0x00429A90; MapClass 0x00563D40 after rebuilding the subzones).
    void Unknown_00429A90();
    // Sizes the estimator for the map rectangle (0x004284E0; MapClass 0x005499C0).
    void Unknown_004284E0(Rect const &size);
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
    UnknownPathTable24 *unknown_0c;         // +0x0C
    UnknownPathTable16 *unknown_10;         // +0x10
    UnknownPathEstimatorBlock *unknown_14;  // +0x14
    int *unknown_18;                        // +0x18
    int *unknown_1c;                        // +0x1C
    int *unknown_20;                        // +0x20
    int *unknown_24;                        // +0x24
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
    short unknown_70;                       // +0x70
    short unknown_72;                       // +0x72
    DynamicVectorClass<unsigned int> unknown_74[3];     // +0x74 (growth step 10)
    int unknown_bc[3][250];                 // +0xBC (cleared by the constructor)
    int unknown_c74[3];                     // +0xC74
};
extern UnknownPathEstimator unknown_path_estimator_8315c8;     // 0x008315C8
// The cell index offsets of the eight facings for a map of side unknown_map_cell_side_84e804 (0x0084C838).
extern int unknown_path_facing_offsets_84c838[8];
// The facing by (dy + 1, dx + 1); -1 at the centre (0x007CF100).
extern int unknown_path_facing_table_7cf100[3][3];

#endif
