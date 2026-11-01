// OwnerTalkClass (RTTI name of the list element's owner; the class itself has
// no vtable): the router connection owner of the unit at 0x0063ED70. One
// global object, 0x00AB6D18 (0x20 bytes; initializer 0x0063EF60, atexit
// destructor 0x0063EFB0). The list of connections is its first member
// (vtable 0x007A8FEC is DynamicVectorClass<OwnerTalkClass::ConnectionListStruct *>);
// the destructor deletes every connection. +0x1C is the router process handle
// (Wait_For_Router_Shutdown 0x0063FD70, from its debug text). Names of the
// list and +0x18 are hypotheses.
#ifndef RA2_SHARED_OWNER_TALK_HPP
#define RA2_SHARED_OWNER_TALK_HPP

#include "shared/vector_class_decl.hpp"

class IPXAddressClass;

class OwnerTalkClass {
public:
    struct ConnectionListStruct {
        int unknown_00;
    };

    OwnerTalkClass() : unknown_18(false), RouterProcess(0) {}
    ~OwnerTalkClass()
    {
        while (Connections.Count()) {
            delete Connections[0];
            Connections.Delete(0);
        }
    }

    // Waits up to timeout for the router process to end; on a timeout gives
    // up (false) or, with force, terminates it (0x0063FD70).
    bool Wait_For_Router_Shutdown(unsigned long timeout, bool force);

    // Whether a connection with this ID is flagged (0x0063F4C0; hypothesis).
    unsigned char Unknown_0063F4C0(int id);
    void Unknown_0063FC90();
    void Unknown_0063F070();                                // 0x0063F070 (empties the list; also UnknownOwnedList_0063f070::unknown_clear)
    char *Unknown_0063FB40(int index);                      // 0x0063FB40 (a connection's name)
    IPXAddressClass *Unknown_0063FA00(char *name);          // 0x0063FA00 (the address of a named connection)
    int Unknown_0063FBA0();                                 // 0x0063FBA0 (the next game host, -1: none; ABOUTTOEXIT)
    bool Unknown_0063F130();                                // 0x0063F130 (the new host takes over the router; ABOUTTOEXIT; Create_Connections tests the result)
    void Unknown_0063F2A0();                                // 0x0063F2A0 (Create_Connections, packet-router games)
    bool Unknown_0063F510(unsigned char *address);          // 0x0063F510 (starts mph.exe for this IP, null: the first player's or ours, and waits for TALK_HELLO; Create_Connections with 0)
    void Unknown_0063F9A0(int id, IPXAddressClass *address);   // 0x0063F9A0 (a player's new address; ADDRESSCHANGE)
    void Unknown_0063FE20(int id);                          // 0x0063FE20 (a removed player; REMOVEPLAYER)
    unsigned short Unknown_0063FAF0(char *name);            // 0x0063FAF0 (the id of a named connection)                // 0x0063FC90 (MPCooperative slot 37, when the flagged connection exists)

    DynamicVectorClass<ConnectionListStruct *> Connections;   // +0x00
    bool unknown_18;                                          // +0x18
    void *RouterProcess;                                      // +0x1C (a process HANDLE)
};

extern OwnerTalkClass unknown_OwnerTalkClass_00ab6d18;     // 0x00AB6D18

#endif
