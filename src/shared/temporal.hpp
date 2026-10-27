// TemporalClass: a chrono-weapon erasing link (Temporal.cpp, 0x006E1E70-
// 0x006E2AA5; RTTI vtables 0x007AD320 primary, 0x007AD304 at +4, 0x007AD2FC,
// 0x007AD2F4). Layout from the constructors 0x006E1EF0 / 0x006E1F80 and
// Load 0x006E2110 (pointer fixups at +0x24, +0x28, +0x38, +0x3C, +0x40,
// +0x44); Size_Of 0x50, Kind_Of 0x46. Member names are placeholders except
// Owner (the constructor argument).
#ifndef RA2_SHARED_TEMPORAL_HPP
#define RA2_SHARED_TEMPORAL_HPP

#include "shared/abstract.hpp"
#include "shared/cd_timer.hpp"
#include "shared/vector_class.hpp"

#ifndef E_POINTER
#define E_POINTER ((HRESULT)0x80004003L)
#endif

extern "C" GUID const CLSID_TemporalClass;     // 0x007A1E20

class TemporalClass : public AbstractClass {
public:
    TemporalClass();                                            // 0x006E1EF0
    TemporalClass(AbstractClass *owner);                        // 0x006E1F80
    TemporalClass(NoInitClass const &noinit);                   // 0x006E2040
    virtual ~TemporalClass();                                   // 0x006E2080

    virtual HRESULT __stdcall GetClassID(GUID *classid);        // 0x006E21F0
    virtual HRESULT __stdcall Load(IStream *stream);            // 0x006E2110
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x006E21D0
    virtual int Kind_Of() const;                                // 0x006E2A10
    virtual int Size_Of() const;                                // 0x006E2A00
    virtual void Compute_CRC(WWCRCEngine &crc) const;           // 0x006E2100
    virtual void AI();                                          // 0x006E2230

    AbstractClass *Owner;                           // +0x24
    AbstractClass *Target;                          // +0x28
    CDTimerClass<FrameTimerClass> unknown_2c;       // +0x2C
    AbstractClass *unknown_38;                      // +0x38
    AbstractClass *unknown_3c;                      // +0x3C
    AbstractClass *unknown_40;                      // +0x40
    AbstractClass *unknown_44;                      // +0x44
    int unknown_48;                                 // +0x48
    int unknown_4c;                                 // +0x4C
};

extern DynamicVectorClass<TemporalClass *> unknown_TemporalClass_list_00ac02e0;   // 0x00AC02E0

#endif
