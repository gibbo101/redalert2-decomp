// void WorldDominationTour::Campaign::Load_History(INIClass &ini) (0x00726930)
// Loads WDTHist.ini into ini, creating the file first when it is missing.
// No callers: the unit's callers expand it inline.
#include "shared/wdt_campaign.hpp"

namespace WorldDominationTour {

void Campaign::Load_History(INIClass &ini)
{
    CDFileClass file;
    file.Open("WDTHist.ini", FILE_RIGHTS_READ);
    if (!file.Is_Available()) {
        file.Create();
        file.Close();
        file.Open("WDTHist.ini", FILE_RIGHTS_READ);
    }
    ini.Load(file, false);
    file.Close();
}

}
