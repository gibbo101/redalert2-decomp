#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

bool UnknownPairKey::operator==(UnknownPairKey const &other) const
{
    if (other.unknown_04 == unknown_04 && other.unknown_00 == unknown_00) {
        return true;
    }
    return false;
}

}
