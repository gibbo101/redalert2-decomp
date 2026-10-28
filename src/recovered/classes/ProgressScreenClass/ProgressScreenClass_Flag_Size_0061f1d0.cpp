// void ProgressScreenClass::Flag_Size(int *width, int *height) (0x0061F1D0)
// The size of the first country's flag image (zero without one).
#include "shared/progress_screen.hpp"
#include "shared/surface.hpp"
// @ref ?Country_Flag_004d1120@@YIPAVSurface@@H@Z=004d1120

void ProgressScreenClass::Flag_Size(int *width, int *height)
{
    Surface *flag = Country_Flag_004d1120(0);
    if (flag == 0) {
        *width = 0;
        *height = 0;
        return;
    }
    *width = flag->Get_Width();
    *height = flag->Get_Height();
}
