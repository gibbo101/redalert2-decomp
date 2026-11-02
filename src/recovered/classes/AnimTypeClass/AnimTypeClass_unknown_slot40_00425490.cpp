// void AnimTypeClass::unknown_slot40(int theater) (0x00425490)
// Loads the image (TibSun AnimTypeClass::Load_Image): the theater-named SHP
// of the Image= name (else the ID), falling back to the generic name; then
// defaults End/LoopEnd from the frame count and records the largest frame.
#include "shared/anim_type.hpp"
#include "shared/unknown_static_rect.hpp"
#define SHAPE_FILE_EMPTY_RECT unknown_static_rect
#include "shared/shape_file.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/mix_file_class.hpp"

void AnimTypeClass::unknown_slot40(int theater)
{
    if (!DemandLoad) {
        if (unknown_1fc) {
            unknown_func_5d7630();
        } else {
            if (unknown_a4 != 0 && unknown_a8) {
                operator delete(unknown_a4);
                unknown_a8 = false;
            }
            unknown_a4 = 0;
            char fullname[512];
            _makepath(fullname, 0, 0, unknown_1c8[0] != '\0' ? (char const *)unknown_1c8 : ID, ".SHP");
            Theater_Naming_Convention(fullname, theater);
            unknown_a4 = (void *)MixFileClass<CCFileClass>::Retrieve(fullname);
            if (unknown_a4 == 0) {
                Generic_Naming_Convention(fullname);
                unknown_a4 = (void *)MixFileClass<CCFileClass>::Retrieve(fullname);
            }
        }
    }

    ShapeFileStruct const *shape = (ShapeFileStruct const *)unknown_a4;
    if (shape != 0) {
        if (End == 0) {
            End = shape->FrameCount;
            if (Shadow) {
                End /= 2;
            }
        }
        if (LoopEnd == 0) {
            LoopEnd = End;
        }

        int biggest_size = 0;
        int biggest_frame = 0;
        for (int frame = 0; frame < shape->FrameCount; frame++) {
            Rect rect = shape->Get_Frame_Rect(frame);
            if (rect.Width * rect.Height > biggest_size) {
                biggest_frame = frame;
                biggest_size = rect.Width * rect.Height;
            }
        }
        unknown_268 = biggest_frame;
    }
}
