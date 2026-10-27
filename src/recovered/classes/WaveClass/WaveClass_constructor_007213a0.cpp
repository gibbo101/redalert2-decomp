// Original DynamicVector<CellClass*> vtable slots 0 and 5 (007A5EFC).
// @ref ??_G?$DynamicVectorClass@PAVCellClass@@@@UAEPAXI@Z=0058ede0
// @ref ?ID@?$DynamicVectorClass@PAVCellClass@@@@UAEHPBQAVCellClass@@@Z=0058de40
// @ref ??_7?$DynamicVectorClass@PAVCellClass@@@@6B@=007a5efc
#include "shared/fast_math.hpp"
#include "shared/wave.hpp"
int __fastcall Wave_Direction_00721db0(Point2D const &start, Point2D const &end);
// @ref ?Wave_Direction_00721db0@@YIHABUPoint2D@@0@Z=00721db0
// @ref ?unknown_func_7238b0@WaveClass@@QAEXABUCoordStruct@@0@Z=007238b0
// @ref ?Update_Wave_00724200@WaveClass@@QAEXXZ=00724200
WaveClass::WaveClass(CoordStruct const &start, CoordStruct const &end, TechnoClass *owner, int type, ObjectClass *target) : Target(target), Type(type), unknown_118(true), unknown_119(false), unknown_11c(100), unknown_120(0), unknown_128(0), Polygon_130(), Scanlines_168(), unknown_198(0), Owner(owner), Cells(5)
{
    if (start == end) { ObjectClass::unknown_slot60(); return; }
    AbstractClass::Create_ID();
    Waves.Add(this);
    if (!Wave_Tables_Initialized_00b25554) {
    Wave_Tables_Initialized_00b25554 = true;
    int y = 0;
    unsigned short *row = &Wave_Distance_Table_00af9620[0][0];
    do {
        unsigned short *distance = row;
        int x = 0;
        do {
            *distance = (unsigned short)(int)Fast_Sqrt((double)(x * x + y * y));
            ++x;
            ++distance;
        } while (x < 300);
        row = distance;
        ++y;
    } while ((int)row < (int)&Wave_Distance_Table_00af9620[300][0]);
    for (int angle = 0; angle < 500; ++angle)
        Wave_Sine_Table_00af91e4[angle] = (short)(int)(Fast_Sin((double)angle * 0.125) * 12.0 + 0.49);
    int *intensity = Wave_Intensity_Table_00af95d8;
    for (int value = 110; value < 214; value += 8) *intensity++ = value;
    }
    unknown_func_7238b0(start, end);
    Scanlines_168.Spans = 0;
    unknown_194 = Wave_Direction_00721db0(unknown_b8, unknown_d0);
    WaveClass::unknown_slot53(&unknown_a0, 0);
    if (Type > 0 && Type <= 2) {
        unknown_120 = 1.0;
        unknown_198 = 160;
        Polygon_130.Points[0] = unknown_c8;
        Polygon_130.Points[1] = unknown_c0;
        Polygon_130.Points[2] = unknown_d0;
    }
    Update_Wave_00724200();
}
