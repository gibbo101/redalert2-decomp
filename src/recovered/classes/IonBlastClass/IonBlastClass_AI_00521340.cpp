// IonBlastClass::AI() (0x00521340): one frame of an ion blast; the shock wave
// rocks every foot occupier within 128 screen pixels (Scout571).
#define VECTOR3_DECLARE_WWMATH
// @ref ?Point_To_Spiral_Index@@YIHUPoint2D@@@Z=005220c0
#include "shared/unknown_globals.hpp"
extern "C" int __cdecl abs(int);
#pragma intrinsic(abs)
extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
#include "shared/foot.hpp"
#include "shared/techno.hpp"
#include "shared/techno_type.hpp"
#include "shared/object_type.hpp"
#include "shared/unknown_pair_first.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
#include "shared/rules.hpp"
#include "shared/anim.hpp"
#include "shared/tactical.hpp"
#include "shared/facing.hpp"
#include "shared/vector3.hpp"
#include "shared/fast_math.hpp"
// @ref ?Fast_Sqrt@@YAMN@Z=004ba410
// @ref ?Fast_Sin@@YAMN@Z=004ba480
// @ref ?Fast_Cos@@YAMN@Z=004ba4d0
// @ref __real@8@3ff2d1b71758e2196800=007a4620
// @ref __real@8@3fefa7c5ac471b478800=007a4628
double __cdecl unknown_sin_4ba480(double angle);    // 0x004BA480
double __cdecl unknown_cos_4ba4d0(double angle);    // 0x004BA4D0
// @ref ?unknown_sin_4ba480@@YANN@Z=004ba480
// @ref ?unknown_cos_4ba4d0@@YANN@Z=004ba4d0
// @ref ?Delete@?$DynamicVectorClass@PAVIonBlastClass@@@@QAE_NH@Z=00522500
// @ref _WaveFrequency=007a45b0
// @ref _WaveAmplitudeFalloff=007a45b8
// @ref _WaveRockScale=007a45c0
// @ref _WavePhaseSpeed=00a51e18
// @ref __real@8@40049800000000000000=007a4618
// @ref __real@8@4000e000000000000000=007a4610
// @ref _unknown_geometry_j=00a51fa0
inline float Length552(Vector3 const &v) { return Fast_Sqrt((double)v.X * v.X + (double)v.Y * v.Y + (double)v.Z * v.Z); }
void IonBlastClass::AI()
{
    if (Lifetime >= 79) {
        delete this;
        return;
    }

    if (unknown_10 != 1) {
        Point2D point;
        unknown_tactical_83996c->Coord_To_Pixel(Coord, point);

        if (Lifetime == 0) {
            if (Map[Coord].unknown_ec == 2) {
                new AnimClass(Rules->SplashList[Rules->SplashList.Count() - 1], Coord + CoordStruct(0, 0, 5), 0, 1, 0x600, 0);
            } else {
                new AnimClass(Rules->IonBlast, Coord + CoordStruct(0, 0, 5), 0, 1, 0x600, 0);
            }
            new AnimClass(Rules->IonBeam, Coord + CoordStruct(0, 0, 5), 0, 1, 0x600, 0);

            if (Map[Coord].IsUnderBridge) {
                CoordStruct coord = CoordStruct(Coord.X, Coord.Y, unknown_geometry_j + Coord.Z);
                Unknown_0047E2C0(coord, Rules->IonCannonDamage, 0, Rules->IonCannonWarhead, 1);
            }

            Unknown_0047E2C0(Coord, Rules->IonCannonDamage, 0, Rules->IonCannonWarhead, 1);
            Unknown_0047F600(Coord, Rules->IonCannonDamage, Rules->IonCannonWarhead, 0, 0);
        }

        Cell center(Coord);

        for (int x_offset = -3; x_offset < 4; x_offset++) {
            for (int y_offset = -3; y_offset < 4; y_offset++) {
                CellClass &cell = Map[center + Cell(x_offset, y_offset)];
                ObjectClass *occupier = cell.OccupierPtr;

                while (occupier != 0) {
                    if (occupier->Kind_Of() == 0x0F || occupier->Kind_Of() == 1) {
                        FootClass *foot = (FootClass *)occupier;
                        Point2D occupier_point;
                        unknown_tactical_83996c->Coord_To_Pixel(occupier->Position_Coord_004f3f40(), occupier_point);

                        Point2D diff = occupier_point - point;
                        int screen_dist = (int)Fast_Sqrt((double)diff.Y * diff.Y + (double)diff.X * diff.X) + 8;

                        if (screen_dist < 128) {
                            char *displacement = (char *)BlastSurfaces[Lifetime]->Lock(Point2D(screen_dist + 128, 64));

                            if (*displacement > 0) {
                                foot->unknown_slot306(0.0);
                                int draw_offset = Spiral_Index_To_Point(*displacement).Y;
                                *(signed char *)&foot->unknown_59e = 2 * draw_offset;
                            }

                            UnknownPairFirst *voxel;
                            if (foot->unknown_slot32()->unknown_b0.unknown_00 != 0 && (voxel = foot->unknown_slot32()->unknown_b0.unknown_00, !voxel->unknown_00) && *displacement >= 0) {

                                CoordStruct blast_coord = Coord;
                                CoordStruct occupier_coord = occupier->Position_Coord_004f3f40();
                                Vector3 to_blast;
                                to_blast.X = (float)(blast_coord.X - occupier_coord.X);
                                to_blast.Y = (float)(occupier_coord.Y - blast_coord.Y);
                                to_blast.Z = (float)(blast_coord.Z - occupier_coord.Z);
                                Vector3 flat = to_blast;

                                double facing_rad = (double)((short)foot->unknown_2e0.Current().Raw - 0x3FFF) * -9.587672516830327e-05;
                                float facing_sin = (float)unknown_sin_4ba480(facing_rad);
                                Vector3 facing;
                                facing.X = (float)unknown_cos_4ba4d0(facing_rad);

                                float blast_dist = Fast_Sqrt((double)to_blast.X * to_blast.X + (double)to_blast.Y * to_blast.Y + (double)to_blast.Z * to_blast.Z);

                                if (fabs(blast_dist) > 0.00002) {
                                    flat.Z = 0.0;

                                    double flat_len = Fast_Sqrt(flat.X * flat.X + flat.Y * flat.Y);

                                    Vector3 normal;
                                    if (flat_len != 0.0) {
                                        normal = flat / flat_len;
                                    } else {
                                        normal = flat;
                                    }

                                    float forwards = normal.X * facing.X + normal.Y * facing_sin;
                                    float sideways = Length552(Vector3(-(normal.Z * facing_sin), normal.Z * facing.X, normal.X * facing_sin - normal.Y * facing.X));

                                    float c2 = facing.X;
                                    float s2 = facing_sin;
                                    float c3 = facing.X;
                                    float s3 = facing_sin;
                                    if (fabs(c2 * forwards - s2 * sideways - normal.X) > 0.0002
                                        || fabs(c3 * sideways + s3 * forwards - normal.Y) > 0.0002) {
                                        sideways = -sideways;
                                    }

                                    double decay = blast_dist + WaveAmplitudeFalloff;
                                    double height = (unknown_sin_4ba480((blast_dist - (double)Lifetime * WavePhaseSpeed + 38.0) * WaveFrequency) * 3.5 + 3.0) * WaveAmplitudeFalloff;
                                    double slope = ((unknown_cos_4ba4d0((blast_dist - (double)Lifetime * WavePhaseSpeed + 38.0) * WaveFrequency) * WaveFrequency * WaveAmplitudeFalloff * 3.5) * decay - height) / (decay * decay);

                                    foot->unknown_280 = (float)(sideways * slope * WaveRockScale);
                                    foot->unknown_284 = (float)(-(forwards * slope * WaveRockScale));
                                }
                            }
                        }
                    }
                    occupier = occupier->unknown_30;
                }
            }
        }
    }

    Lifetime++;
}
