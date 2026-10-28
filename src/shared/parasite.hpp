// ParasiteClass: a unit attached to a victim (Parasite.cpp, 0x00606120-
// 0x00607EE6; RTTI vtables 0x007A7C98 primary, 0x007A7C7C at +4, 0x007A7C74,
// 0x007A7C6C). Layout from the constructors 0x006061A0 / 0x00606240,
// Compute_CRC 0x00606460 and Load 0x00606540; Size_Of 0x58, Kind_Of 0x43.
// Member names are placeholders except Owner (constructor argument) and
// Victim (the object whose slot 60 the destructor calls).
#ifndef RA2_SHARED_PARASITE_HPP
#define RA2_SHARED_PARASITE_HPP

#include "shared/abstract.hpp"
#include "shared/cd_timer.hpp"
#include "shared/vector_class.hpp"

#ifndef E_POINTER
#define E_POINTER ((HRESULT)0x80004003L)
#endif

// The victim: an AbstractClass-derived object; only its slot 60 is called.
class ParasiteVictim : public AbstractClass {
public:
    virtual void unknown_slot24();
    virtual void unknown_slot25();
    virtual void unknown_slot26();
    virtual void unknown_slot27();
    virtual void unknown_slot28();
    virtual void unknown_slot29();
    virtual void unknown_slot30();
    virtual void unknown_slot31();
    virtual void unknown_slot32();
    virtual void unknown_slot33();
    virtual void unknown_slot34();
    virtual void unknown_slot35();
    virtual void unknown_slot36();
    virtual void unknown_slot37();
    virtual void unknown_slot38();
    virtual void unknown_slot39();
    virtual void unknown_slot40();
    virtual void unknown_slot41();
    virtual void unknown_slot42();
    virtual void unknown_slot43();
    virtual void unknown_slot44();
    virtual void unknown_slot45();
    virtual void unknown_slot46();
    virtual void unknown_slot47();
    virtual void unknown_slot48();
    virtual void unknown_slot49();
    virtual void unknown_slot50();
    virtual void unknown_slot51();
    virtual void unknown_slot52();
    virtual void unknown_slot53();
    virtual void unknown_slot54();
    virtual void unknown_slot55();
    virtual void unknown_slot56();
    virtual void unknown_slot57();
    virtual void unknown_slot58();
    virtual void unknown_slot59();
    virtual void unknown_slot60();              // slot 60 (+0xF0)
};

extern "C" GUID const CLSID_ParasiteClass;     // 0x007A1DF0
// Objects updated every frame (0x00AC0BF8; name hypothesis, see BulletClass).
extern DynamicVectorClass<AbstractClass *> unknown_abstracts_ac0bf8;

class ParasiteClass : public AbstractClass {
public:
    ParasiteClass();                                            // 0x006061A0
    ParasiteClass(AbstractClass *owner);                        // 0x00606240
    ParasiteClass(NoInitClass const &noinit);                   // 0x00606320
    virtual ~ParasiteClass();                                   // 0x00606370

    virtual HRESULT __stdcall GetClassID(GUID *classid);        // 0x00606660
    virtual HRESULT __stdcall Load(IStream *stream);            // 0x00606540
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x00606640
    virtual void Detach(AbstractClass *target, bool all);       // 0x00607200
    virtual int Kind_Of() const;                                // 0x00607DE0
    virtual int Size_Of() const;                                // 0x00607DD0
    virtual void Compute_CRC(WWCRCEngine &crc) const;           // 0x00606460
    virtual void AI();                                          // 0x00606F50
    void Unknown_006064C0();                                    // 0x006064C0 (the destructor's release steps)
    void Unknown_00607440();                                    // 0x00607440 (FootClass slot 82 after restarting the +0x2C timer)

    AbstractClass *Owner;                           // +0x24
    AbstractClass *unknown_28;                      // +0x28
    CDTimerClass<FrameTimerClass> unknown_2c;       // +0x2C
    CDTimerClass<FrameTimerClass> unknown_38;       // +0x38
    ParasiteVictim *Victim;                         // +0x44
    int unknown_48;                                 // +0x48
    int unknown_4c;                                 // +0x4C
    int unknown_50;                                 // +0x50
    bool unknown_54;                                // +0x54 listed in unknown_abstracts_ac0bf8
};

extern DynamicVectorClass<ParasiteClass *> unknown_ParasiteClass_list_00a76430;   // 0x00A76430

#endif
