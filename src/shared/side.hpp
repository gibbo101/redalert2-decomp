// SideClass: a side (faction) and the house types that belong to it
// (Side.cpp, members 0x0067AE10-0x0067B2BC; RTTI vtables 0x007AB270 primary,
// 0x007AB254 IRTTITypeInfo at +4, 0x007AB24C INoticeSink, 0x007AB244
// INoticeSource).
//
// Layout (constructor 0x0067AE10, Load 0x0067B040, Save 0x0067B160):
//   +0x00  AbstractTypeClass (0x98 bytes)
//   +0x98  TypeList<int> Houses   the HousesType indices of the side
//   size 0xB4 (Size_Of)
// Every constructed side is added to Sides (0x008661B0) and removed by the
// destructor. Kind_Of answers 0x1C (the side RTTI kind).
#ifndef SHARED_SIDE_HPP
#define SHARED_SIDE_HPP

#include "shared/abstract_type.hpp"
#include "shared/type_list.hpp"

// Called by the destructor with the dying object (0x006ECB90). The same
// function is declared for ObjectClass in shared/object.hpp; its parameter is
// presumably AbstractClass (it is passed a SideClass here).

// Class ID returned by SideClass::GetClassID (0x007A1E50).
extern "C" GUID const CLSID_SideClass;

class SideClass : public AbstractTypeClass {
public:
    SideClass(char const *ini_name);                            // 0x0067AE10
    SideClass(NoInitClass const &noinit) : AbstractTypeClass(noinit), Houses() {}
    // 0x0067AED0 (defined in Side.cpp; the scalar deleting destructor 0x0067B1F0 expands it).
    virtual ~SideClass();

    // Index in Sides of the side whose ID equals the name (case-insensitive), or -1.
    static int __fastcall Find_Index(char const *name);         // 0x0067AF90

    virtual HRESULT __stdcall GetClassID(GUID *classid);        // 0x0067B000
    virtual HRESULT __stdcall Load(IStream *stream);            // 0x0067B040
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty); // 0x0067B160
    virtual int Kind_Of() const;                                // 0x0067B1E0
    virtual int Size_Of() const;                                // 0x0067B1D0
    virtual void Compute_CRC(WWCRCEngine &crc) const;           // 0x0067AFD0

    TypeList<int> Houses;           // +0x98
};

extern DynamicVectorClass<SideClass *> Sides;                   // 0x008661B0

// Side.cpp defines the destructor out of line (0x0067AED0; RA2_SIDE_UNIT in that unit's first source);
// other units keep this inline copy.
#ifndef RA2_SIDE_UNIT
inline SideClass::~SideClass()
{
    Unknown_006ECB90(this, true);
    Sides.Delete(this);
}
#endif

#endif
