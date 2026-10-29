// HRESULT __stdcall CChatEventSink::OnUserLocale(HRESULT result, WOL::User *users) (0x00764D70, slot 33)
// Records each user's locale by lower-case name; for the local player also stores it in the
// profile (saved to the registry when profiles are kept there) and signals the waiting request.
// The local-player test and the stored locale read the first user of the list, not the current one.
#include "shared/wol_sink.hpp"
// @ref ?unknown_b26530=00b26530
// @ref ?unknown_profile_b28cc4=00b28cc4
// @ref ?Set_Locale_00739950@PlayerProfile@@QAEXHH@Z=00739950
// @ref ?Save_007395d0@PlayerProfile@@QAEXABVWstring@@@Z=007395d0

HRESULT __stdcall CChatEventSink::OnUserLocale(HRESULT result, WOL::User *users)
{
    bool local = false;
    if (result < 0) {
        Debug_Printf("OnUserLocale callback failed!\n");
        return S_OK;
    }
    WOL::User *user = users;
    while (user) {
        Wstring name;
        name.Set(user->name);
        name.To_Lower();
        int old_locale;
        unknown_channel_names_b293a0.Remove_007675e0(name, &old_locale);
        int locale = user->locale;
        WolChannelNameSet::Node *node = new WolChannelNameSet::Node;
        node->Key = name;
        node->Value = locale;
        node->Next = 0;
        unsigned int bucket = unknown_channel_names_b293a0.Key_Hash_007679a0(name);
        WolChannelNameSet::Node *head = unknown_channel_names_b293a0.Buckets[bucket];
        unknown_channel_names_b293a0.Buckets[bucket] = node;
        if (head) node->Next = head;
        ++unknown_channel_names_b293a0.Count;
        if ((float)unknown_channel_names_b293a0.Count / (float)unknown_channel_names_b293a0.Get_Size() >= unknown_channel_names_b293a0.GrowLimit) {
            unknown_channel_names_b293a0.Grow_00767900();
        }
        if (!_stricmp(users->name, unknown_wstring_b26cb8.Get())) {
            WolRegistryOptions options;
            options.Read_004ff200();
            rc_ptr<PlayerProfile> profile;
            if (options.unknown_004ff2c0()) {
                profile = PlayerProfile::Load_00738880(unknown_wstring_b26cb8);
            } else {
                profile.Set(unknown_profile_b28cc4);
            }
            profile->Set_Locale_00739950(users->locale, 2);
            if (options.unknown_004ff2c0()) profile->Save_007395d0(unknown_wstring_b26cb8);
            Debug_Printf("OnUserLocale callback - Locale is %d\n", users->locale);
            local = true;
        }
        user = user->next;
    }
    if (local) SetEvent(unknown_b26530);
    return S_OK;
}
// @ref ??_C@_0BP@BBKG@OnUserLocale?5callback?5failed?$CB?6?$AA@=007fe350
// @ref ??_C@_0CG@DJLJ@OnUserLocale?5callback?5?9?5Locale?5i@=007fe328
// @ref ??_7?$rc_ptr@VPlayerProfile@@@@6B@=007af54c
// @ref ??_G?$rc_ptr@VPlayerProfile@@@@UAEPAXI@Z=0073a0c0
