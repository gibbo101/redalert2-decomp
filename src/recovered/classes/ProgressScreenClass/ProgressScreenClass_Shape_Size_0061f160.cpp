// void ProgressScreenClass::Shape_Size(int *width, int *height) (0x0061F160)
// The size of the shape's first frame plus a 6-pixel border.
#include "shared/progress_screen.hpp"
#include "shared/shape_file.hpp"

void ProgressScreenClass::Shape_Size(int *width, int *height)
{
    Rect rect = Shape->Get_Frame_Rect(0);
    *width = rect.Width + 6;
    *height = rect.Height + 6;
}
