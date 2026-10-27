#ifndef RA2_SHARED_UNKNOWN_CRC_STREAMS_HPP
#define RA2_SHARED_UNKNOWN_CRC_STREAMS_HPP
#include "shared/pipe.hpp"
#include "shared/straw.hpp"
#include "shared/ini_class.hpp"
// Uninstantiated CRC stream classes: names remain unresolved (no RTTI copy).
// Same-ECX qualified calls establish the Pipe/Straw prefix; inheritance is
// a hypothesis without RTTI. State offsets+C/+10/+14 identify the
// real CRCEngine prefix. No allocation, constructor or full-size claim here.
class UnknownCRCPipe : public Pipe {
public:
    virtual int Put(void const *source,int length);
    unsigned long Value_00494240();
    CRCEngine Engine;
};
class UnknownCRCStraw : public Straw {
public:
    virtual int Get(void *buffer,int length);
    unsigned long Value_004942d0();
    CRCEngine Engine;
};
#endif
