// int __fastcall Startup_Chat_00741300(HINSTANCE instance) (0x00741300)
// Creates the Westwood Online Chat, NetUtil and Download objects, connects an event sink to each,
// checks the installed API version and gives Chat the registry path and product SKU. Returns 1, or
// -2 after a message box when an object is missing or too old. The Tiberian Sun twin is Startup_Chat.
#include "shared/wol_sink.hpp"
#include "shared/atl_module.hpp"
#include "shared/connection_points.hpp"
#include "shared/lobby.hpp"
#include "shared/string_table.hpp"
extern unsigned long wol_chat_cookie_b2ac60,wol_net_cookie_b2ac64,wol_download_cookie_b2ac68;
extern GUID const wol_chat_event_iid_007af5b0,wol_net_event_iid_007af5f0,wol_download_event_iid_007af5d0;
extern GUID const wol_chat_clsid_007af640,wol_chat_iid_007af5a0,wol_net_clsid_007af660,wol_net_iid_007af5e0,wol_download_clsid_007af650,wol_download_iid_007af5c0;
extern ATL::CComObject<CChatEventSink> *wol_chat_sink_b2a720;
extern ATL::CComObject<CNetUtilEventSink> *wol_net_sink_b26560;
extern ATL::CComObject<CDownloadEventSink> *wol_download_sink_b28de0;
// @ref ?_Module@@3VCComModule@@A=00b292f8
// @ref ?_pModule@@3PAVCComModule@@A=00b2acc0
// @ref ?GUID_ATLVer30@@3UGUID@@A=007fd528
// @ref ?wol_chat_cookie_b2ac60@@3KA=00b2ac60
// @ref ?wol_net_cookie_b2ac64@@3KA=00b2ac64
// @ref ?wol_download_cookie_b2ac68@@3KA=00b2ac68
// @ref ?wol_chat_event_iid_007af5b0@@3UGUID@@B=007af5b0
// @ref ?wol_net_event_iid_007af5f0@@3UGUID@@B=007af5f0
// @ref ?wol_download_event_iid_007af5d0@@3UGUID@@B=007af5d0
// @ref ?wol_chat_clsid_007af640@@3UGUID@@B=007af640
// @ref ?wol_chat_iid_007af5a0@@3UGUID@@B=007af5a0
// @ref ?wol_net_clsid_007af660@@3UGUID@@B=007af660
// @ref ?wol_net_iid_007af5e0@@3UGUID@@B=007af5e0
// @ref ?wol_download_clsid_007af650@@3UGUID@@B=007af650
// @ref ?wol_download_iid_007af5c0@@3UGUID@@B=007af5c0
// @ref ?wol_chat_sink_b2a720@@3PAV?$CComObject@VCChatEventSink@@@ATL@@A=00b2a720
// @ref ?wol_net_sink_b26560@@3PAV?$CComObject@VCNetUtilEventSink@@@ATL@@A=00b26560
// @ref ?wol_download_sink_b28de0@@3PAV?$CComObject@VCDownloadEventSink@@@ATL@@A=00b28de0
// @ref ?CChatEventSinkInterfaceMap@ATL@@3QBUInterfaceMapEntry@1@B=007af760
// @ref ?CNetUtilEventSinkInterfaceMap@ATL@@3QBUInterfaceMapEntry@1@B=007af720
// @ref ?CDownloadEventSinkInterfaceMap@ATL@@3QBUInterfaceMapEntry@1@B=007af708
// @ref ??_7?$CComObject@VCChatEventSink@@@ATL@@6B@=007af77c
// @ref ??_7?$CComObject@VCNetUtilEventSink@@@ATL@@6B@=007af73c
// @ref ?unknown_module_locks_b2930c@@3JA=00b2930c
// @ref _IID_IConnectionPointContainer=007afd20
// @ref ??_C@_0BE@EACC@TXT_APIWRONGVERSION?$AA@=007fdae4
// @ref ??_C@_0P@LCJ@TXT_APIMISSING?$AA@=007fdac8
// @ref ??_C@_07BLJB@RegPath?$AA@=007fdadc
// @ref ??_C@_03HKIO@SKU?$AA@=007fdad8
// @ref ??1?$CComPtr@UIConnectionPoint@@@@QAE@XZ=00765b10
// @ref ??1?$CComPtr@UIConnectionPointContainer@@@@QAE@XZ=00765b00
WIN32_IMPORT LONG WINAPI RegOpenKeyExA(HKEY key,char const *sub_key,unsigned long options,unsigned long access,HKEY *result);
WIN32_IMPORT LONG WINAPI RegQueryValueExA(HKEY key,char const *name,unsigned long *reserved,unsigned long *type,unsigned char *data,unsigned long *size);
extern "C" unsigned int __cdecl strlen(char const *string);
extern "C" char *__cdecl strcpy(char *destination,char const *source);
#define APP_REG_KEY "SOFTWARE\\Westwood\\Red Alert 2"

