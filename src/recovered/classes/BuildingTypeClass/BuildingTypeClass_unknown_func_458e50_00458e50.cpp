// bool BuildingTypeClass::unknown_func_458e50(void **image, int *frame) const (0x00458E50)
// Like 0x00458E00, but the frame is half the frame count plus three.
#include "shared/building_type.hpp"
#include "shared/shape_file.hpp"

bool BuildingTypeClass::unknown_func_458e50(void **image, int *frame) const
{
    if (LeaveRubble && image) {
        *image = unknown_slot39();
        if (*image) {
            int half = ((ShapeFileStruct *)*image)->FrameCount / 2;
            if (half > 3) {
                *frame = half + 3;
                return true;
            }
        }
    }
    return false;
}
