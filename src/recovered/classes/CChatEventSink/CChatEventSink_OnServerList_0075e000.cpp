#include "shared/wol_sink.hpp"
HRESULT __stdcall CChatEventSink::OnServerList(HRESULT result, WOL::Server *servers)
{
    WOL::Server *current = servers;
    int irc_count = 0;
    int matching_irc = 0;
    int game_count = 0;
    srand(time(0));
    if (FAILED(result)) {
        SetEvent(unknown_server_error_event_b264f8);
        swprintf(unknown_server_error_b2a8ec, StringTable::Load_String("TXT_NO_SERV_LIST", 0, "D:\\Ra2\\wonline.cpp", 0xff9));
        return S_OK;
    }
    bool got_mangler = false;
    char ladder_text[128];
    char second_game_text[128];
    char irc_text[128];
    char wdt_text[128];
    char first_game_text[128];
    char mangler_text[128];
    while (current) {
        if (!strcmp(current->kind, "IRC")) {
            if (!irc_count) {
                unknown_servers_b2a700.Insert(unknown_servers_b2a700.Count, *current);
                unknown_irc_index_b292d8 = 0;
                irc_count = 1;
            } else {
                unknown_servers_b2a700.Insert(unknown_servers_b2a700.Count, *current);
                strcpy(irc_text, current->name);
                unsigned int protocol = -1;
                char *token = strtok(irc_text, ",");
                while (token && (protocol = atol(token)) != (unknown_protocol_7fd370 & 0xff) && !strchr(token, ':')) token = strtok(0, ",");
                if (protocol == (unknown_protocol_7fd370 & 0xff)) {
                    ++matching_irc;
                    if ((double)rand() * (1.0 / 32767.0) <= 1.0 / matching_irc) unknown_irc_index_b292d8 = irc_count;
                }
                ++irc_count;
                unknown_irc_index_b2a7f4 = unknown_irc_index_b292d8;
            }
        } else if (!strcmp(current->kind, "LAD")) {
            strcpy(ladder_text, current->connection);
            strtok(ladder_text, ";");
            char *token = strtok(0, ";");
            if (token) strcpy(unknown_ladder_address_b29018, token);
            token = strtok(0, ";");
            if (token) unknown_ladder_port_b2a8ac = atol(token);
        } else if (!strcmp(current->kind, "GAM") && game_count == 0) {
            unknown_game_server_b28cd0 = *current;
            strcpy(first_game_text, unknown_game_server_b28cd0.connection);
            strtok(first_game_text, ";");
            char *token = strtok(0, ";");
            if (token) strcpy(unknown_game_address_b2a758, token);
            token = strtok(0, ";");
            if (token) unknown_game_port_b28ffc = atol(token);
            unknown_game_address_b2ab00[0] = 0;
            unknown_game_port_b28dd4 = 0;
            game_count = 1;
        } else if (!strcmp(current->kind, "GAM") && game_count == 1) {
            unknown_game_server_b28cd0 = *current;
            strcpy(second_game_text, unknown_game_server_b28cd0.connection);
            strtok(second_game_text, ";");
            char *token = strtok(0, ";");
            if (token) strcpy(unknown_game_address_b2ab00, token);
            token = strtok(0, ";");
            if (token) unknown_game_port_b28dd4 = atol(token);
            game_count = 2;
        } else if (!strcmp(current->kind, "WDT")) {
            unknown_wdt_server_b29880 = *current;
            strcpy(wdt_text, unknown_wdt_server_b29880.connection);
            strtok(wdt_text, ";");
            char *token = strtok(0, ";");
            if (token) strcpy(unknown_wdt_address_b269ac, token);
            token = strtok(0, ";");
            if (token) unknown_wdt_port_b299bc = atol(token);
        } else if (!_stricmp(current->kind, "MGL")) {
            Debug_Printf("MGL entry in server list\n");
            if (!got_mangler) {
                memset(unknown_mangler_addresses_b26cbc, 0, sizeof(unknown_mangler_addresses_b26cbc));
                unknown_mangler_count_b2ac34 = 0;
                memset(unknown_mangler_ports_b291a4, 0, sizeof(unknown_mangler_ports_b291a4));
                got_mangler = true;
            }
            WOL::Server *copy = new WOL::Server;
            *copy = *current;
            strcpy(mangler_text, copy->connection);
            strtok(mangler_text, ";");
            char *token = strtok(0, ";");
            if (token) {
                strcpy(unknown_mangler_addresses_b26cbc[unknown_mangler_count_b2ac34], token);
                token = strtok(0, ";");
                if (token) unknown_mangler_ports_b291a4[unknown_mangler_count_b2ac34] = atol(token);
                Debug_Printf("Got mangler server from servserv - address is %s ; %d\n", unknown_mangler_addresses_b26cbc[unknown_mangler_count_b2ac34], unknown_mangler_ports_b291a4[unknown_mangler_count_b2ac34]);
                ++unknown_mangler_count_b2ac34;
            }
            delete copy;
        }
        current = current->next;
    }
    WOL::Server *server = 0;
    for (int i = 0; i < unknown_servers_b2a700.Count; ++i) {
        unknown_servers_b2a700.Get(server, i);
        strcpy(server->nickname, unknown_wstring_b26cb8.Get());
        strcpy(server->password, unknown_password_b2a63c.Get());
    }
    Debug_Printf("Got %d mangler servers\n", unknown_mangler_count_b2ac34);
    if (unknown_mangler_count_b2ac34 > 1) unknown_mangler_index_b2ac38 = unknown_random_839218(0, unknown_mangler_count_b2ac34 - 1);
    else unknown_mangler_index_b2ac38 = 0;
    Debug_Printf("CurrentManglerServer = %d\n", unknown_mangler_index_b2ac38);
    wchar_t const *status = StringTable::Load_String("TXT_DETECTING_FIREWALL_SETTINGS", 0, "D:\\Ra2\\wonline.cpp", 0x10af);
    HWND dialog = (HWND)Unknown_00735940(0xc4);
    if (dialog) SendDlgItemMessageA(dialog, 0x5b2, 0x4b2, 0, (LPARAM)status);
    unknown_firewall_a71b18.Detect_And_Save_005b9e80();
    SetEvent(unknown_server_list_event_b264fc);
    return S_OK;
}
// @ref ?Grow_00768110@WolServerArray@@=00768110
// @ref ?unknown_servers_b2a700=00b2a700
// @ref ?unknown_game_server_b28cd0=00b28cd0
// @ref ?unknown_wdt_server_b29880=00b29880
// @ref ?unknown_irc_index_b292d8=00b292d8
// @ref ?unknown_irc_index_b2a7f4=00b2a7f4
// @ref ?unknown_protocol_7fd370=007fd370
// @ref ?unknown_mangler_count_b2ac34=00b2ac34
// @ref ?unknown_mangler_index_b2ac38=00b2ac38
// @ref ?unknown_ladder_address_b29018=00b29018
// @ref ?unknown_ladder_port_b2a8ac=00b2a8ac
// @ref ?unknown_game_address_b2a758=00b2a758
// @ref ?unknown_game_address_b2ab00=00b2ab00
// @ref ?unknown_game_port_b28ffc=00b28ffc
// @ref ?unknown_game_port_b28dd4=00b28dd4
// @ref ?unknown_wdt_address_b269ac=00b269ac
// @ref ?unknown_wdt_port_b299bc=00b299bc
// @ref ?unknown_mangler_addresses_b26cbc=00b26cbc
// @ref ?unknown_mangler_ports_b291a4=00b291a4
// @ref ?unknown_server_error_event_b264f8=00b264f8
// @ref ?unknown_server_list_event_b264fc=00b264fc
// @ref ?unknown_server_error_b2a8ec=00b2a8ec
// @ref ?Detect_And_Save_005b9e80@FirewallSettings@@=005b9e80
// @ref ?unknown_firewall_a71b18=00a71b18
// @ref ?unknown_wstring_b26cb8=00b26cb8
// @ref ?unknown_password_b2a63c=00b2a63c
// @ref _atol=00782d72
// @ref _srand=0078469d
// @ref _rand=007846aa
// @ref ??_C@_03EMEC@WDT?$AA@=007fdc80
// @ref ??_C@_03HGHH@GAM?$AA@=007fdc84
// @ref ??_C@_03JPIH@MGL?$AA@=007fdc7c
// @ref ??_C@_03OONG@LAD?$AA@=007fdc88
// @ref ??_C@_03PACJ@IRC?$AA@=007fdc8c
// @ref ??_C@_0BB@MDD@TXT_NO_SERV_LIST?$AA@=007fdc90
// @ref ??_C@_0BI@LGLC@Got?5?$CFd?5mangler?5servers?6?$AA@=007fdc10
// @ref ??_C@_0BK@PMMH@MGL?5entry?5in?5server?5list?6?$AA@=007fdc60
// @ref ??_C@_0BL@GEFL@CurrentManglerServer?5?$DN?5?$CFd?6?$AA@=007fdbf4
// @ref ??_C@_0CA@NBLO@TXT_DETECTING_FIREWALL_SETTINGS?$AA@=007fdbd4
// @ref ??_C@_0DH@NIHF@Got?5mangler?5server?5from?5servserv@=007fdc28
// @ref __real@8@3ff08001000200040000=007af928
// @ref ??_C@_0BD@IJO@D?3?2Ra2?2wonline?4cpp?$AA@=007fd62c
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
// @ref ??_C@_01FAJB@?$DL?$AA@=007d27e4
