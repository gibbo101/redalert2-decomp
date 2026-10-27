// TEventClass: one event of a trigger type (TEvent.cpp, unit 0x006E5B70;
// RTTI vtables 0x007AD700 primary, 0x007AD6E4 IRTTITypeInfo at +4).
// Partial layout (from the constructor 0x006E5DE0 and its users in
// TriggerType.cpp; names are hypotheses):
//   +0x24  int (-1), +0x28 TEventClass *Next, +0x2C int Type,
//   +0x30  AbstractTypeClass *unknown_30 (an object type named by the
//          entry, written by its ID), +0x34 int Data
//   size 0x38 (slot 12)
#ifndef RA2_SHARED_TEVENT_HPP
#define RA2_SHARED_TEVENT_HPP

#include "shared/abstract_type.hpp"

extern "C" GUID const CLSID_TEventClass;        // 0x007A1D80
// The type named (0x006BF260; hypothesis: TeamTypeClass::From_Name).
AbstractTypeClass *__fastcall Unknown_006BF260(char const *name);

class TEventClass : public AbstractClass {
public:
    TEventClass();                                                      // 0x006E5DE0
    TEventClass(NoInitClass const &noinit) : AbstractClass(noinit) {}
    virtual ~TEventClass();                                             // 0x006E5F40

    virtual HRESULT __stdcall GetClassID(GUID *clsid);                  // 0x006E6C20 slot 3
    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x006E6C60 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x006E6CD0 slot 6
    virtual void Detach(AbstractClass *target, bool all = true);        // 0x006E6BA0 slot 10
    virtual int Kind_Of() const;                                        // 0x006E6D80 slot 11
    virtual int Size_Of() const;                                        // 0x006E6D70 slot 12
    virtual void Compute_CRC(WWCRCEngine &crc) const;                   // 0x006E6BC0 slot 13
    virtual int unknown_slot16() const;                                 // 0x006E6D90

    void Build_INI_Entry(char *buffer) const;                           // 0x006E68B0 (appends "type,kind,value")
    void Read_INI();                                                    // 0x006E6900 (the next strtok fields)
    bool unknown_func_6e6d50() const;                                   // 0x006E6D50 (false for types 1, 6, 0x2C)
    static int __fastcall Event_Flags(int type);                        // 0x006E6A30 (hypothesis)

    int unknown_24;                         // +0x24
    TEventClass *Next;                      // +0x28
    int Type;                               // +0x2C
    AbstractTypeClass *unknown_30;          // +0x30
    int Data;                               // +0x34
};

// Every event (0x00AC0808; defined in this unit).
extern DynamicVectorClass<TEventClass *> unknown_TEventClass_list_00ac0808;

#endif
