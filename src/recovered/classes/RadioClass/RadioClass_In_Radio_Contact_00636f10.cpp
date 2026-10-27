#include "shared/radio.hpp"

bool RadioClass::In_Radio_Contact() const {
    for (int index = 0; index < RadioLinks.Length(); ++index) {
        if (RadioLinks[index]) return true;
    }
    return false;
}
