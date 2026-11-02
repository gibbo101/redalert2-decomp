// void WorldDominationTour::Voices::Say_List(int index, bool counted, int delay) (0x00732700)
#include "shared/wdt_voices.hpp"

namespace WorldDominationTour {

void Voices::Say_List(int index, bool counted, int delay)
{
    Trim();
    Wstring name;
    if (Pick_List(index, name)) {
        if (!Speech_Is_Playing()) {
            Timer = delay;
        }
        Queue.Add(name);
        if (counted) {
            Pending++;
        }
    }
}

}
