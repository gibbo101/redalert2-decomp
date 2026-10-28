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

    DynamicVectorClass<ConnectionListStruct *> Connections;   // +0x00
    bool unknown_18;                                          // +0x18
    void *RouterProcess;                                      // +0x1C (a process HANDLE)
};

extern OwnerTalkClass unknown_OwnerTalkClass_00ab6d18;     // 0x00AB6D18

#endif
