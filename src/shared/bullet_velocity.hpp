#ifndef RA2_SHARED_BULLET_VELOCITY_HPP
#define RA2_SHARED_BULLET_VELOCITY_HPP
#ifndef RA2_BULLET_MISSILE_VELOCITY
#include "shared/bullet.hpp"
#else
#include "shared/dir_type.hpp"
#include "shared/fast_math.hpp"

// Same existing three-double BulletVelocity representation, using the Missile unit's direction view.
struct BulletVelocityXY {
    BulletVelocityXY() {}
    BulletVelocityXY(double x, double y) : X(x), Y(y) {}
    double Speed() const { return Fast_Sqrt(X * X + Y * Y); }
    void Nonzero_Check() { if (X == 0 && Y == 0) X = 100; }
    double X;
    double Y;
};
struct BulletVelocity : public BulletVelocityXY {
    BulletVelocity() {}
    BulletVelocity(BulletVelocity const &velocity) : BulletVelocityXY(velocity), Z(velocity.Z) {}
    BulletVelocity(double x, double y, double z) : BulletVelocityXY(BulletVelocityXY(x,y)), Z(z) {}
    BulletVelocity &operator+=(BulletVelocity const &other);
    BulletVelocityXY &XY() { return *this; }
    BulletVelocityXY const &XY() const { return *this; }
    double Horizontal_Speed() const { return Fast_Sqrt(X * X + Y * Y); }
    double Speed() const { return Fast_Sqrt(X * X + Y * Y + Z * Z); }
    void Nonzero_Check() { if (X == 0 && Y == 0 && Z == 0) X = 100; }
    DirType Get_Yaw() const { return Fast_Atan2(-Y, X); }
#ifdef RA2_BULLET_MISSILE_GET_PITCH_SOURCE
    DirType Get_Pitch() const;
#else
    DirType Get_Pitch() const { double const &horizontal = BulletVelocityXY::Speed(); return Fast_Atan2(Z, horizontal); }
#endif
    void Set_Yaw(DirType const &yaw)
    {
        BulletVelocityXY::Nonzero_Check();
        double horizontal_speed = Horizontal_Speed();
        X = horizontal_speed * Fast_Cos(yaw.As_Radian());
        Y = -horizontal_speed * Fast_Sin(yaw.As_Radian());
    }
#ifdef RA2_BULLET_MISSILE_SET_PITCH_SOURCE
    void Set_Pitch(DirType const &pitch);
#else
    void Set_Pitch(DirType const &pitch)
    {
        double current_pitch = Get_Pitch().As_Radian();
        double speed = Speed();
        if (current_pitch != 0) {
            X /= Fast_Cos(current_pitch);
            Y /= Fast_Cos(current_pitch);
        }
        X *= Fast_Cos(pitch.As_Radian());
        Y *= Fast_Cos(pitch.As_Radian());
        Z = speed * Fast_Sin(pitch.As_Radian());
    }
#endif
    void Set_Speed(double speed)
    {
        Nonzero_Check();
        double ratio = speed / Speed();
        X *= ratio;
        Y *= ratio;
        Z *= ratio;
    }
    double Z;
};

#endif
#endif
