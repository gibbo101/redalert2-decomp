#include "shared/wol_sink.hpp"
extern char wol_buddy_separator_7e6f8c[];
// @ref ?wol_buddy_separator_7e6f8c@@3PADA=007e6f8c
void Unknown_00757380()
{
    int count=unknown_strings_b2a7d8.Count;
    if(count>10) count=10;
    else if(count==0) return;
    Wstring names;
    if(count>0) {
        int remaining=count;
        do {
            Wstring name;
            if(unknown_strings_b2a7d8.Count>0) {
                unknown_strings_b2a7d8.Get(name,0);
                unknown_strings_b2a7d8.Remove(0);
            }
            if(names.Length()>0) names+=wol_buddy_separator_7e6f8c;
            names+=name;
        } while(--remaining);
    }
    unknown_ladder_client_a72d00->Request(unknown_ladder_address_b29018,unknown_ladder_port_b2a8ac,names.Get(),unknown_protocol_7fd370 & 0xffff00,-1,0,0);
}
