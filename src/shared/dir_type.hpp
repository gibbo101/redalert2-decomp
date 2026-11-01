// FacingType and DirType: an eight-way facing and a 16-bit direction (TibSun face.h shape: a
// short Facing overlaid on an int Raw, so copies move four bytes; hypotheses).
#ifndef RA2_SHARED_DIR_TYPE_HPP
#define RA2_SHARED_DIR_TYPE_HPP

enum FacingType {
    FACING_NONE = -1,
    FACING_N,
    FACING_NE,
    FACING_E,
    FACING_SE,
    FACING_S,
    FACING_SW,
    FACING_W,
    FACING_NW,
    FACING_COUNT
};

enum Dir256 { DIR_MIN=0, DIR_MAX=255 };

class DirType {
public:
    DirType() {}
    DirType(int dir) { Facing = dir; }
    DirType(FacingType dir) { From_Facing(dir); }
    DirType(Dir256 dir) { From_Dir256(dir); }
    void From_Dir256(Dir256 dir) { Facing=0; Facing|=(dir<<8); }
    DirType const &Snap_To_256() { Facing &= 0xFF00; return *this; }

    void From_Facing(FacingType dir)
    {
        Facing = 0;
        Facing |= (dir << 13);
    }

    unsigned int Round_To_256() const { return ((((unsigned int)Raw >> 7) + 1) >> 1); }
    int As_Dir256() const { return (int)(Round_To_256() % 256); }
    DirType const &Snap_To_8() { Facing &= 0xE000; return *this; }
    int As_Int() const { return Facing; }

    union {
        short Facing;
        int Raw;
    };
};

#endif
