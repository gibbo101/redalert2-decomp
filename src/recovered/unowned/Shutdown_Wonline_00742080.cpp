#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/map_preview.hpp"
#include "shared/connection_points.hpp"
#include "shared/atl_module.hpp"
extern bool wol_initialized_b2ac81;
extern HANDLE wol_wait_events_b264f8[18];
extern unsigned long wol_chat_cookie_b2ac60,wol_net_cookie_b2ac64,wol_download_cookie_b2ac68;
extern GUID const wol_chat_event_iid_007af5b0,wol_net_event_iid_007af5f0,wol_download_event_iid_007af5d0;
extern _ATL_MODULE wol_module_b292f8;
// @ref ?wol_initialized_b2ac81@@3_NA=00b2ac81
// @ref ?wol_wait_events_b264f8@@3PAPAXA=00b264f8
// @ref ?wol_chat_cookie_b2ac60@@3KA=00b2ac60
// @ref ?wol_net_cookie_b2ac64@@3KA=00b2ac64
// @ref ?wol_download_cookie_b2ac68@@3KA=00b2ac68
// @ref ?wol_chat_event_iid_007af5b0@@3UGUID@@B=007af5b0
// @ref ?wol_net_event_iid_007af5f0@@3UGUID@@B=007af5f0
// @ref ?wol_download_event_iid_007af5d0@@3UGUID@@B=007af5d0
// @ref ?wol_module_b292f8@@3U_ATL_MODULE@@A=00b292f8
// @ref _IID_IConnectionPointContainer=007afd20
inline HRESULT __stdcall Atl_Unadvise_Wonline(IUnknown *source,GUID const &event_iid,unsigned long cookie)
{
    CComPtr<IConnectionPointContainer> container;
    CComPtr<IConnectionPoint> point;
    HRESULT result=source->QueryInterface(IID_IConnectionPointContainer,(void **)&container);
    if(SUCCEEDED(result)) result=container->FindConnectionPoint(event_iid,&point);
    if(SUCCEEDED(result)) result=point->Unadvise(cookie);
    return result;
}
void Shutdown_Wonline_00742080()
{
    if(unknown_dialog_preview_a72ce8) {
        delete unknown_dialog_preview_a72ce8;
        unknown_dialog_preview_a72ce8=0;
    }
    void *dialog=Unknown_00735940(0x11e);
    if(dialog) Unknown_007357E0(dialog,0);
    if(wol_initialized_b2ac81) {
        Unknown_Free_Lobby_Entries_005c8950();
        if(unknown_chat_a72cfc) {
            Atl_Unadvise_Wonline(unknown_chat_a72cfc,wol_chat_event_iid_007af5b0,wol_chat_cookie_b2ac60);
            unknown_chat_a72cfc->Release();
        }
        if(unknown_ladder_client_a72d00) {
            Atl_Unadvise_Wonline(unknown_ladder_client_a72d00,wol_net_event_iid_007af5f0,wol_net_cookie_b2ac64);
            unknown_ladder_client_a72d00->Release();
        }
        if(unknown_download_a72d04) {
            Atl_Unadvise_Wonline(unknown_download_a72d04,wol_download_event_iid_007af5d0,wol_download_cookie_b2ac68);
            unknown_download_a72d04->Release();
        }
        unknown_chat_a72cfc=0;
        unknown_ladder_client_a72d00=0;
        unknown_download_a72d04=0;
        for(int i=0;i<18;++i) CloseHandle(wol_wait_events_b264f8[i]);
        AtlModuleTerm(&wol_module_b292f8);
        wol_initialized_b2ac81=false;
    }
}
