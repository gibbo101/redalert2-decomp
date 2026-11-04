#include "shared/wol_sink.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/winsock_interface.hpp"
#include "shared/debug_printf.hpp"
#include "shared/crt_string.hpp"
extern "C" int __cdecl sscanf(char const *,char const *,...);
typedef int (WINAPI *AddressFarProc)();
WIN32_IMPORT HINSTANCE WINAPI LoadLibraryA(char const *name);
WIN32_IMPORT BOOL WINAPI FreeLibrary(HINSTANCE module);
WIN32_IMPORT AddressFarProc WINAPI GetProcAddress(HINSTANCE module,char const *name);

// Winsock IN_ADDR: exact four-byte SDK union, with named octets.
struct in_addr {
    union {
        struct { unsigned char s_b1,s_b2,s_b3,s_b4; } S_un_b;
        struct { unsigned short s_w1,s_w2; } S_un_w;
        unsigned long S_addr;
    } S_un;
};

// RTTI already names VectorClass<tConnInfoStruct *>; the20B record is
// written column-by-column from the TCP connection MIB in this routine.
class tConnInfoStruct {
public:
    long State;
    unsigned long LocalAddress;
    unsigned short LocalPort;
    unsigned long RemoteAddress;
    unsigned short RemotePort;
};
// SNMP ABI types, checked against Microsoft snmp.h documentation and
// original8B list/24B binding allocations. No reference implementation copied.
struct AsnObjectIdentifier { unsigned int idLength; unsigned int *ids; };
struct AsnOctetString { unsigned char *stream; unsigned int length; BOOL dynamic; };
struct AsnCounter64 { unsigned long low,high; };
struct AsnAny {
    unsigned char asnType;
    union {
        long number;
        unsigned long unsigned32;
        AsnCounter64 counter64;
        AsnOctetString string;
        AsnObjectIdentifier object;
        AsnOctetString address;
    } asnValue;
};
struct SnmpVarBind { AsnObjectIdentifier name; AsnAny value; };
struct SnmpVarBindList { SnmpVarBind *list; unsigned int len; };
typedef BOOL (WINAPI *AddressSnmpInit)(DWORD,HANDLE *,AsnObjectIdentifier *);
typedef BOOL (WINAPI *AddressSnmpQuery)(unsigned char,SnmpVarBindList *,long *,long *);
typedef void *(WINAPI *AddressSnmpAlloc)(unsigned int);
typedef void (WINAPI *AddressSnmpFree)(void *);
extern "C" {
    extern AddressSnmpInit address_snmp_init_b2a754;
    extern AddressSnmpQuery address_snmp_query_b294b0;
    extern AddressSnmpAlloc address_snmp_alloc_b2a718;
    extern AddressSnmpFree address_snmp_free_b2a8dc;
}
// @ref _address_snmp_init_b2a754=00b2a754
// @ref _address_snmp_query_b294b0=00b294b0
// @ref _address_snmp_alloc_b2a718=00b2a718
// @ref _address_snmp_free_b2a8dc=00b2a8dc
extern char address_text_007ce9bc[];
// @ref ?address_text_007ce9bc@@3PADA=007ce9bc
extern char address_text_007e6554[];
// @ref ?address_text_007e6554@@3PADA=007e6554
extern char address_text_007ff468[];
// @ref ?address_text_007ff468@@3PADA=007ff468
extern char address_text_007ff488[];
// @ref ?address_text_007ff488@@3PADA=007ff488
extern char address_text_007ff4bc[];
// @ref ?address_text_007ff4bc@@3PADA=007ff4bc
extern char address_text_007ff4e8[];
// @ref ?address_text_007ff4e8@@3PADA=007ff4e8
extern char address_text_007ff514[];
// @ref ?address_text_007ff514@@3PADA=007ff514
extern char address_text_007ff530[];
// @ref ?address_text_007ff530@@3PADA=007ff530
extern char address_text_007ff54c[];
// @ref ?address_text_007ff54c@@3PADA=007ff54c
extern char address_text_007ff588[];
// @ref ?address_text_007ff588@@3PADA=007ff588
extern char address_text_007ff5c0[];
// @ref ?address_text_007ff5c0@@3PADA=007ff5c0
extern char address_text_007ff5e8[];
// @ref ?address_text_007ff5e8@@3PADA=007ff5e8
extern char address_text_007ff60c[];
// @ref ?address_text_007ff60c@@3PADA=007ff60c
extern char address_text_007ff628[];
// @ref ?address_text_007ff628@@3PADA=007ff628
extern char address_text_007ff644[];
// @ref ?address_text_007ff644@@3PADA=007ff644
extern char address_text_007ff654[];
// @ref ?address_text_007ff654@@3PADA=007ff654
extern char address_text_007ff668[];
// @ref ?address_text_007ff668@@3PADA=007ff668
extern char address_text_007ff67c[];
// @ref ?address_text_007ff67c@@3PADA=007ff67c
extern char address_text_007ff690[];
// @ref ?address_text_007ff690@@3PADA=007ff690
extern char address_text_007ff6ac[];
// @ref ?address_text_007ff6ac@@3PADA=007ff6ac
extern char address_text_007ff6b8[];
// @ref ?address_text_007ff6b8@@3PADA=007ff6b8
extern char address_text_007ff6d4[];
// @ref ?address_text_007ff6d4@@3PADA=007ff6d4
extern char address_text_007ff6f4[];
// @ref ?address_text_007ff6f4@@3PADA=007ff6f4
extern char address_text_007ff704[];
// @ref ?address_text_007ff704@@3PADA=007ff704
extern char address_text_007ff720[];
// @ref ?address_text_007ff720@@3PADA=007ff720
extern char address_text_007ff740[];
// @ref ?address_text_007ff740@@3PADA=007ff740
extern char address_text_007ff760[];
// @ref ?address_text_007ff760@@3PADA=007ff760
extern char address_text_007ff778[];
// @ref ?address_text_007ff778@@3PADA=007ff778
extern char address_text_007ff798[];
// @ref ?address_text_007ff798@@3PADA=007ff798

