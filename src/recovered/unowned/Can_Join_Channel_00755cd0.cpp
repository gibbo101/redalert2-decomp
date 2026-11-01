int __fastcall Channel_Version_00737af0();
#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/string_table.hpp"
#include "shared/crt_string.hpp"
// The existing parser's final4-byte string slot is a Wstring: the caller constructs and destroys it.
#include "shared/wol_list_text.hpp"
unsigned int Unknown_0073cfd0();
extern int unknown_own_squad_b2abfc;
extern char wol_nosquad_label_7ffb44[];
extern char wol_channel_full_label_7ffb34[];
extern char wol_observers_label_7e6cdc[];
extern char wol_wrong_version_label_7e21ac[];
extern char wol_source_file_007fd62c[];
// @ref ?unknown_own_squad_b2abfc@@3HA=00b2abfc
// @ref ?wol_nosquad_label_7ffb44@@3PADA=007ffb44
// @ref ?wol_channel_full_label_7ffb34@@3PADA=007ffb34
// @ref ?wol_observers_label_7e6cdc@@3PADA=007e6cdc
// @ref ?wol_wrong_version_label_7e21ac@@3PADA=007e21ac
// @ref ?wol_source_file_007fd62c@@3PADA=007fd62c
bool __fastcall Can_Join_Channel_00755cd0(WOL::Channel const *channel,bool notify,bool observer)
{
    bool ladder=Unknown_0073c3e0(channel)||Unknown_0073c400(channel);
    int online=Is_Online_Session();
    if(ladder!=online) return false;
    if(Unknown_0073c3c0(channel) && unknown_own_squad_b2abfc<1) {
        if(notify) Unknown_005C2C80(-1,StringTable::Load_String(wol_nosquad_label_7ffb44,0,wol_source_file_007fd62c,0x5fe7));
        return false;
    }
    char info[132];
    strcpy(info,channel->exInfo);
    int version=0;
    int checksum=0;
    int reserved=0;
    int observers=0;
    int allow_observers=0;
    Wstring name;
    Parse_Channel_Info_0073d070(info,&version,&checksum,&reserved,&observers,&allow_observers,&name);
    if(Channel_Version_00737af0()==version && Unknown_0073cfd0()==(unsigned int)checksum) {
        if(!observer) {
            int occupancy=((int)channel->currentUsers-observers)+reserved;
            int observer_slot=(observers==0 && allow_observers==0)?0:1;
            if(occupancy>=(int)channel->maxUsers-observer_slot) {
                if(notify) Unknown_005C2C80(-1,StringTable::Load_String(wol_channel_full_label_7ffb34,0,wol_source_file_007fd62c,0x6016));
            } else return true;
        } else {
            if(allow_observers==0 || observers!=0) {
                if(notify) Unknown_005C2C80(-1,StringTable::Load_String(wol_observers_label_7e6cdc,0,wol_source_file_007fd62c,0x601e));
            } else return true;
        }
    } else if(notify) {
        Unknown_005C2C80(-1,StringTable::Load_String(wol_wrong_version_label_7e21ac,0,wol_source_file_007fd62c,0x600b));
    }
    return false;
}
