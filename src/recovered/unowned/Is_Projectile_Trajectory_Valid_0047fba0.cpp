// bool __fastcall Is_Projectile_Trajectory_Valid(int speed, int distance, int height, double gravity) -- 0x0047FBA0
// TibSun combat.cpp: whether either ballistic solution is non-negative.
#include "shared/weapon_type.hpp"
#include "shared/facing.hpp"
#include "shared/rules.hpp"
#include "shared/fast_math.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/combat.hpp"

bool __fastcall Is_Projectile_Trajectory_Valid(int speed, int distance, int height, double gravity)
{
    double v = (double)speed;
    double dx = (double)distance;
    if (dx == 0.0) dx = 0.001;
    double dy = (double)height;

    double y2 = dy * dy;
    double vsq = v * v;
    double g2 = gravity * gravity;
    double x2 = dx * dx;

    double discriminant = (v * v * vsq) - (2 * vsq * dy * gravity) - (g2 * x2);

    if (discriminant < 0.0) {
        return false;
    }

    double denominator = 2 * ((y2 / x2) + 1.0);
    if (denominator == 0.0) {
        return false;
    }

    double base = vsq - (dy * gravity);

    if (((base + unknown_sqrt_4ba410(discriminant)) / denominator) >= 0.0 ||
        ((base - unknown_sqrt_4ba410(discriminant)) / denominator) >= 0.0) {
        return true;
    }
    return false;
}
// @ref __real@8@00000000000000000000=0079b610
// @ref __real@8@3ff583126e978d4fe000=0079c528
// @ref ?unknown_sqrt_4ba410@@YANN@Z=004ba410
// @ref __real@8@3fff8000000000000000=0079a708
