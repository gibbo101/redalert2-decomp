// void WaveClass::Wave_Recalc_Affected_Cells() (0x00723360)
// Rebuilds the list of cells the wave covers (TibSun Wave_Recalc_Affected_Cells): unknown_a0/unknown_ac are
// TibSun's StartCoord/EndCoord, unknown_118 IsWaveActive, unknown_120/unknown_128 WaveProgress/FadeProgress,
// unknown_194 the direction. The unit sees CoordStruct::As_Cell and the Cell comparisons (RA2_COORD_AS_CELL,
// defined by the unit's first draft); their out-of-line copies are 0x00413770 and 0x0058DB50, and the budget
// runs out exactly where the original's does (the middle cell test calls them; the right edge also calls Lerp).
#include "shared/wave.hpp"
#include "shared/cell.hpp"
#include "shared/unknown_geometry.hpp"

extern float const Wave_Advance_Step_007aec88;
// @ref ?Wave_Advance_Step_007aec88@@3MB=007aec88
// @ref ?As_Cell@CoordStruct@@QBE?AVCell@@XZ=00413770
// @ref ??9Cell@@QBE_NABV0@@Z=0058db50
// @ref ??0Cell@@QAE@HH@Z=0042ad30
// @ref ??0UnknownCoord434820@@QAE@HHH@Z=00434820
// @ref ?Add@?$DynamicVectorClass@PAVCellClass@@@@QAE_NABQAVCellClass@@@Z=00724730

void WaveClass::Wave_Recalc_Affected_Cells()
{
    Cells.Clear();

    if (unknown_118) {
        Cell start = unknown_a0.As_Cell();

        for (double t = Wave_Advance_Step_007aec88; t <= ((Wave_Advance_Step_007aec88 / 2.0) + unknown_120); t += Wave_Advance_Step_007aec88) {
            CoordStruct coord = Lerp(unknown_a0, unknown_ac, t);
            if (start != coord.As_Cell()) {
                start = coord.As_Cell();
                unknown_func_722040(start);
            }
        }
    } else {
        Cell left = WaveEndLeftCoord.As_Cell();
        Cell right = WaveEndRightCoord.As_Cell();
        Cell middle = unknown_ac.As_Cell();

        for (double t = unknown_128; t <= ((Wave_Advance_Step_007aec88 / 2.0) + unknown_120); t += Wave_Advance_Step_007aec88) {
            CoordStruct coord = unknown_geometry_l;

            if (unknown_194 < 4) {
                coord = Lerp(WaveStartLeftCoord, WaveEndLeftCoord, t);
                if (left != coord.As_Cell()) {
                    left = coord.As_Cell();
                    unknown_func_722040(left);
                }
            }

            coord = Lerp(unknown_a0, unknown_ac, t);
            if (middle != coord.As_Cell()) {
                middle = coord.As_Cell();
                unknown_func_722040(middle);
            }

            if (unknown_194 >= 4) {
                coord = Lerp(WaveStartRightCoord, WaveEndRightCoord, t);
                if (right != coord.As_Cell()) {
                    right = coord.As_Cell();
                    unknown_func_722040(right);
                }
            }
        }
    }
}
