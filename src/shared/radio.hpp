// RadioClass: MissionClass with radio contact (Radio.cpp, 0x00636640-
// 0x0063702F; RTTI vtables 0x007A88E8 primary (153 slots), 0x007A88CC/
// 0x007A88C4/0x007A88BC). Layout (constructor 0x00636830): +0xBC three
// words (a CoordStruct; cleared), +0xC8 VectorClass<TechnoClass *> RadioLinks (1 entry).
// Slot 151 (0x00636A50) sends a radio message; names are hypotheses.
#ifndef RA2_SHARED_RADIO_HPP
#define RA2_SHARED_RADIO_HPP

#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/vector_class.hpp"
#include "shared/mission.hpp"

class TechnoClass;

// The message argument passed by the broadcast slots (0x00A40BE0).
extern int unknown_radio_param_a40be0;

class RadioClass : public MissionClass {
public:
    RadioClass();                                               // 0x00636830
    RadioClass(NoInitClass const &noinit);                      // 0x006368C0

    bool In_Radio_Contact() const;                              // 0x00636F10 (hypothesis)
    bool Unknown_00636EA0() const;                              // 0x00636EA0 (has an empty contact slot; hypothesis)
    TechnoClass *Contact_With_Whom(int index) const;            // 0x00636E20 (hypothesis)
    bool Unknown_00636ED0(TechnoClass *techno) const;           // 0x00636ED0 (in contact with techno; hypothesis)
    int Unknown_00636E70(TechnoClass *techno) const;            // 0x00636E70 (the techno's index among the contacts, or -1; hypothesis)
    bool Is_Radio_Contact(TechnoClass *techno) const;           // 0x00636E30 (techno is one of RadioLinks; hypothesis)
    virtual ~RadioClass() {}

    virtual HRESULT __stdcall Load(IStream *stream);            // slot 5 0x00636C60
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // slot 6 0x00636D20
    virtual void Detach(AbstractClass *target, bool all = true);    // slot 10 0x00636BA0
    virtual void Compute_CRC(WWCRCEngine &crc) const;           // slot 13 0x00636BF0
    virtual int unknown_slot95(RadioClass *radio, int message, long &param);   // slot 95 0x00636900

    virtual bool unknown_slot52();                               // slot 52 0x00636B60
    virtual int unknown_slot149(int message);                   // slot 149 0x00636D90 to the first contact
    virtual int unknown_slot150(int message, TechnoClass *techno);  // slot 150 0x00636B80
    virtual int unknown_slot151(int message, int *param, TechnoClass *techno);  // slot 151 0x00636A50 transmit
    virtual void unknown_slot152(int message);                  // slot 152 0x00636DC0 to every contact

    void Set_Radio_Count(int count);                            // 0x00636F40 (grows RadioLinks, clearing new entries; name hypothesis)
    TechnoClass *Contact(int index) const;                      // 0x00636E10
    TechnoClass *Contact2(int index) const;                     // 0x00636E20 (identical copy)

    CoordStruct unknown_bc;                 // +0xBC (cleared by the constructor)
    VectorClass<TechnoClass *> RadioLinks;  // +0xC8
};

#endif
