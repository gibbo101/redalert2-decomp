// BaseClass: a house's base plan (Base.cpp, unit 0x0042BCF0; RTTI BaseClass,
// vtable 0x0079C590; 0x78 bytes). Westwood's BASE.CPP (TS) names the members:
// Nodes, PercentBuilt, House; the other fields keep placeholder names. Moved
// out of shared/house.hpp so the Base unit does not include the House layout.
// BaseNodeClass: shared/house_nodes.hpp.
#ifndef RA2_SHARED_BASE_HPP
#define RA2_SHARED_BASE_HPP

#include "shared/com_persist.hpp"
#include "shared/vector_class.hpp"
#include "shared/house_nodes.hpp"
#include "shared/rect.hpp"

class HouseClass;
class BuildingClass;
class CCINIClass;
class WWCRCEngine;

class BaseClass {
public:
#ifdef RA2_BASE_INIT
    void Init() { Nodes.Clear(); }
#endif
    BaseClass();                            // 0x0042BF70
    BaseClass(NoInitClass const &noinit);   // 0x0042CA50
    virtual HRESULT __stdcall Load(IStream *stream);  // slot 0 0x0042C6A0
    virtual HRESULT __stdcall Save(IStream *stream);  // slot 1 0x0042C8E0
    ~BaseClass() { Nodes.Clear(); }
    virtual void Compute_CRC(WWCRCEngine &crc) const;   // slot 2 0x0042C9F0
    void Read_INI(CCINIClass &ini, char const *section);    // 0x0042C460 (the house's section)
    void Write_INI(CCINIClass &ini, char const *section);   // 0x0042C5D0
    bool Is_Built(int index) const;                         // 0x0042C000
    bool unknown_42c080(int index) const;                   // 0x0042C080 (the node's +0x08 flag)
    BuildingClass *Get_Building(int index) const;           // 0x0042C0A0
#ifdef BASE_DECLARE_IS_NODE
    // Whether the building stands on one of this base's nodes (0x0042C210; TibSun Is_Node; guarded:
    // base.hpp is in house.hpp's closure, so only the base unit sees it).
    bool Is_Node(BuildingClass *building);
#endif
    BaseNodeClass *Get_Node(BuildingClass *building);       // 0x0042C2B0
    BaseNodeClass *Next_Buildable(int type = -1);           // 0x0042C3A0
    int Next_Buildable_Index(int type = -1);                // 0x0042C3D0
    void unknown_42cad0(BuildingClass *building);           // 0x0042CAD0 (marks the building's node)
    int unknown_42cb70(BaseNodeClass *node);                // 0x0042CB70 (counts on the node's +0x0C)

    DynamicVectorClass<BaseNodeClass> Nodes;    // +0x04 (vtable 0x0079C5C0)
    int PercentBuilt;                       // +0x1C ([house] PercentBuilt)
    DynamicVectorClass<Cell> unknown_20;  // +0x20 (vtable 0x0079C5A0)
    DynamicVectorClass<Cell> unknown_38;  // +0x38 (vtable 0x0079C5A0)
    Cell unknown_50;                  // +0x50
    // Two zeroed 16-byte members (layout hypothesis: their inline constructors
    // are what keeps the list constructors out of line in 0x0042BF70/0x0042CA50).
    Rect unknown_54;                        // +0x54
    Rect unknown_64;                        // +0x64
    HouseClass *House;                      // +0x74 (set by HouseClass::Read_INI)
};

#endif
