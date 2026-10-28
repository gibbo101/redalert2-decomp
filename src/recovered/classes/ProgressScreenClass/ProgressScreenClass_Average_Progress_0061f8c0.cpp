// double ProgressScreenClass::Average_Progress() (0x0061F8C0)
// The players' mean progress as a fraction of the total.
#include "shared/progress_screen.hpp"

double ProgressScreenClass::Average_Progress()
{
    double sum = 0;
    int count = Count;
    for (int index = 0; index < count; index++) {
        sum += Progress[index];
    }
    return sum / count / Total;
}
