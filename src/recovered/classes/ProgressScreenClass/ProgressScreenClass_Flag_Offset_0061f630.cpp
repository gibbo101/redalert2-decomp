#include "shared/progress_screen.hpp"
int ProgressScreenClass::Flag_Offset(bool flag)
{
    int width = 0, height = 0;
    Box_Size(&width, &height, 1, flag);
    int flag_width = 0, flag_height = 0;
    Flag_Size(&flag_width, &flag_height);
    return (height - flag_height) / 2;
}
