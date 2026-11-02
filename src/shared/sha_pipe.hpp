// SHAPipe: a pipe that computes the SHA-1 digest of the data put through it
// (Westwood's SHAPIPE.H).
//
// Base Pipe; slot 4 SHAPipe::Put 0x00675380 (vtable entry 0x007D9DA4).
// Result 0x006753B0 (CCINIClass digests, 0x0046979A).
#ifndef RA2_SHARED_SHA_PIPE_HPP
#define RA2_SHARED_SHA_PIPE_HPP

#include "shared/pipe.hpp"
#include "shared/sha.hpp"

class SHAPipe : public Pipe {
public:
    SHAPipe() {}
    virtual int Put(void const *source, int slen); // 0x00675380

    // Writes the digest of the data put so far; returns its size.
    int Result(void *result) const;                // 0x006753B0

protected:
    SHAEngine SHA;          // +0x0C
};

#endif
