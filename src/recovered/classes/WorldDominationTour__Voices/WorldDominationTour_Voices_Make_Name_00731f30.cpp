// bool __fastcall WorldDominationTour::Voices::Make_Name(int faction, int line, Wstring &name) (0x00731F30)
// "WWD-Soviet<NN>" for faction 3, else "WWD_Allied<NN>".
#include "shared/wdt_voices.hpp"

namespace WorldDominationTour {

bool __fastcall Voices::Make_Name(int faction, int line, Wstring &name)
{
    if (faction == 3) {
        name = "WWD-Soviet" + Wstring_From_Integer(line, 2);
    } else {
        name = "WWD_Allied" + Wstring_From_Integer(line, 2);
    }
    return true;
}

}
