// void WorldDominationTour::Voices::Say(int group, int kind, bool emphasis, bool counted, int delay) (0x00732510)
#include "shared/wdt_voices.hpp"

namespace WorldDominationTour {

void Voices::Say(int group, int kind, bool emphasis, bool counted, int delay)
{
    Trim();
    Wstring name;
    if (Pick(group, kind, name)) {
        if (!Speech_Is_Playing()) {
            Timer = delay;
        }
        Queue.Add(name);
        if (counted) {
            Pending++;
        }
        if (emphasis && Pick_Emphasis(group, kind, name)) {
            Queue.Add(name);
            if (counted) {
                Pending++;
            }
        }
    }
}

}
