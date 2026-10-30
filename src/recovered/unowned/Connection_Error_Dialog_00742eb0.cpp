#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
extern bool connection_wait_callback_0073c120();
// @ref ?connection_wait_callback_0073c120@@YA_NXZ=0073c120
extern char connection_url_007fe4e8[];
// @ref ?connection_url_007fe4e8@@3PADA=007fe4e8
extern char connection_url_007fe524[];
// @ref ?connection_url_007fe524@@3PADA=007fe524
extern char connection_url_007fe564[];
// @ref ?connection_url_007fe564@@3PADA=007fe564
extern char connection_url_007fe5a0[];
// @ref ?connection_url_007fe5a0@@3PADA=007fe5a0
extern char connection_url_007fe5d8[];
// @ref ?connection_url_007fe5d8@@3PADA=007fe5d8
extern char connection_url_007fe61c[];
// @ref ?connection_url_007fe61c@@3PADA=007fe61c
bool __fastcall Unknown_00742eb0()
{
    bool handled=false;
    char url[260];
    if(unknown_connection_result_b2ac10==(int)0x80040077 ||
       unknown_connection_result_b2ac10==(int)0x80040078 ||
       unknown_connection_result_b2ac10==(int)0x80040072 ||
       unknown_connection_result_b2ac10==(int)0x80040074 ||
       unknown_connection_result_b2ac10==(int)0x80040075 ||
       unknown_connection_result_b2ac10==(int)0x80040076) {
        handled=true;
        if(Message_Box_005c3230(unknown_connection_error_b2a8ec,4,connection_wait_callback_0073c120,false)==6) {
            int language=unknown_b2ac5c;
            switch(unknown_connection_result_b2ac10) {
            case (int)0x80040077: sprintf(url,connection_url_007fe61c,language); break;
            case (int)0x80040078: sprintf(url,connection_url_007fe5d8,language); break;
            case (int)0x80040072: sprintf(url,connection_url_007fe5a0,language); break;
            case (int)0x80040074: sprintf(url,connection_url_007fe564,language); break;
            case (int)0x80040075: sprintf(url,connection_url_007fe524,language); break;
            case (int)0x80040076: sprintf(url,connection_url_007fe4e8,language); break;
            }
            unknown_open_url_73c580(url,1);
        }
    } else {
        Message_Box_005c3230(unknown_connection_error_b2a8ec,0,connection_wait_callback_0073c120,false);
    }
    return handled;
}
