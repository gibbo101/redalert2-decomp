// Point2D __stdcall FlyLocomotionClass::Draw_Point() (0x004BEFB0, ILocomotion 11)
// The screen offset of the drawn aircraft: (0, bob), where the bob (0..2) follows the
// frame counter when the aircraft is not a dropship, neither +0x50 nor +0x51 is set
// and the height the 0x007D80A8 interface reports is below slot 108.
#include "shared/fly_locomotion.hpp"
#include "shared/foot.hpp"
#include "shared/techno_type.hpp"
#include "shared/fast_math.hpp"
// @ref ?Fast_Sin@@YAMN@Z=004ba480
// @ref ?Release_Held@?$UnknownComPtr@UUnknownFlyInterface@@$1?unknown_uuid_7d80a8@@3UGUID@@B@@QAEXXZ=004bfbc0
// @ref __real@8@3ffda0d97bb4e7870000=007a1100
// @ref __real@8@3fff8000000000000000=0079d568
// @ref __real@8@3ffe8000000000000000=0079a728
// @ref _unknown_uuid_7d80a8=007d80a8

Point2D __stdcall FlyLocomotionClass::Draw_Point()
{
    int bob = 0;
    UnknownFlyPtr source(LinkedTo);
    int height = 0;
    if (source) {
        height = source->unknown_slot3();
    }
    if (!LinkedTo->unknown_slot32()->IsDropship && !unknown_51 && !unknown_50 && LinkedTo->unknown_slot108() > height) {
        bob = (int)(Fast_Sin((Frame % 20) * 0.3141592653589793) * 1.5 + 0.5);
    }
    return Point2D(0, bob);
}
