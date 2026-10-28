// The path estimator at 0x008315C8 (moved out of shared/foot.hpp so the map
// units can use it without the FootClass layout).
#ifndef RA2_SHARED_PATH_ESTIMATOR_HPP
#define RA2_SHARED_PATH_ESTIMATOR_HPP

#include "shared/coord.hpp"
#include "shared/rect.hpp"
#include "shared/vector_class.hpp"

class FootClass;

// A 0x14-byte block that owns an array at +0x08 (freed first); the
// constructor 0x00427FB0 builds two (+0x14 with 0x10000 entries, +0x68 with 0x2710).
struct UnknownPathEstimatorBlock {
    int unknown_00;                         // +0x00
    int unknown_04;                         // +0x04 (entry count)
    char *unknown_08;                       // +0x08 (the array)
    int unknown_0c;                         // +0x0C
    int unknown_10;                         // +0x10 (-1)
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

    bool unknown_00;                        // +0x00
    bool unknown_01;                        // +0x01
    bool unknown_02;                        // +0x02
    bool unknown_03;                        // +0x03 (true)
    float unknown_04;                       // +0x04 (1.0)
    bool unknown_08;                        // +0x08 (true)
    char *unknown_0c;                       // +0x0C
    char *unknown_10;                       // +0x10
    UnknownPathEstimatorBlock *unknown_14;  // +0x14
    char *unknown_18;                       // +0x18
    char *unknown_1c;                       // +0x1C
    char *unknown_20;                       // +0x20
    char *unknown_24;                       // +0x24
    int unknown_28;                         // +0x28 (-1)
    int unknown_2c;                         // +0x2C (-1)
    char unknown_30[8];                     // +0x30
    bool unknown_38;                        // +0x38 (true)
    int unknown_3c;                         // +0x3C
    char *unknown_40[3];                    // +0x40
    char *unknown_4c[3];                    // +0x4C
    char *unknown_58[3];                    // +0x58
    char *unknown_64;                       // +0x64
    UnknownPathEstimatorBlock *unknown_68;  // +0x68
    int unknown_6c;                         // +0x6C (-1)
    short unknown_70;                       // +0x70
    short unknown_72;                       // +0x72
    DynamicVectorClass<unsigned int> unknown_74[3];     // +0x74 (growth step 10)
};
extern UnknownPathEstimator unknown_path_estimator_8315c8;     // 0x008315C8

#endif
