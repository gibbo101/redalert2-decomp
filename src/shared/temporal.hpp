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
    TemporalClass(TechnoClass *owner);                          // 0x006E1F80
    TemporalClass(NoInitClass const &noinit);                   // 0x006E2040
    virtual ~TemporalClass();                                   // 0x006E2080

    virtual HRESULT __stdcall GetClassID(GUID *classid);        // 0x006E21F0
    virtual HRESULT __stdcall Load(IStream *stream);            // 0x006E2110
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x006E21D0
    virtual int Kind_Of() const;                                // 0x006E2A10
    virtual int Size_Of() const;                                // 0x006E2A00
    virtual void Compute_CRC(WWCRCEngine &crc) const;           // 0x006E2100
    virtual void AI();                                          // 0x006E2230

    // Names after YRpp's TemporalClass (hypotheses). The warp per step is the owner's current
    // weapon damage; each helper chained at +0x44 adds its own (at most 50 deep).
    int Get_Warp_Per_Step(int step);                            // 0x006E2470
    void Detach_Techno(TechnoClass *target);                    // 0x006E24C0 (the owner or the target died)
    void Let_Go_Of_Target();                                    // 0x006E2500
    void Unknown_006E2610();                         // 0x006E2610 clears target warp state
    void Unknown_006E27B0(TechnoClass *target);           // 0x006E27B0 assigns a warp target
    void Let_Go();                                              // 0x006E2680 (and the helpers chained to it)
    void Just_Let_Go();                                         // 0x006E2710
    bool Can_Warp_Target(TechnoClass *target) const;            // 0x006E2770

    TechnoClass *Owner;                             // +0x24 the firer
    TechnoClass *Target;                            // +0x28 the techno being erased
    CDTimerClass<FrameTimerClass> unknown_2c;       // +0x2C
    AbstractClass *unknown_38;                      // +0x38
    AbstractClass *unknown_3c;                      // +0x3C
    TemporalClass *unknown_40;                      // +0x40 the previous link on the same target
    TemporalClass *unknown_44;                      // +0x44 the next link (a helper)
    int unknown_48;                                 // +0x48
    int unknown_4c;                                 // +0x4C the warp per step (Get_Warp_Per_Step)
};

extern DynamicVectorClass<TemporalClass *> unknown_TemporalClass_list_00ac02e0;   // 0x00AC02E0

#endif
