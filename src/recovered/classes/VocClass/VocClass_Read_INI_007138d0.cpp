// bool VocClass::Read_INI(CCINIClass &ini) (0x007138D0): sets the event type's
// samples and settings from its Sound.ini section; false without an event type
// or section.
#include "shared/voc_class.hpp"
#include "shared/ccini_class.hpp"
#include "shared/crt_tokens.hpp"
extern "C" int __cdecl atoi(char const *string);
// @ref _strtok=00782ec2
// @ref ??_C@_00A@?$AA@=0083c55c
// @ref ??_C@_04FCOP@Type?$AA@=007d9eec
// @ref ??_C@_04PHFA@Loop?$AA@=007d9e10
// @ref ??_C@_05MCCK@Range?$AA@=007f9afc
// @ref ??_C@_06MEDA@Sounds?$AA@=007e5a44
// @ref ??_C@_08MJHG@Priority?$AA@=007f7038
// @ref ??_C@_0M@OOFK@Invalid?5Voc?$AA@=007f9b3c
// @ref __real@4@3ff8a3d70a0000000000=007a5df0
// @ref ??_C@_03OALN@?5?7?6?$AA@=007f9b38
// @ref ??_C@_05BBKO@Delay?$AA@=007f9af4
// @ref ??_C@_05BMGN@Limit?$AA@=007f9b04
// @ref ??_C@_05DPHK@Decay?$AA@=007f9b14
// @ref ??_C@_06HDDE@NORMAL?$AA@=007ccca4
// @ref ??_C@_06IJCK@VShift?$AA@=007f9b28
// @ref ??_C@_06MBHJ@Attack?$AA@=007cd8fc
// @ref ??_C@_06NDCI@FShift?$AA@=007f9aec
// @ref ??_C@_06OPOL@Volume?$AA@=007f9b30
// @ref ??_C@_07FNBF@Control?$AA@=007f9b0c
// @ref ??_C@_09EHOI@MinVolume?$AA@=007f9b1c
// @ref ?Audio_Control_Apply_Keyword@@YI_NPAIPBD@Z=00406830
// @ref ?Audio_Event_Type_Set_Delay@@YIXPAUAudioEventType@@HH@Z=00406610
// @ref ?Audio_Event_Type_Set_FShift@@YIXPAUAudioEventType@@HH@Z=00406620
// @ref ?Audio_Event_Type_Set_Intro@@YIXPAUAudioEventType@@H@Z=00406530
// @ref ?Audio_Event_Type_Set_Limit@@YIXPAUAudioEventType@@H@Z=004065e0
// @ref ?Audio_Event_Type_Set_Loop@@YIXPAUAudioEventType@@H@Z=00406650
// @ref ?Audio_Event_Type_Set_Min_Volume@@YIXPAUAudioEventType@@M@Z=00406600
// @ref ?Audio_Event_Type_Set_Outro@@YIXPAUAudioEventType@@H@Z=00406540
// @ref ?Audio_Event_Type_Set_Priority@@YIXPAUAudioEventType@@H@Z=00406550
// @ref ?Audio_Event_Type_Set_Range@@YIXPAUAudioEventType@@H@Z=004065f0
// @ref ?Audio_Event_Type_Set_Type@@YIXPAUAudioEventType@@I@Z=004065d0
// @ref ?Audio_Priority_From_Name@@YI_NPBDPAH@Z=004067e0
// @ref ?unknown_voc_control_ad0850@@3IA=00ad0850
// @ref ?unknown_voc_limit_7f9a80@@3HA=007f9a80
// @ref ?unknown_voc_min_volume_7f9a74@@3MA=007f9a74
// @ref ?unknown_voc_priority_7f9a6c@@3HA=007f9a6c
// @ref ?unknown_voc_range_7f9a7c@@3HA=007f9a7c
// @ref ?unknown_voc_type_7f9a78@@3IA=007f9a78
// @ref ?unknown_voc_volume_7f9a70@@3MA=007f9a70
// @ref _atoi=00782dfd

