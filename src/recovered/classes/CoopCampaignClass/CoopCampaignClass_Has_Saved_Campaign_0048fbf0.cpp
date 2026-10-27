#define LIST_DECLARE_CONSTRUCTOR
#define INDEX_DECLARE_CONSTRUCTOR
#include "shared/coop_campaign.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/ccini_class.hpp"
#include "shared/quoted_printable.hpp"
extern char const campaign_save_filename_007d4f48[];
char *__fastcall Quoted_Printable_Encode_0048dec0(char const *input);
// @ref ?campaign_save_filename_007d4f48@@3QBDB=007d4f48
// @ref ??0CCFileClass@@QAE@PBD@Z=00468f50
// @ref ?Load@CCINIClass@@QAEHAAVFileClass@@_N1@Z=004696b0
// @ref ?Close@CCFileClass@@UAEXXZ=004691f0
// @ref ??1INIClass@@UAE@XZ=0050b8d0
// @ref ??1Buffer@@QAE@XZ=00438410
// @ref ??1BufferIOFileClass@@UAE@XZ=0042f350
// @ref ??0?$IndexClass@HPAUINISection@INIClass@@@@QAE@XZ=004910c0
// @ref ??0?$List@PAUINISection@INIClass@@@@QAE@XZ=00490ff0
// @ref ??_7CCINIClass@@6B@=0079aae4
// @ref ?Find_Section@INIClass@@QBEPAUINISection@1@PBD@Z=0050c9b0
bool CoopCampaignClass::Has_Saved_Campaign_0048fbf0()
{
    if(FirstName[0] && SecondName[0]) {
    CCFileClass saved(campaign_save_filename_007d4f48);
    CCINIClass ini;
    if(!ini.Load(saved,false,false)) {
        saved.Close();
    } else {
    saved.Close();
    char section[100];
    strcpy(section,Quoted_Printable_Encode_0048dec0(FirstName));
    strcat(section,Quoted_Printable_Encode_0048dec0(SecondName));
    return ini.Find_Section(section)!=0;
    }
    }
    return false;
}
