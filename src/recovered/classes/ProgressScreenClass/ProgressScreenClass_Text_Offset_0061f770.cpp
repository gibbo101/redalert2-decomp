#include "shared/progress_screen.hpp"
int ProgressScreenClass::Text_Offset(bool flag)
{
    int width = 0, height = 0;
    Box_Size(&width, &height, 1, flag);
    int text_width = 0, text_height = 0;
    Text_Size(&text_width, &text_height);
    return (height - text_height) / 2;
}