inline void Clear_Chat_Interfaces()
{
    unknown_chat_a72cfc=0;
    unknown_ladder_client_a72d00=0;
    unknown_download_a72d04=0;
    wol_chat_cookie_b2ac60=0;
    wol_net_cookie_b2ac64=0;
    wol_download_cookie_b2ac68=0;
}

int __fastcall Startup_Chat_00741300(HINSTANCE instance)
{
    HRESULT result=0;
    _Module.Init(0,instance);
    Clear_Chat_Interfaces();

    CoCreateInstance(wol_chat_clsid_007af640,0,1,wol_chat_iid_007af5a0,(void **)&unknown_chat_a72cfc);
    if(unknown_chat_a72cfc) {
        ATL::CComObject<CChatEventSink>::CreateInstance(&wol_chat_sink_b2a720);
        result=AtlAdvise(unknown_chat_a72cfc,wol_chat_sink_b2a720->GetUnknown(),wol_chat_event_iid_007af5b0,&wol_chat_cookie_b2ac60);
    }
    if(unknown_chat_a72cfc==0 || result!=0) {
        Message_Box_005c3230(StringTable::Load_String("TXT_APIMISSING",0,"D:\\Ra2\\wonline.cpp",0x1ec9),0,0,false);
        return -2;
    }

    CoCreateInstance(wol_net_clsid_007af660,0,1,wol_net_iid_007af5e0,(void **)&unknown_ladder_client_a72d00);
    if(unknown_ladder_client_a72d00) {
        ATL::CComObject<CNetUtilEventSink>::CreateInstance(&wol_net_sink_b26560);
        result=AtlAdvise((IUnknown *)unknown_ladder_client_a72d00,wol_net_sink_b26560->GetUnknown(),wol_net_event_iid_007af5f0,&wol_net_cookie_b2ac64);
    }
    if(unknown_ladder_client_a72d00==0 || result!=0) {
        Message_Box_005c3230(StringTable::Load_String("TXT_APIMISSING",0,"D:\\Ra2\\wonline.cpp",0x1ed9),0,0,false);
        return -2;
    }

    CoCreateInstance(wol_download_clsid_007af650,0,1,wol_download_iid_007af5c0,(void **)&unknown_download_a72d04);
    if(unknown_download_a72d04) {
        ATL::CComObject<CDownloadEventSink>::CreateInstance(&wol_download_sink_b28de0);
        result=AtlAdvise(unknown_download_a72d04,wol_download_sink_b28de0->GetUnknown(),wol_download_event_iid_007af5d0,&wol_download_cookie_b2ac68);
    }
    if(unknown_download_a72d04==0 || result!=0) {
        Message_Box_005c3230(StringTable::Load_String("TXT_APIMISSING",0,"D:\\Ra2\\wonline.cpp",0x1ee9),0,0,false);
        return -2;
    }

    unsigned long version;
    unknown_chat_a72cfc->GetVersion(&version);
    if(version<0x1000e) {
        Message_Box_005c3230(StringTable::Load_String("TXT_APIWRONGVERSION",0,"D:\\Ra2\\wonline.cpp",0x1ef5),0,0,false);
        return -2;
    }

    unknown_chat_a72cfc->SetAttributeValue("RegPath",APP_REG_KEY);
    HKEY key;
    char buffer[256];
    if(APP_REG_KEY!=0 && strlen(APP_REG_KEY)) {
        strcpy(buffer,APP_REG_KEY);
        if(RegOpenKeyExA((HKEY)0x80000002,buffer,0,0x20019,&key)==0) {
            unsigned long type;
            unsigned long value;
            unsigned long size=sizeof(value);
            if(RegQueryValueExA(key,"SKU",0,&type,(unsigned char *)&value,&size)==0) unknown_chat_a72cfc->unknown_slot35(value);
            RegCloseKey(key);
        }
    }
    return 1;
}
