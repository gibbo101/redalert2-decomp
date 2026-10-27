#include "shared/coop_campaign.hpp"
void __cdecl operator delete[](void *block);
// @ref ??_V@YAXPAX@Z=00781d3b
CoopCampaignClass::~CoopCampaignClass()
{
    if(MapNames) {
        for(int i=0;i<MapCount;++i) {
            if(MapNames[i]) delete [] MapNames[i];
        }
        delete [] MapNames;
    }
}
