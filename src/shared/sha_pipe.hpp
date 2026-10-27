// SHAPipe: a Pipe that feeds everything put to it into an SHAEngine (and
// passes it on). Vtable 0x0079D994 (no RTTI locator). Layout from the inline
// constructor in CCINIClass::Calculate_Message_Digest (0x0046C260):
//   +0x00 Pipe (vtable, ChainTo, ChainFrom)
//   +0x0C SHAEngine SHA
// The destructor is implicit (only Pipe::~Pipe 0x0060EA60 is called).
#ifndef SHARED_SHA_PIPE_HPP
#define SHARED_SHA_PIPE_HPP

#include "shared/pipe.hpp"
#include "shared/sha.hpp"

class SHAPipe : public Pipe {
public:
    virtual int Put(void const *source, int length);
    // Writes the 20-byte digest of everything put so far (0x006753B0).
    int Result(void *result) const;

protected:
    SHAEngine SHA;      // +0x0C
};

#endif
