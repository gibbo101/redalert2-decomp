// HRESULT __stdcall CChatEventSink::OnSquadInfo(HRESULT result, unsigned long id, WOL::Squad *squad) (0x0075ED00, slot 32)
// Stores the squad's name and abbreviation in the users of that squad (and, when it was the
// local player's lookup, the local squad), then requests the squad's ladder entry if uncached.
#include "shared/wol_sink.hpp"
// @ref ?unknown_squad_query_b2abf8=00b2abf8
// @ref ?unknown_squad_id_b2abfc=00b2abfc
// @ref ?unknown_squad_name_b2a8b0=00b2a8b0

HRESULT __stdcall CChatEventSink::OnSquadInfo(HRESULT result, unsigned long id, WOL::Squad *squad)
{
    --unknown_query_count_b2abf4;
    if (unknown_squad_query_b2abf8) {
        unknown_squad_query_b2abf8 = 0;
        unknown_squad_id_b2abfc = id;
        if (result != S_OK) return S_OK;
        strcpy(unknown_squad_name_b2a8b0, squad->name);
    } else if (result != S_OK) {
        return S_OK;
    }
    for (int index = 0; index < unknown_users_b2a728.Count; ++index) {
        WOL::User *user = 0;
        unknown_users_b2a728.Get(user, index);
        if (user->unknown_14 == id) {
            strcpy(user->unknown_57, squad->name);
            strcpy(user->unknown_2e, squad->abbreviation);
        }
    }
    Wstring name(squad->name);
    name.To_Lower();
    if (!unknown_ladder_b296f8.Contains(name)) {
        unknown_ladder_client_a72d00->Request(unknown_ladder_address_b29018, unknown_ladder_port_b2a8ac, squad->name, 0x802100, -1, 0, 0);
    }
    if (unknown_query_count_b2abf4 == 0) Unknown_0073FEE0(0, false);
    return S_OK;
}
// @ref ?unknown_ladder_b296f8=00b296f8
// @ref ?unknown_query_count_b2abf4=00b2abf4
