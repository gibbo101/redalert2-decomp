#include "shared/wol_sink.hpp"
#include "shared/multiplayer_game_mode.hpp"
WideString __fastcall Locale_Name_0073f1c0(int locale);
// @ref ?Locale_Name_0073f1c0@@YI?AVWideString@@H@Z=0073f1c0
// @ref ??_7?$rc_ptr@VPlayerProfile@@@@6B@=007af54c
void __fastcall Unknown_00753240(HWND combo)
{
    unknown_reset_combo_6007f0(combo);
    int count=0;
    unknown_chat_a72cfc->unknown_slot52(&count);
    WolRegistryOptions options;
    options.Read_004ff200();
    rc_ptr<PlayerProfile> profile;
    if(options.unknown_004ff2c0()) profile=PlayerProfile::Load_00738880(unknown_wstring_b26cb8);
    else profile.Set(unknown_profile_b28cc4);
    if(count>0) {
    for(int locale=count-1;locale>=0;--locale) {
        WideString name=Locale_Name_0073f1c0(locale);
        int item;
        if(locale<2) item=SendMessageA(combo,0x4c1,0,(LPARAM)name.Get());
        else item=SendMessageA(combo,0x4c2,0,(LPARAM)name.Get());
        SendMessageA(combo,0x151,item,locale);
        if(profile.Get() && locale==profile->unknown_10) SendMessageA(combo,0x14e,item,0);
    }
    }
}
