// BounceClass (name hypothesis): the bouncing-motion state of AnimClass
// (+0x108) and VoxelAnimClass (+0x98); 0x50 bytes. The constructors clear
// three doubles at +0x00, +0x08, +0x10 and build two 4-float values
// (0, 0, 0, 1) at +0x30 and +0x40 with the out-of-line 0x00622160.
#ifndef RA2_SHARED_BOUNCE_HPP
#define RA2_SHARED_BOUNCE_HPP

#include "shared/vector3.hpp"
#include "shared/coord.hpp"
#include "shared/matrix3d.hpp"

class NoInitClass;
#include "shared/coord.hpp"

// Four floats (hypothesis: a quaternion, built as 0, 0, 0, 1).
struct UnknownQuaternion {
    UnknownQuaternion(float x, float y, float z, float w);   // 0x00622160
    UnknownQuaternion(NoInitClass const &noinit) {}
    float X;
    float Y;
    float Z;
    float W;
};

// Builds the rotation matrix of a quaternion (0x00622EB0, quat.cpp;
// __fastcall with the result in ecx; name hypothesis).
Matrix3D __fastcall unknown_quaternion_matrix_622eb0(UnknownQuaternion const &quat);

// The first 0x30 bytes (AnimClass's UnknownBounce): three doubles cleared
// by the constructor (VC6 stores the three low words, then the three high
// words; six int members cleared in order do not schedule the same).
struct UnknownBounce {
    UnknownBounce() : unknown_00(0), unknown_08(0), unknown_10(0) {}
    UnknownBounce(NoInitClass const &noinit) {}
    double unknown_00;
    double unknown_08;
    double unknown_10;
    Vector3 Position;                       // +0x18 (Coord 0x00436F80 converts it)
    int unknown_24[2];
    float unknown_2c;                       // +0x2C (a meteor adds unknown_08 every step)

    int Unknown_004370E0();                 // 0x004370E0 one step: 1 bounced, 2 came to rest (AnimClass slot 116)
    CoordStruct Unknown_00436F80() const;   // 0x00436F80 the current position
};

#ifdef RA2_BOUNCE_DECLARE_MEMBERS
#include "shared/quaternion.hpp"

// What one BounceClass::AI step did (TibSun bounce.h).
enum BounceResultType {
    BOUNCE_MOVING,
    BOUNCE_IMPACT,
    BOUNCE_SETTLED
};

double __cdecl unknown_sin_4ba480(double angle);    // 0x004BA480
double __cdecl unknown_cos_4ba4d0(double angle);    // 0x004BA4D0
// The slope matrix of a ramp (0x00718D60) and the matrix that bounces toward
// a facing (0x00719010): both fill and return matrix.
Matrix3D * __fastcall Unknown_00718D60(Matrix3D *matrix, int ramp);
Matrix3D * __fastcall Unknown_00719010(Matrix3D *matrix, int index);
#endif

class BounceClass {
public:
    BounceClass() : unknown_30(0, 0, 0, 1.0f), unknown_40(0, 0, 0, 1.0f) {}
    BounceClass(NoInitClass const &noinit) : unknown_00(noinit), unknown_30(noinit), unknown_40(noinit) {}

    CoordStruct Coord() const;              // 0x00436F80 (the position, truncated)
    Matrix3D unknown_matrix_436fc0() const; // 0x00436FC0 (the rotation at +0x30 as a matrix)

#ifdef RA2_BOUNCE_DECLARE_MEMBERS
    // The BounceClass unit (TibSun bounce.cpp, 0x00436C70-0x0043768F). The
    // layout is TibSun's: Elasticity +0x00, Gravity +0x08, MaxVelocity +0x10
    // (unknown_00's three doubles), MyCoord +0x18 (unknown_00.Position),
    // Velocity +0x24 (a Vector3 over unknown_24/unknown_2c), Rotation +0x30
    // and AngularVelocity +0x40 (Quaternions).
    // Launches in a random direction at a speed from [min_speed, max_speed] (0x00436C70; no callers).
    void Init(CoordStruct const &coord, double elasticity, double, double min_speed, double max_speed);
    // Launches with the given velocity and a random tumble axis (0x00436DC0; AnimClass, VoxelAnimClass).
    void Init(CoordStruct const &coord, double elasticity, double gravity, double max_velocity,
              Vector3 const &velocity, double rotation);
    double Get_Remaining_Motion() const;    // 0x00436FF0
    BounceResultType AI();                  // 0x004370E0 (BOUNCE_IMPACT 1, BOUNCE_SETTLED 2)

#endif

    UnknownBounce unknown_00;               // +0x00
    UnknownQuaternion unknown_30;           // +0x30
    UnknownQuaternion unknown_40;           // +0x40
};

#endif
