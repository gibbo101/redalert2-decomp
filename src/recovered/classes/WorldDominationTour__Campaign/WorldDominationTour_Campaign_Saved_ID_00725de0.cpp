// int __fastcall WorldDominationTour::Campaign::Saved_ID(Wstring const &name) (0x00725DE0)
// The CampaignID saved in WDTHist.INI under the campaign's name; -1 without
// the file (or the entry). No callers in the executable.
#define VECTOR_IMPLEMENT_ALL
#include "shared/wdt_campaign.hpp"

namespace WorldDominationTour {

int __fastcall Campaign::Saved_ID(Wstring const &name)
{
    CDFileClass file("WDTHist.INI");
    if (file.Is_Available()) {
        INIClass ini;
        ini.Load(file, false);
        file.Close();
        Wstring key("CampaignID");
        return ini.Get_Int(name, key, -1);
    }
    return -1;
}

}
