// ObjectClass slot71 existing ABI/layout only; diagnostic, not accepted.
// Full BuildingType include emits held existing Rect initializer; no suppression.
#include "shared/techno.hpp"
#include "shared/building_type.hpp"
// @ref ?As_Techno@AbstractClass@@QAEPAVTechnoClass@@XZ=0040dc20
bool ObjectClass::unknown_slot71(int request)
{
    int action = request;
    if (!unknown_76) {
        if (action == 2) {
            if (!unknown_75 && unknown_74) {
                unknown_slot75();
                return true;
            }
        } else {
            if (Kind_Of() != 6 ||
                !static_cast<BuildingClass *>(this)->Type->unknown_bf0 || action != 0) {
                TechnoClass *techno = As_Techno();
                if (techno) {
                    techno->unknown_slot168();
                    techno->Owner();
                    unknown_slot104();
                }
            }
            if ((action == 1 || action == 3) && !unknown_74) {
                unknown_74 = true;
                unknown_slot75();
                return true;
            }
            if (action == 0 && unknown_74) {
                unknown_74 = false;
                return true;
            }
        }
    }
    return false;
}
