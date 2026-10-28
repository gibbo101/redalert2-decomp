// void ProgressScreenClass::Load_Shape(char const *filename, void const *image, int unknown) (0x0061EF40)
// Replaces the background shape; draws the image when there is one.
#include "shared/progress_screen.hpp"
// @ref ?Unknown_00515A80@@YIXPBX_N@Z=00515a80

void ProgressScreenClass::Load_Shape(char const *filename, void const *image, int unknown)
{
    if (filename != 0) {
        if (Shape != 0) {
            Free_Shape();
        }
        Shape = (ShapeFileStruct const *)Unknown_Load_Shape_00495270(filename, ShapeAllocated);
        if (Shape != 0) {
            if (image != 0) {
                Image = image;
                Unknown_00515A80(image, false);
            }
            unknown_74 = unknown;
        }
    }
}
