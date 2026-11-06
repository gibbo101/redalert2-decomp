// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 ra2-decomp contributors
// Copyright 2025 Electronic Arts Inc.; 2026 OpenTS contributors
// Derived from Electronic Arts source code; EA's GPL Section 7 terms apply (COPYING.md).
// void EBolt::Draw_Bolt_004B1900(CoordStruct start, CoordStruct end, int color) (0x004B1900): from
// ra2-decomp EBolt::FUN_004C1F20 (YR 0x004C1F20), adapted to our names. Splits the bolt into three
// jittered strands by repeated midpoint displacement (an explicit stack of eight segments) and draws
// each finished piece with Draw_Line_004B1850, the main strand in colour 15.
// @ref ?unknown_random_839218@@3VRandom2Class@@A=00839218
// @ref ??0CoordStruct@@QAE@XZ=004b25e0
// @ref ??0UnknownVector3@@QAE@HHH@Z=0041b630
// @ref __real@8@4000c90fdaa22168c000=0079d158
// @ref ?unknown_drawer_8323c4@@3PAVConvertClass@@A=008323c4
// @ref ?unknown_surface_839964@@3PAVSurface@@A=00839964
// @ref ?unknown_rect_839630@@3VRect@@A=00839630
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ?Unknown_006A2970@@YIHH@Z=006a2970
// @ref ?Coord_To_Pixel@Tactical@@QAE_NABUCoordStruct@@AAUPoint2D@@@Z=006a29d0
// @ref ??_H@YGXPAXIHP6EX0@Z@Z=0040aed0
#include "shared/ebolt.hpp"
#include "shared/tactical.hpp"
#include "shared/convert.hpp"
#include "shared/surface.hpp"
#include "shared/fast_math.hpp"
#include "shared/random2.hpp"
#include "shared/crt_memory.hpp"
#include "shared/unknown_vector3.hpp"
extern ConvertClass *unknown_drawer_8323c4;
extern Surface *unknown_surface_839964;
extern Rect unknown_rect_839630;
extern Random2Class unknown_random_839218;
int __fastcall Unknown_006A2970(int height);

// One pending piece of the bolt: the three strands' ends and the subdivision state.
struct BoltSegment {
    CoordStruct Start[3];
    CoordStruct End[3];
    int Length;
    int Deviation;
    int StartDepth;
    int EndDepth;
};

// The length of a lepton vector through the fast square root, summed y, z, x (as TPoint3D::Length_YZX).
static inline int Length_YZX(UnknownVector3 const &vector)
{
    double y = vector.Y;
    double z = vector.Z;
    double x = vector.X;
    return (int)Fast_Sqrt(y * y + (z * z + x * x));
}

void EBolt::Draw_Bolt_004B1900(CoordStruct start, CoordStruct end, int color)
{
    BoltSegment stack[8];
    CoordStruct mids[3];
    CoordStruct starts[3];
    CoordStruct ends[3];
    int offsets[6];
    bool first = true;
    int depth = 0;

    UnknownVector3 delta = UnknownVector3(start.X - end.X, start.Y - end.Y, start.Z - end.Z);
    int length = Length_YZX(delta);
    if (length != 0) {
        int threshold = (length * 102) >> 8;
        int deviation = (length * 23) >> 8;
        int start_z = unknown_18;
        BoltSegment *seg = stack;
        int end_z = 0;
        for (int i = 0; i < 3; i++) {
            starts[i] = start;
            ends[i] = end;
        }

        for (;;) {
            if (length > 64 && depth < 8) {
                for (int j = 0; j < 3; j++) {
                    mids[j].X = (starts[j].X + ends[j].X) >> 1;
                    mids[j].Y = (starts[j].Y + ends[j].Y) >> 1;
                    mids[j].Z = (starts[j].Z + ends[j].Z) >> 1;
                }
                if (first) {
                    first = false;
                    double dev = deviation;
                    for (int k = 0; k < 6; k++) {
                        offsets[k] = Fast_Sin(unknown_1c * 3.141592653589793 / (k + 7)) * dev;
                    }
                    int zoff = (offsets[2] + offsets[4] + deviation * 2) >> 1;
                    for (int m = 0; m < 3; m++) {
                        mids[m].X += offsets[0] + offsets[3];
                        mids[m].Y += offsets[1] + offsets[5];
                        mids[m].Z += zoff;
                    }
                }
                if (length <= 128) {
                    mids[0].X += unknown_random_839218(-1, 1) * deviation * 2;
                    mids[0].Y += unknown_random_839218(-1, 1) * deviation * 2;
                    mids[0].Z += unknown_random_839218(-1, 1) * deviation * 2;
                } else {
                    mids[0].X += unknown_random_839218(-deviation, deviation);
                    mids[0].Y += unknown_random_839218(-deviation, deviation);
                    mids[0].Z += unknown_random_839218(-deviation, deviation);
                }
                if (length > threshold) {
                    for (int n = 1; n < 3; n++) {
                        mids[n].X = mids[0].X + (unknown_random_839218(-deviation, deviation) >> 1);
                        mids[n].Y = mids[0].Y + (unknown_random_839218(-deviation, deviation) >> 1);
                        mids[n].Z = mids[0].Z + (unknown_random_839218(-deviation, deviation) >> 1);
                    }
                } else {
                    for (int n2 = 1; n2 < 3; n2++) {
                        mids[n2].X += unknown_random_839218(-deviation, deviation);
                        mids[n2].Y += unknown_random_839218(-deviation, deviation);
                        mids[n2].Z += unknown_random_839218(-deviation, deviation);
                    }
                }
                length >>= 1;
                deviation >>= 1;
                int mid_z = (end_z + start_z) >> 1;
                for (int p = 0; p < 3; p++) {
                    seg->Start[p] = mids[p];
                    seg->End[p] = ends[p];
                }
                seg->Length = length;
                seg->Deviation = deviation;
                seg->StartDepth = mid_z;
                seg->EndDepth = end_z;
                seg++;
                depth++;
                memcpy(ends, mids, sizeof(ends));
                end_z = mid_z;
            } else {
                Draw_Line_004B1850(starts[1], ends[1], color, start_z, end_z);
                Draw_Line_004B1850(starts[2], ends[2], color, start_z, end_z);
                Draw_Line_004B1850(starts[0], ends[0], 15, start_z, end_z);
                if (--depth < 0) break;
                seg--;
                memcpy(ends, seg->End, sizeof(ends));
                memcpy(starts, seg->Start, sizeof(starts));
                length = seg->Length;
                deviation = seg->Deviation;
                start_z = seg->StartDepth;
                end_z = seg->EndDepth;
            }
        }
    }
}
