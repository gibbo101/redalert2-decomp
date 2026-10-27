// MSShapeAnim::~MSShapeAnim() (0x005AC720)
// Releases a shape this animation loaded itself.
#include "shared/ms_anim.hpp"

MSShapeAnim::~MSShapeAnim()
{
    if (Shape != 0 && OwnsShape) {
        operator delete(Shape);
        Shape = 0;
        OwnsShape = false;
    }
}
