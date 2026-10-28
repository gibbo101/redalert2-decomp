// void VocClass::Process(CCINIClass &ini) (0x00714540): resets the static
// sounds (their list and a pool of 100), reads the [Defaults] of Sound.ini and
// makes (or finds) a sound effect type for each [SoundList] entry, which then
// reads its own section (name hypothesis).
#include "shared/voc_static.hpp"
#include "shared/ccini_class.hpp"
#include "shared/crt_tokens.hpp"
#include "shared/crt_string.hpp"
// @ref _strtok=00782ec2
// @ref __stricmp=00781f20
// @ref ??_C@_08COGH@Defaults?$AA@=007f9b54
// @ref ??_C@_09PIFF@SoundList?$AA@=007f9b48
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ??_C@_03OALN@?5?7?6?$AA@=007f9b38
// @ref ??_C@_04FCOP@Type?$AA@=007d9eec
// @ref ??_C@_05BMGN@Limit?$AA@=007f9b04
// @ref ??_C@_05MCCK@Range?$AA@=007f9afc
// @ref ??_C@_06HDDE@NORMAL?$AA@=007ccca4
// @ref ??_C@_06OPOL@Volume?$AA@=007f9b30
// @ref ??_C@_07FNBF@Control?$AA@=007f9b0c
// @ref ??_C@_08MJHG@Priority?$AA@=007f7038
// @ref ??_C@_09EHOI@MinVolume?$AA@=007f9b1c
// @ref ??_C@_0M@OOFK@Invalid?5Voc?$AA@=007f9b3c
// @ref ?unknown_voc_static_list_ad07d0@@3UAudioListNode@@A=00ad07d0
// @ref ?unknown_voc_static_pool_ad0844@@3PAUAudioPool@@A=00ad0844
// @ref ?unknown_voc_control_ad0850@@3IA=00ad0850
// @ref ?unknown_voc_limit_7f9a80@@3HA=007f9a80
// @ref ?unknown_voc_min_volume_7f9a74@@3MA=007f9a74
// @ref ?unknown_voc_priority_7f9a6c@@3HA=007f9a6c
// @ref ?unknown_voc_range_7f9a7c@@3HA=007f9a7c
// @ref ?unknown_voc_type_7f9a78@@3IA=007f9a78
// @ref ?unknown_voc_volume_7f9a70@@3MA=007f9a70
// @ref ?Audio_Priority_From_Name@@YI_NPBDPAH@Z=004067e0
// @ref ?Audio_Control_Apply_Keyword@@YI_NPAIPBD@Z=00406830

void __fastcall VocClass::Process(CCINIClass &ini)
{
    Audio_List_Init(&unknown_voc_static_list_ad07d0);
    unknown_voc_static_pool_ad0844 = Audio_Pool_Create(100, sizeof(VocStaticSound));
    Audio_Static_Sound_Count = 0;
    Audio_Static_Sound_Maximum = 0;

    char buffer[0x800];
    char *token;
    if (ini.Is_Present("Defaults")) {
        unknown_voc_volume_7f9a70 = (float)ini.Get_Double("Defaults", "Volume", unknown_voc_volume_7f9a70);
        unknown_voc_min_volume_7f9a74 = (float)ini.Get_Double("Defaults", "MinVolume", unknown_voc_min_volume_7f9a74);
        ini.Get_String("Defaults", "Priority", "NORMAL", buffer, sizeof(buffer));
        Audio_Priority_From_Name(buffer, &unknown_voc_priority_7f9a6c);

        ini.Get_String("Defaults", "Control", "", buffer, sizeof(buffer));
        token = strtok(buffer, " \t\n");
        if (token != 0) {
            unknown_voc_control_ad0850 = 0;
            do {
                Audio_Control_Apply_Keyword(&unknown_voc_control_ad0850, token);
                token = strtok(0, " \t\n");
            } while (token != 0);
        }

        ini.Get_String("Defaults", "Type", "", buffer, sizeof(buffer));
        token = strtok(buffer, " \t\n");
        if (token != 0) {
            unknown_voc_type_7f9a78 = 0x20;
            do {
                Audio_Event_Apply_Keyword(&unknown_voc_type_7f9a78, token);
                token = strtok(0, " \t\n");
            } while (token != 0);
        }

        unknown_voc_limit_7f9a80 = ini.Get_Int("Defaults", "Limit", unknown_voc_limit_7f9a80);
        unknown_voc_range_7f9a7c = ini.Get_Int("Defaults", "Range", unknown_voc_range_7f9a7c);
    }

    if (ini.Is_Present("SoundList")) {
        int count = ini.Entry_Count("SoundList");
        for (int index = 0; index < count; index++) {
            char name[0x20];
            if (ini.Get_String("SoundList", ini.Get_Entry("SoundList", index), "", name, sizeof(name))) {
                VocClass *voc;
                int voc_index = From_Name(name);
                if (voc_index == -1) {
                    voc = new VocClass(name);
                } else {
                    voc = unknown_VocClass_list_00ad0818[voc_index];
                }
                voc->Read_INI(ini);
            }
        }
    }
}
