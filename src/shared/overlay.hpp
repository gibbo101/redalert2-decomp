// OverlayClass: an overlay being placed on the map (walls, ore, crates;
// Overlay.cpp, members 0x005DA7D0-0x005DC3A6; RTTI vtables 0x007A77F4
// primary (118 slots), 0x007A77D0 IRTTITypeInfo at +4, 0x007A77EC
// INoticeSink, 0x007A77C8 INoticeSource).
//
// Layout (from the constructor 0x005DA7D0, the destructor 0x005DA8D0 and
// Load 0x005DBC80):
//   +0x000  ObjectClass (0x98)
//   +0x098  OverlayTypeClass *Class (swizzled; Class_Of returns it)
//   size 0x9C
// Like smudges, an overlay object exists while it is placed: the cell keeps
// the overlay index. Every overlay is in the list at 0x00A40C00.
#ifndef RA2_SHARED_OVERLAY_HPP
#define RA2_SHARED_OVERLAY_HPP

#include "shared/unknown_globals.hpp"
#include "shared/overlay_type.hpp"
#include "shared/map_cell_view.hpp"
#include "shared/rect.hpp"
#include "shared/ini_class.hpp"

extern "C" GUID const CLSID_OverlayClass;       // 0x007A1C20

// The house an overlay is placed for (0x007E8A8C; -1 otherwise; hypothesis).
extern int unknown_placing_house_7e8a8c;

// The scenario INI format (0x00A40D24; terrain and overlay read their packs when above 1; hypothesis).
// The INI section name "OVERLAY" (a pointer variable at 0x007A77C0).
extern char const *unknown_overlay_section_7a77c0;

class OverlayClass : public ObjectClass {
public:
    OverlayClass(OverlayTypeClass *type, Cell const &cell, int house = -1);   // 0x005DA7D0
    OverlayClass(NoInitClass const &noinit) : ObjectClass(noinit) {}    // inline (Load)
    virtual ~OverlayClass();                                            // 0x005DA8D0

    virtual HRESULT __stdcall GetClassID(GUID *clsid)                   // 0x005DC2A0 slot 3 (inline)
    {
        if (clsid == 0) {
            return E_POINTER;
        }
        *clsid = CLSID_OverlayClass;
        return S_OK;
    }
    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x005DBC80 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x005DBCE0 slot 6
    virtual int Kind_Of() const { return 0x14; }                        // 0x005DC2E0 slot 11 (inline)
    virtual int Size_Of() const { return sizeof(OverlayClass); }        // 0x005DC290 slot 12 (inline)
    virtual ObjectTypeClass *Class_Of() const;                          // 0x005DC170 slot 33
    virtual void unknown_slot67(int arg1, int arg2) {}                  // 0x005DC2F0 (inline)
    virtual void unknown_slot68(int arg1, int arg2);                    // 0x005DBD00
    virtual bool unknown_slot71(int arg1);                              // 0x005DA970

    static Point2D __fastcall Draw_Offset(int overlay);                 // 0x005DC050 (pixel offset of an overlay image; hypothesis)
    static int __fastcall To_Tiberium(int overlay);                     // 0x005DC0B0 (the tiberium type of an ore overlay, -1)
    static void __fastcall Read_INI(CCINIClass &ini);                   // 0x005DB670 ([OverlayPack] and [OverlayDataPack])
    static void __fastcall Write_INI(CCINIClass &ini);                  // 0x005DBA30
    static void unknown_func_5dc180();                                  // 0x005DC180 (clears overlay 0x7E, then a pass over the dense cells)

    OverlayTypeClass *Class;                // +0x098
};

// The list of overlays (0x00A40C00; defined by the unit at 0x004D2BA0).
extern DynamicVectorClass<OverlayClass *> unknown_OverlayClass_list_00a40c00;

#endif