bool __fastcall Find_Local_Address_0074fcb0(IPXAddressClass *address)
{
    DynamicVectorClass<tConnInfoStruct *> connections;
    int server_port=0;
    NetNumType network;
    NetNodeType node;
    if(unknown_irc_index_b292d8<1 || unknown_irc_index_b292d8>=unknown_servers_b2a700.Count) return false;
    Debug_Printf(address_text_007ff798);
    WOL::Server *server=0;
    unknown_servers_b2a700.Get(server,unknown_irc_index_b292d8);
    char hostname[128];
    memset(hostname,0,sizeof(hostname));
    strncpy(hostname,server->connection+4,128);
    char *port=strchr(hostname,';');
    if(port) {
        *port=0;
        sscanf(port+1,address_text_007ce9bc,&server_port);
        Debug_Printf(address_text_007ff778,hostname);
        Debug_Printf(address_text_007ff760,server_port);
        Debug_Printf(address_text_007ff740);
        hostent *host=gethostbyname(hostname);
        if(!host) { Debug_Printf(address_text_007e6554,WSAGetLastError());return false; }
        in_addr remote_address;
        remote_address=*(in_addr *)host->h_addr_list[0];
        remote_address.S_un.S_addr=ntohl(remote_address.S_un.S_addr);
        Debug_Printf(address_text_007ff720,remote_address.S_un.S_un_b.s_b4,remote_address.S_un.S_un_b.s_b3,remote_address.S_un.S_un_b.s_b2,remote_address.S_un.S_un_b.s_b1);
        Debug_Printf(address_text_007ff704);
        HINSTANCE extension=LoadLibraryA(address_text_007ff6f4);
        if(!extension) { Debug_Printf(address_text_007ff6d4);return false; }
        Debug_Printf(address_text_007ff6b8);
        HINSTANCE utility=LoadLibraryA(address_text_007ff6ac);
        if(!utility) { Debug_Printf(address_text_007ff690);FreeLibrary(extension);return false; }
        address_snmp_init_b2a754=(AddressSnmpInit)GetProcAddress(extension,address_text_007ff67c);
        address_snmp_query_b294b0=(AddressSnmpQuery)GetProcAddress(extension,address_text_007ff668);
        address_snmp_alloc_b2a718=(AddressSnmpAlloc)GetProcAddress(utility,address_text_007ff654);
        address_snmp_free_b2a8dc=(AddressSnmpFree)GetProcAddress(utility,address_text_007ff644);
        if(!address_snmp_init_b2a754 || !address_snmp_query_b294b0 || !address_snmp_alloc_b2a718 || !address_snmp_free_b2a8dc) {
            Debug_Printf(address_text_007ff488);FreeLibrary(utility);FreeLibrary(extension);return false;
        }
        SnmpVarBindList *list=(SnmpVarBindList *)address_snmp_alloc_b2a718(sizeof(SnmpVarBindList));
        SnmpVarBind *binding=(SnmpVarBind *)address_snmp_alloc_b2a718(sizeof(SnmpVarBind));
        Debug_Printf(address_text_007ff628);
        HANDLE event;
        AsnObjectIdentifier first_region;
        if(!address_snmp_init_b2a754(GetTickCount(),&event,&first_region)) {
            Debug_Printf(address_text_007ff60c);address_snmp_free_b2a8dc(list);address_snmp_free_b2a8dc(binding);
            FreeLibrary(utility);FreeLibrary(extension);return false;
        }
        unsigned int tcp_connection_oid[10]={1,3,6,1,2,1,6,13,1,1};
        unsigned int *oid_copy=(unsigned int *)address_snmp_alloc_b2a718(sizeof(tcp_connection_oid));
        memcpy(oid_copy,tcp_connection_oid,sizeof(tcp_connection_oid));
        // The original still points the query at the stack OID, not its copy.
        binding->name.idLength=10;
        binding->name.ids=tcp_connection_oid;
        list->list=binding;
        list->len=1;
        int previous_column=1;
        int row=0;
        long error_status,error_index;
        while(true) {
            if(!address_snmp_query_b294b0(0xa1,list,&error_status,&error_index)) {
                // The failure path frees these two objects and leaves oid_copy allocated.
                Debug_Printf(address_text_007ff5e8);
                address_snmp_free_b2a8dc(list);address_snmp_free_b2a8dc(binding);
                FreeLibrary(utility);FreeLibrary(extension);
                return false;
            }
            if(binding->name.idLength<10) break;
            int column=binding->name.ids[9];
            if(previous_column!=column) {row=0;previous_column=column;}
            switch(column) {
            case 1: {
                    tConnInfoStruct *connection=new tConnInfoStruct;
                    connection->State=binding->value.asnValue.number;
                    connections.Add(connection);
                } break;
            case 2: connections[row]->LocalAddress=*(unsigned long *)binding->value.asnValue.address.stream;++row;break;
            case 3: connections[row]->LocalPort=(unsigned short)binding->value.asnValue.number;++row;break;
            case 4: connections[row]->RemoteAddress=*(unsigned long *)binding->value.asnValue.address.stream;++row;break;
            case 5: connections[row]->RemotePort=(unsigned short)binding->value.asnValue.number;++row;break;
            }
        }

        address_snmp_free_b2a8dc(list);address_snmp_free_b2a8dc(binding);address_snmp_free_b2a8dc(oid_copy);
        Debug_Printf(address_text_007ff5c0,connections.Count());
        bool found=false;
        if(connections.Count()) {
            do {
                tConnInfoStruct *connection=connections[0];
                in_addr endpoint;
                endpoint.S_un.S_addr=ntohl(connection->RemoteAddress);
                if(!found && memcmp(&endpoint,&remote_address,sizeof(endpoint))==0) {
                    Debug_Printf(address_text_007ff588);
                    if(server_port && server_port!=connection->RemotePort) {
                        Debug_Printf(address_text_007ff54c,connection->RemotePort,server_port);
                    } else {
                        Debug_Printf(address_text_007ff530);
                        if(connection->State==5) {
                            Debug_Printf(address_text_007ff514);
                            *(unsigned long *)node=connection->LocalAddress;
                            address->Set_Address(network,node,connection->LocalPort);
                            found=true;
                        } else Debug_Printf(address_text_007ff4e8);
                    }
                }
                delete connections[0];
                connections.Delete(0);
            }while(connections.Count());
            if(found) Debug_Printf(address_text_007ff4bc,address->As_String_00523840());
        }
        FreeLibrary(utility);FreeLibrary(extension);
        return found;
    } else Debug_Printf(address_text_007ff468);
    return false;
}

