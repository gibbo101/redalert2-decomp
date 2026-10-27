#include "shared/radio.hpp"
void RadioClass::Set_Radio_Count(int count) {
    int previous = RadioLinks.Length();
    if (count > previous) {
        RadioLinks.Resize(count);
        for (int index = previous; index < count; ++index) RadioLinks[index] = 0;
    }
}
