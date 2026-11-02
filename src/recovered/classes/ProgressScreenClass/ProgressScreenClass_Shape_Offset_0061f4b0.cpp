#include "shared/progress_screen.hpp"
#include "shared/shape_file.hpp"
int ProgressScreenClass::Shape_Offset(bool flag)
{
    int width = 0, height = 0;
    Box_Size(&width, &height, 1, flag);
    Rect frame = Shape->Get_Frame_Rect(0);
    return (height - 6 - frame.Height) / 2;
}
