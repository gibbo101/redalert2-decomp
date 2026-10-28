// RadSiteClass: a radiation site (RadSite.cpp, 0x00637220-0x00637FAB; RTTI
// vtables 0x007A8BD0 primary, 0x007A8BB4 at +4, 0x007A8BAC, 0x007A8BA4).
//
// Layout (constructor 0x006372A0, NoInit constructor 0x00637360, destructor
// 0x006373B0, Size_Of 0x74). Every site is listed in
// unknown_RadSiteClass_list_00ab6620 (defined with the unit's header statics).
// Field names are hypotheses from the accessors.
#ifndef RA2_SHARED_RADSITE_HPP
#define RA2_SHARED_RADSITE_HPP

#include "shared/abstract.hpp"
#include "shared/cd_timer.hpp"
#include "shared/vector_class.hpp"

#include "shared/coord.hpp"

// The light source a site owns (+0x24): shared/light_source.hpp.
#include "shared/light_source.hpp"

// The map's cell lookup and the one cell call RadSite makes.
class RadSiteClass;
class RadSiteCell {
public:
    virtual void unknown_slot0();
    virtual void unknown_slot1();
    virtual void unknown_slot2();
    virtual void unknown_slot3();
    virtual void unknown_slot4();
    virtual void unknown_slot5();
    virtual void unknown_slot6();
    virtual void unknown_slot7();
    virtual void unknown_slot8();
    virtual void unknown_slot9();
    virtual void unknown_slot10();
    virtual void unknown_slot11();
    virtual void unknown_slot12();
    virtual void unknown_slot13();
    virtual void unknown_slot14();
    virtual void unknown_slot15();
    virtual void unknown_slot16();
    virtual void unknown_slot17();
    virtual CoordStruct Center_Coord() const;   // slot 18 (+0x48)

    RadSiteClass *Unknown_0047CE40();           // 0x0047CE40 the cell's radiation site, or 0
    void Unknown_0047CE30(RadSiteClass *site);  // 0x0047CE30 sets it
    void Unknown_0047CEA0(double level);        // 0x0047CEA0 sets its radiation level (hypothesis)
    void Unknown_0047CEC0(double level);        // 0x0047CEC0 lowers its radiation level (hypothesis)
};

// The rules (0x00839848) are `Rules`: shared/rules.hpp.
#include "shared/rules.hpp"

// Removes every reference to object (0x006ECB90, __fastcall; name hypothesis).
void __fastcall Detach_This_From_All(AbstractClass *object, bool all);

extern "C" GUID const CLSID_RadSiteClass;       // 0x007A1E10

#ifndef E_POINTER
#define E_POINTER ((HRESULT)0x80004003L)
#endif

class RadSiteClass : public AbstractClass {
public:
    RadSiteClass();                                             // 0x006372A0
    RadSiteClass(NoInitClass const &noinit);                    // 0x00637360
    virtual ~RadSiteClass();                                    // 0x006373B0

    virtual HRESULT __stdcall GetClassID(GUID *classid);        // 0x00637530
    virtual HRESULT __stdcall Load(IStream *stream);            // 0x00637490
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x00637510
    virtual int Kind_Of() const;                                // 0x00637480
    virtual int Size_Of() const;                                // 0x00637460
    virtual void Compute_CRC(WWCRCEngine &crc) const;           // 0x00637470
    virtual void AI();                                          // 0x006378C0

    int Get_Spread() const;                                     // 0x00637570
    void Set_Base_Cell(Cell const &cell);                 // 0x00637580
    void Set_Spread(int spread);                                // 0x00637590
    void Set_Rad_Level(int level);                              // 0x006375B0
    int Get_Current_Level() const;                              // 0x006375D0
    void Increase_Radiation(int amount);                        // 0x006375F0
    void Unknown_00637640();                                    // 0x00637640
    // Takes the remaining effect off the cells (Get_Rad_Level_At scaled by the decay steps left).
    void Unknown_00637C10();                                    // 0x00637C10
    // One decay step on the cells (AI, every RadLevelDelay frames).
    void Unknown_00637DC0();                                    // 0x00637DC0
    double Get_Rad_Level_At(Cell const &cell);            // 0x006379B0
    // Gives every cell in the spread square its level (Get_Rad_Level_At).
    void Unknown_00637A80();                                    // 0x00637A80
    void Update_Light();                                        // 0x00637F50

    LightSourceClass *LightSource;                  // +0x24
    CDTimerClass<FrameTimerClass> unknown_28;       // +0x28
    CDTimerClass<FrameTimerClass> unknown_34;       // +0x34
    Cell BaseCell;                            // +0x40
    int Spread;                                     // +0x44
    int SpreadInLeptons;                            // +0x48 (Spread * 256 + 128)
    int RadLevel;                                   // +0x4C
    int unknown_50;                                 // +0x50
    int unknown_54;                                 // +0x54
    int unknown_58;                                 // +0x58 light colour (red; hypothesis)
    int unknown_5c;                                 // +0x5C (green)
    int unknown_60;                                 // +0x60 (blue)
    int unknown_64;                                 // +0x64
    int unknown_68;                                 // +0x68 light intensity offset
    int RadDuration;                                // +0x6C total time (level x RadDurationMultiple)
    int RadTimeLeft;                                // +0x70 counted down by AI
};

extern DynamicVectorClass<RadSiteClass *> unknown_RadSiteClass_list_00ab6620;   // 0x00AB6620

#endif
