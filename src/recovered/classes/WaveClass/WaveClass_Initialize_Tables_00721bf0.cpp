#include "shared/wave.hpp"
#include "shared/fast_math.hpp"
extern bool Wave_Tables_Initialized_00b25554;
extern unsigned short Wave_Distance_Table_00af9620[300][300];
extern short Wave_Sine_Table_00af91e4[500];
extern int Wave_Intensity_Table_00af95d8[13];
// @ref ?Wave_Tables_Initialized_00b25554@@3_NA=00b25554
// @ref ?Wave_Distance_Table_00af9620@@3PAY0BCM@GA=00af9620
// @ref ?Wave_Sine_Table_00af91e4@@3PAFA=00af91e4
// @ref ?Wave_Intensity_Table_00af95d8@@3PAHA=00af95d8
// @ref __real@8@3ffdfae147ae147ae000=007a6050
// @ref __real@8@4002c000000000000000=007a5e18
// @ref __real@8@3ffc8000000000000000=007aec98
void __fastcall Initialize_Wave_Tables_00721bf0()
{
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
