#include "shared/coop_campaign.hpp"
#include "shared/unknown_description_list.hpp"
#include "shared/id_source.hpp"
#include "shared/random.hpp"
extern "C" char *__cdecl strncpy(char *destination, char const *source, unsigned int count);
// @ref _strncpy=007823d0
// @ref ??0UnknownDescriptionList_00490E00@@QAE@XZ=00490510
// @ref ??1UnknownDescriptionList_00490E00@@QAE@XZ=00490ca0
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
bool CoopCampaignClass::Load_Campaign_0048f590(int index)
{
    UnknownDescriptionList_00490E00 *campaigns=new UnknownDescriptionList_00490E00;
    if(index>=0 && index<campaigns->Count) {
        UnknownDescriptionRecord_00490E00 *record=&campaigns->Entries[index];
        Initialized=true;
        CurrentMap=-1;
        Kills[0]=0;
        Kills[1]=0;
        Built[0]=0;
        Built[1]=0;
        Score[0]=0;
        Score[1]=0;
        Lost[0]=0;
        Lost[1]=0;
        Time=0;
        if(CampaignType!=index) {
            if(MapNames) {
                for(int i=0;i<MapCount;++i) {
                    if(MapNames[i]) delete [] MapNames[i];
                }
                delete [] MapNames;
            }
            MapNames=0;
            MapCount=0;
            MapNames=new char *[(signed char)record->MapCount];
            for(int m=0;m<(signed char)record->MapCount;++m) {
                int choice=unknown_id_source_a3d290->Random()(0,2);
                MapNames[m]=new char[260];
                strncpy(MapNames[m],record->Maps+(m*3+choice)*260,259);
            }
            MapCount=(signed char)record->MapCount;
            CurrentMap=0;
        }
        CampaignType=index;
        delete campaigns;
        return true;
    }
    delete campaigns;
    return false;
}
