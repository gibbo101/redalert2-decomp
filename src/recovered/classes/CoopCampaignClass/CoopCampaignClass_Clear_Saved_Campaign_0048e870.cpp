#define INDEX_DECLARE_CONSTRUCTOR
#define LIST_DECLARE_CONSTRUCTOR
#include "shared/quoted_printable.hpp"
extern "C" int __cdecl isalnum(int value);
extern char unknown_encoded_buffer_00851170[];
// @ref _isalnum=00782c31
// @ref ?unknown_encoded_buffer_00851170@@3PADA=00851170
#include "shared/coop_campaign.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/ccini_class.hpp"
extern char const campaign_save_filename_007d4f48[];
// @ref ?campaign_save_filename_007d4f48@@3QBDB=007d4f48
// @ref ??0CCFileClass@@QAE@PBD@Z=00468f50
// @ref ??0CCFileClass@@QAE@XZ=00468fd0
// @ref ?Load@CCINIClass@@QAEHAAVFileClass@@_N1@Z=004696b0
// @ref ?Save@CCINIClass@@QAEHAAVFileClass@@_N@Z=004698f0
// @ref ?Close@CCFileClass@@UAEXXZ=004691f0
// @ref ?Clear@INIClass@@QAE_NPBD0@Z=0050b9a0
// @ref ??1INIClass@@UAE@XZ=0050b8d0
// @ref ??1Buffer@@QAE@XZ=00438410
// @ref ??1BufferIOFileClass@@UAE@XZ=0042f350
inline void Prepare_Campaign_Save_File(FileClass &file)
{
    file.Set_Name(campaign_save_filename_007d4f48);
    file.Open(FILE_RIGHTS_WRITE);
}
bool CoopCampaignClass::Clear_Saved_Campaign_0048e870()
{
    if(FirstName[0] && SecondName[0]) {
        CCFileClass saved(campaign_save_filename_007d4f48);
        CCINIClass ini;
        ini.Load(saved,false,false);
        saved.Close();
        char section[100];
        strcpy(section,Quoted_Printable_Encode_0048dec0(FirstName));
        strcat(section,Quoted_Printable_Encode_0048dec0(SecondName));
        CCFileClass output;
        Prepare_Campaign_Save_File(output);
        ini.Clear(section,0);
        ini.Save(output,false);
        output.Close();
    }
    return true;
}

// @ref ??0?$IndexClass@HPAUINISection@INIClass@@@@QAE@XZ=004910c0
// @ref ??0?$List@PAUINISection@INIClass@@@@QAE@XZ=00490ff0
// @ref ??_7CCINIClass@@6B@=0079aae4
// @ref ?Hex_Digit_0048de60@@YIDH@Z=0048de60
