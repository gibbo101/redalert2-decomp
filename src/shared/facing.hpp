// Direction values and FacingClass: turning state shared by technos and locomotors.
#ifndef RA2_SHARED_FACING_HPP
#define RA2_SHARED_FACING_HPP
#include "shared/coord.hpp"
#include "shared/cd_timer.hpp"
// A 16-bit direction in a 4-byte value (hypothesis: Westwood's DirStruct;
// cf. UnknownDirStruct in shared/bullet.hpp).
enum Dir32 {}; // The reference's wrapped 32-direction index type.
struct UnknownFacingDir {
    unsigned Round_To_32() const;
    Dir32 As_Dir32() const;
    double As_Radian32() const;
    void From_Radian(double angle); // original inline angle conversion
    double As_Radian() const; // original signed16 angle observation
    UnknownFacingDir() {}
    UnknownFacingDir(unsigned short raw) : Raw(raw) {}
    UnknownFacingDir(CoordStruct const &from, CoordStruct const &to);   // 0x00423EF0 (the direction from one coordinate to another)
    // Private source hypothesis for original signed-angle magnitude comparison.
    bool Magnitude_At_Least_004bfb30(UnknownFacingDir const &other) const;
    unsigned short Raw;
    unsigned short Padding;
};

// One of eight directions (the top bits of a direction, rounded; read as
// 32 bits).
inline int Dir_To_8(UnknownFacingDir const &dir)
{
    return (((*(unsigned const *)&dir >> 12) + 1) >> 1) & 7;
}

// The direction of an 8-way facing, and a direction as one of 256 (read as
// 32 bits).
inline UnknownFacingDir Facing_Dir(int facing)
{
    return UnknownFacingDir((unsigned short)(facing << 13));
}
inline int Dir_To_256(UnknownFacingDir const &dir)
{
    return (((*(unsigned const *)&dir >> 7) + 1) >> 1) & 0xFF;
}
// A direction as one of 32 (BuildingClass slot 183; read as 32 bits).
inline int Dir_To_32(UnknownFacingDir const &dir)
{
    return (((*(unsigned const *)&dir >> 10) + 1) >> 1) & 0x1F;
}


class FacingClass {
public:
    FacingClass();                      // 0x004B89D0
    FacingClass(int rate);              // 0x004B89F0
    FacingClass(NoInitClass const &noinit) : Timer(noinit) {}
    bool Set_Desired(UnknownFacingDir const &dir);  // 0x004B8A30 (name hypothesis)
    UnknownFacingDir unknown_4b8c80() const;    // 0x004B8C80 (the direction being turned toward; hypothesis)
    UnknownFacingDir Current() const;   // 0x004B8BE0 (name hypothesis: the direction now, part way through a turn)
    UnknownFacingDir Difference_To_Desired() const; // 0x004B8D40
    UnknownFacingDir Difference(UnknownFacingDir const &dir) const; // 0x004B8DE0
    bool Set_Current(UnknownFacingDir const &dir);  // 0x004B8B10 (name hypothesis)
    bool Is_Rotating() const;           // 0x004B8C90 (name hypothesis)
    char Is_Turning_Positive() const; // 0x004B8CC0
    char Is_Turning_Negative() const; // 0x004B8D00
    void Set_ROT(int rate);             // 0x004B8E90 (name hypothesis; BuildingClass::Init passes the type ROT)
    short Desired;                      // +0x00
    short unknown_02;
    short Start;                        // +0x04
    short unknown_06;
    CDTimerClass<FrameTimerClass> Timer;    // +0x08
    short ROT;                          // +0x14
};

#endif