bool VocClass::Read_INI(CCINIClass &ini)
{
    if (Event == 0 || !ini.Is_Present(Name())) {
        return false;
    }
    char buffer[0x800];
    char *token;

    ini.Get_String(Name(), "Sounds", "", buffer, sizeof(buffer));
    for (token = strtok(buffer, " \t\n"); token != 0; token = strtok(0, " \t\n")) {
        Audio_Event_Type_Add_Sample(Event, token);
    }

    float volume = (float)ini.Get_Double(Name(), "Volume", unknown_voc_volume_7f9a70) * 0.01f;
    if (volume > 1.0) {
        volume = 1.0f;
    } else if (volume <= 0) {
        volume = 0.0f;
    }
    Audio_Event_Type_Set_Volume(Event, (int)(volume * 16384.0f));

    Audio_Event_Type_Set_Percent(Event, ini.Get_Int(Name(), "VShift", 0));

    float min_volume = (float)ini.Get_Double(Name(), "MinVolume", unknown_voc_min_volume_7f9a74) * 0.01f;
    if (min_volume > 1.0) {
        min_volume = 1.0f;
    } else if (min_volume <= 0) {
        min_volume = 0.0f;
    }
    Audio_Event_Type_Set_Min_Volume(Event, min_volume);

    ini.Get_String(Name(), "Priority", "NORMAL", buffer, sizeof(buffer));
    int priority = unknown_voc_priority_7f9a6c;
    Audio_Priority_From_Name(buffer, &priority);
    Audio_Event_Type_Set_Priority(Event, priority);

    Audio_Event_Type_Set_Intro(Event, ini.Get_Int(Name(), "Attack", 0));
    Audio_Event_Type_Set_Outro(Event, ini.Get_Int(Name(), "Decay", 0));

    ini.Get_String(Name(), "Control", "", buffer, sizeof(buffer));
    token = strtok(buffer, " \t\n");
    unsigned int control = unknown_voc_control_ad0850;
    if (token != 0) {
        control = 0;
        do {
            Audio_Control_Apply_Keyword(&control, token);
            token = strtok(0, " \t\n");
        } while (token != 0);
    }
    Audio_Event_Type_Set_Flags(Event, control);

    ini.Get_String(Name(), "Type", "", buffer, sizeof(buffer));
    token = strtok(buffer, " \t\n");
    unsigned int type = unknown_voc_type_7f9a78;
    if (token != 0) {
        type = 0x20;
        do {
            Audio_Event_Apply_Keyword(&type, token);
            token = strtok(0, " \t\n");
        } while (token != 0);
    }
    Audio_Event_Type_Set_Type(Event, type);

    Audio_Event_Type_Set_Limit(Event, ini.Get_Int(Name(), "Limit", unknown_voc_limit_7f9a80));
    Audio_Event_Type_Set_Loop(Event, ini.Get_Int(Name(), "Loop", 0));
    Audio_Event_Type_Set_Range(Event, ini.Get_Int(Name(), "Range", unknown_voc_range_7f9a7c));

    ini.Get_String(Name(), "Delay", "", buffer, sizeof(buffer));
    token = strtok(buffer, " \t\n");
    int low = 0;
    if (token != 0) {
        low = atoi(token);
        token = strtok(0, " \t\n");
    }
    int high = low;
    if (token != 0) {
        high = atoi(token);
    }
    Audio_Event_Type_Set_Delay(Event, low, high);

    ini.Get_String(Name(), "FShift", "", buffer, sizeof(buffer));
    token = strtok(buffer, " \t\n");
    low = 0;
    if (token != 0) {
        low = atoi(token);
        token = strtok(0, " \t\n");
    }
    high = low;
    if (token != 0) {
        high = atoi(token);
    }
    Audio_Event_Type_Set_FShift(Event, low, high);
    return true;
}
