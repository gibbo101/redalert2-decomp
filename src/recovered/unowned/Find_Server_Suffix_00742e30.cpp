#include "shared/wol_sink.hpp"
#include "shared/crt_string.hpp"
int __fastcall Find_Server_Suffix_00742e30(Wstring const &name)
{
    if(name.Length()!=0) {
        for(int i=1;i<unknown_servers_b2a700.length();++i) {
            WOL::Server *server=0;
            unknown_servers_b2a700.Get(server,i);
            char *separator=strchr(server->name,':');
            if(separator && *separator && name==(separator+1)) return i;
        }
    }
    return -1;
}
