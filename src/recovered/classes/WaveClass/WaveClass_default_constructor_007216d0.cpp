#include "shared/fast_math.hpp"
#include "shared/wave.hpp"
WaveClass::WaveClass() : Target(0), unknown_118(true), unknown_119(false), unknown_11c(100), unknown_120(0), unknown_128(0), Polygon_130(), Scanlines_168(), unknown_198(0), Owner(0), Cells(5)
{
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
}
