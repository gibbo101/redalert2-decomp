// LightSourceClass: a light on the map (LightSource.cpp, unit 0x00536F30:
// 0x00537240-0x00537C8F; RTTI vtables 0x007A5560 primary (24 slots),
// 0x007A5544 IRTTITypeInfo at +4, 0x007A553C, 0x007A5534). Every light is in
// unknown_LightSourceClass_list_00a6e818 (defined with the unit's header
// statics). Layout from the constructors 0x00537240/0x00537310 and Change
// 0x00537580; names are hypotheses (YR's LightSourceClass agrees on them).
// The nested PendingCellClass and its static list are defined by the unit
// only: a static data member declared here would renumber the header-static
// initializers of every unit that includes this header.
#ifndef RA2_SHARED_LIGHT_SOURCE_HPP
#define RA2_SHARED_LIGHT_SOURCE_HPP

#include "shared/abstract.hpp"
#include "shared/coord.hpp"
#include "shared/vector_class.hpp"

// A light colour (red, green, blue intensities).
struct TintStruct {
    TintStruct() {}
    TintStruct(int red, int green, int blue) : Red(red), Green(green), Blue(blue) {}

    int Red;        // +0x00
    int Green;      // +0x04
    int Blue;       // +0x08
};

class LightSourceClass : public AbstractClass {
public:
    class PendingCellClass;

    LightSourceClass(CoordStruct coord, int visibility, int intensity, int red, int green, int blue);   // 0x00537240
    LightSourceClass();                                         // 0x00537310
    LightSourceClass(NoInitClass const &noinit) : AbstractClass(noinit) {}  // 0x005373C0 (out-of-line copy)
    virtual ~LightSourceClass();                                // 0x005373F0

    // Deletes every light and every pending cell (0x00537480).
    static void Clear_All();
    void Activate(int arg);                                     // 0x00537540 (turns it on, then Unknown_005375D0)
    void Deactivate(int arg);                                   // 0x00537560
    // Takes a new intensity and colour; relights the cells when active.
    void Change(int intensity, int red, int green, int blue, int arg);   // 0x00537580
    void Unknown_005375D0(int arg);                             // 0x005375D0 (relights the cells around it; not recovered)

    virtual HRESULT __stdcall GetClassID(GUID *clsid);          // 0x00537B60 slot 3
    virtual HRESULT __stdcall Load(IStream *stream);            // 0x00537BA0 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x00537BF0 slot 6
    virtual int Kind_Of() const { return 0x36; }                // 0x00537C20 slot 11 (inline)
    virtual int Size_Of() const { return sizeof(LightSourceClass); }    // 0x00537C10 slot 12 (inline)
    virtual void Compute_CRC(WWCRCEngine &crc) const;           // 0x00537B50 slot 13

    int Intensity;              // +0x24
    TintStruct Tint;            // +0x28
    int DetailLevel;            // +0x34 (2 for a placed light)
    CoordStruct Location;       // +0x38
    int Visibility;             // +0x44 (the lit radius)
    bool Activated;             // +0x48
};

extern DynamicVectorClass<LightSourceClass *> unknown_LightSourceClass_list_00a6e818;   // 0x00A6E818
// Lights update the cells while set (0x007DF630; Clear_All clears it while it
// deletes the lights; tested by 0x005375D0).
extern bool unknown_flag_7df630;

#endif
