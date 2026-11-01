// void __fastcall Make_Wakes_00606E10(FootClass *victim, CoordStruct coord) (0x00606E10)
// Three wake animations at random spots around coord (up to 180 leptons
// along and 64 across the victim's facing).
#include "shared/foot.hpp"
#include "shared/anim.hpp"
#include "shared/rules.hpp"
#include "shared/id_source.hpp"
#include "shared/parasite.hpp"
// @ref ?unknown_facing_radians_79b620@@3NB=0079b620
// @ref ?unknown_sin_4ba480@@YANN@Z=004ba480
// @ref ?unknown_cos_4ba4d0@@YANN@Z=004ba4d0

extern double const unknown_facing_radians_79b620;
double __cdecl unknown_sin_4ba480(double angle);
double __cdecl unknown_cos_4ba4d0(double angle);

inline double UnknownFacingDir::As_Radian() const
{
    return (short(Raw)-0x3fff)*unknown_facing_radians_79b620;
}

void __fastcall Make_Wakes_00606E10(FootClass *victim, CoordStruct coord)
{
    double angle = -victim->unknown_2e0.Current().As_Radian();
    double cosine = unknown_cos_4ba4d0(angle);
    double sine = unknown_sin_4ba480(angle);
    for (int i = 0; i < 3; i++) {
        double along = unknown_id_source_a3d290->Random()(-180, 180);
        double across = unknown_id_source_a3d290->Random()(-64, 64);
        CoordStruct spot = coord + CoordStruct((int)(along * cosine - across * sine), (int)(along * sine + across * cosine), 0);
        new AnimClass(Rules->unknown_09c, spot, 0, 1, 0x600, 0);
    }
}
