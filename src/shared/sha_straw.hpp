// SHAStraw: a straw that computes the SHA-1 digest of the data drawn through
// it (Westwood's SHASTRAW.H).
//
// Vtable 0x007A647C (base Straw): slot 0 scalar deleting destructor
// 0x00595D40, slot 1 Straw::Get_From 0x0069B050, slot 2 SHAStraw::Get
// 0x006753C0. Result 0x00675400.
#ifndef RA2_SHARED_SHA_STRAW_HPP
#define RA2_SHARED_SHA_STRAW_HPP

#include "shared/straw.hpp"
#include "shared/sha.hpp"

class SHAStraw : public Straw {
public:
    SHAStraw() : IsDisabled(false) {}
    virtual int Get(void *source, int slen);       // 0x006753C0

    // Writes the digest of the data drawn so far; returns its size.
    int Result(void *result) const;                // 0x00675400

protected:
    bool IsDisabled;        // +0x0C digest not updated while set
    SHAEngine SHA;          // +0x10
};

#endif
