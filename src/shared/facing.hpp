// Direction values and FacingClass: turning state shared by technos and locomotors.
#ifndef RA2_SHARED_FACING_HPP
#define RA2_SHARED_FACING_HPP
#include "shared/coord.hpp"
#include "shared/cd_timer.hpp"
#if defined(RA2_FACING_DIR256) || defined(RA2_SHIP_SOM)
#include "shared/dir_type.hpp"
#endif
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
#ifdef RA2_SHIP_SOM
    UnknownFacingDir(Dir256 dir) { From_Dir256(dir); }
    void From_Dir256(Dir256 dir) { Raw=0; Raw|=(dir<<8); }
    void From_Facing(int facing) { Raw=0; Raw |= facing << 13; }
    UnknownFacingDir(FacingType facing) { From_Facing(facing); }
    UnknownFacingDir operator-(UnknownFacingDir const &other) const { return UnknownFacingDir((unsigned short)((short)Raw-(short)other.Raw)); }
#endif
#ifdef RA2_FACING_DIR256
    UnknownFacingDir(Dir256 dir) { From_Dir256(dir); }
    void From_Dir256(Dir256 dir) { Raw=0; Raw|=(dir<<8); }
#endif
// The native Parasite AI observes a signed low-word angle, then rotates left by a quarter turn.
#ifdef RA2_FACING_LEFT90
    UnknownFacingDir(int facing) : Facing((short)facing) {}
    UnknownFacingDir Left_90() const { return UnknownFacingDir((int)Facing - 0x3fff); }
#endif
    UnknownFacingDir(CoordStruct const &from, CoordStruct const &to);   // 0x00423EF0 (the direction from one coordinate to another)
    // TibSun DirType::Direction: the same code as the constructor above (the
    // AnimClass unit calls it on a default-constructed direction and reads the
    // direction back through the returned reference).
    UnknownFacingDir &Direction(CoordStruct const &from, CoordStruct const &to);   // 0x00423EF0
    // Private source hypothesis for original signed-angle magnitude comparison.
    bool Magnitude_At_Least_004bfb30(UnknownFacingDir const &other) const;
#ifdef RA2_FACING_LEFT90
    union { unsigned short Raw; short Facing; };
#else
    unsigned short Raw;
#endif
    unsigned short Padding;
};
#ifdef RA2_FACING_DIR256
inline bool operator==(UnknownFacingDir const &left,UnknownFacingDir const &right) { return left.Raw==right.Raw; }
inline bool operator!=(UnknownFacingDir const &left,UnknownFacingDir const &right) { return left.Raw!=right.Raw; }
#endif

#ifdef RA2_SHIP_SOM
inline bool operator<(UnknownFacingDir const &left, UnknownFacingDir const &right) { return abs((short)left.Raw) < abs((short)right.Raw); }
#endif
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
