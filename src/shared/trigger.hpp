// TriggerClass: a live scenario trigger (Trigger.cpp; RTTI vtables
// 0x007AD9E0 primary (24 slots), 0x007AD9C4 IRTTITypeInfo at +4,
// 0x007AD9BC INoticeSink, 0x007AD9B4 INoticeSource).
//
// Layout (from the constructor 0x006ED220; names are hypotheses):
//   +0x00  AbstractClass (0x24)
//   +0x24  TriggerTypeClass *Class, +0x28 TriggerClass *Next (a tag's
//          chain), +0x2C bool (queued for removal)
//   +0x30  CDTimerClass<FrameTimerClass> Timer
//   +0x3C  int Events (one bit per event of the type; set when it fired)
//   +0x40  bool IsEnabled (true)
//   size 0x44
// Every trigger is added to Triggers (0x00A40AA0) and the abstract lists
// 0x00AC0CB0 and 0x00AC0D48.
#ifndef RA2_SHARED_TRIGGER_HPP
#define RA2_SHARED_TRIGGER_HPP

#include "shared/trigger_type.hpp"
#include "shared/cd_timer.hpp"

class ObjectClass;

inline int Scenario_Difficulty()
{
    return unknown_id_source_a3d290->Difficulty;
}

extern "C" GUID const CLSID_TriggerClass;       // 0x007A1D50

class TriggerClass : public AbstractClass {
public:
    TriggerClass(TriggerTypeClass *type);                               // 0x006ED220
    TriggerClass(NoInitClass const &noinit) : AbstractClass(noinit), Timer(noinit) {}
    virtual ~TriggerClass();                                            // (scalar deleting 0x006EDBA0)

    virtual HRESULT __stdcall GetClassID(GUID *clsid);                  // 0x006EDA90 slot 3
    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x006EDAD0 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x006EDB40 slot 6
    virtual void Detach(AbstractClass *target, bool all = true);        // 0x006ED900 slot 10
    virtual int Kind_Of() const;                                        // 0x006EDB90 slot 11
    virtual int Size_Of() const;                                        // 0x006EDB80 slot 12
    virtual void Compute_CRC(WWCRCEngine &crc) const;                   // 0x006EDA00 slot 13

    bool unknown_func_6ed4d0() const;                                   // 0x006ED4D0 (chain: TriggerTypeClass::unknown_func_6ee1b0)
    bool unknown_func_6ed510() const;                                   // 0x006ED510 (chain: unknown_func_6ee180)
    bool unknown_func_6ed550() const;                                   // 0x006ED550 (this and next: unknown_func_6ee1e0)
    bool unknown_func_6ed590() const;                                   // 0x006ED590 (this and next: unknown_func_6ee210)
    bool unknown_func_6ed5d0(int value) const;                          // 0x006ED5D0 (this and next: unknown_func_6ee240)
    void unknown_func_6ed620(int value);                                // 0x006ED620 (resets the chain's triggers that answer 0x006EE240)
    void unknown_func_6ed650(int value);                                // 0x006ED650 (resets the chain's triggers that answer 0x006EE280)
    void Reset();                                                       // 0x006ED680 (restarts the timed events)
    void Mark_Event(int index);                                         // 0x006ED930
    void Clear_Event(int index);                                        // 0x006ED950
    bool Is_Event_Marked(int index) const;                              // 0x006ED970
    void unknown_func_6ed990();                                         // 0x006ED990 (queue for removal)
    bool unknown_func_6ed9f0() const;                                   // 0x006ED9F0
    void Enable();                                                      // 0x006EDB60
    void Disable();                                                     // 0x006EDB70
    static TriggerClass *__fastcall Find_Or_Make(TriggerTypeClass *type);   // 0x006ED8A0
    // Springs on event unless already sprung or disabled; forced skips the event tests (0x006ED740;
    // TS's TriggerClass::Spring; persistent comes from the tag type, source is passed to the events).
    bool Spring(int event, ObjectClass *object, bool forced, bool persistent, int source);
    // Runs every action of the type for object at cell in the type's house; true when any acted
    // (0x006ED830; YRpp's FireActions, name hypothesis).
    bool Fire_Actions(ObjectClass *object, Cell cell);

    TriggerTypeClass *Class;                // +0x24
    TriggerClass *Next;                     // +0x28
    bool unknown_2c;                        // +0x2C
    CDTimerClass<FrameTimerClass> Timer;    // +0x30
    int Events;                             // +0x3C
    bool IsEnabled;                         // +0x40
};

// Every trigger (0x00A40AA0; defined in the globals unit).
extern DynamicVectorClass<TriggerClass *> unknown_TriggerClass_list_00a40aa0;

#endif