// Actual original constructor call and RTTI-backed container vptrs.
// @ref ??0?$VectorClass@PAVtConnInfoStruct@@@@QAE@IPBQAVtConnInfoStruct@@@Z=007680c0
// @ref ??_7?$DynamicVectorClass@PAVtConnInfoStruct@@@@6B@=007af984
// @ref ??_7?$VectorClass@PAVtConnInfoStruct@@@@6B@=007af964

// All original virtual targets, read from the two original seven-slot tables.
// @ref ??_E?$DynamicVectorClass@PAVtConnInfoStruct@@@@UAEPAXI@Z=00766850
// @ref ??8?$VectorClass@PAVtConnInfoStruct@@@@UBE_NABV0@@Z=00766520
// @ref ?Resize@?$DynamicVectorClass@PAVtConnInfoStruct@@@@UAE_NHPBQAVtConnInfoStruct@@@Z=007666a0
// @ref ?Clear@?$DynamicVectorClass@PAVtConnInfoStruct@@@@UAEXXZ=00765e00
// @ref ?ID@?$DynamicVectorClass@PAVtConnInfoStruct@@@@UAEHABQAVtConnInfoStruct@@@Z=00766750
// @ref ?ID@?$DynamicVectorClass@PAVtConnInfoStruct@@@@UAEHPBQAVtConnInfoStruct@@@Z=00765e30
// @ref ?Fetch@?$VectorClass@PAVtConnInfoStruct@@@@UBEPAVtConnInfoStruct@@H@Z=00765e50
// @ref ??_E?$VectorClass@PAVtConnInfoStruct@@@@UAEPAXI@Z=00766800
// @ref ?Resize@?$VectorClass@PAVtConnInfoStruct@@@@UAE_NHPBQAVtConnInfoStruct@@@Z=00766560
// @ref ?Clear@?$VectorClass@PAVtConnInfoStruct@@@@UAEXXZ=00766610
// @ref ?ID@?$VectorClass@PAVtConnInfoStruct@@@@UAEHABQAVtConnInfoStruct@@@Z=00766640
// @ref ?ID@?$VectorClass@PAVtConnInfoStruct@@@@UAEHPBQAVtConnInfoStruct@@@Z=00766680
