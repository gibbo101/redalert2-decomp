// bool BuildingTypeClass::unknown_func_458e00(void **image, int *frame) const (0x00458E00)
// For a type that leaves rubble: the image (slot 39) and frame 3 when the
// image has more than three frames per half (hypothesis: the rubble frame).
#include "shared/building_type.hpp"
#include "shared/shape_file.hpp"

bool BuildingTypeClass::unknown_func_458e00(void **image, int *frame) const
{
    if (LeaveRubble && image) {
        *image = unknown_slot39();
        if (*image && ((ShapeFileStruct *)*image)->FrameCount / 2 > 3) {
            *frame = 3;
            return true;
        }
    }
    return false;
}
