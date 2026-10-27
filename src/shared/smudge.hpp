// SmudgeClass: a crater or scorch mark placed on the map (Smudge.cpp,
// members 0x006875C0-0x00687BA6; RTTI vtables 0x007AB58C primary (116
// slots), 0x007AB568 IRTTITypeInfo at +4, 0x007AB584 INoticeSink, 0x007AB560
// INoticeSource).
//
// Layout (from the constructor 0x006875C0, the destructor 0x006876B0 and
// Load 0x00687A00):
//   +0x000  ObjectClass (0x98)
//   +0x098  SmudgeTypeClass *Class (swizzled; Class_Of returns it)
//   size 0x9C
// A smudge exists only while it is being placed: slot 71 marks the cells
// (SmudgeTypeClass::Place) and removes the object again (slot 60).
// Every smudge is in the list at 0x00A3D240.
#ifndef RA2_SHARED_SMUDGE_HPP
#define RA2_SHARED_SMUDGE_HPP

#include "shared/unknown_globals.hpp"
#include "shared/smudge_type.hpp"
#include "shared/map_cell_view.hpp"

extern "C" GUID const CLSID_SmudgeClass;        // 0x007A1C00

// The house a placed object belongs to while it is being placed (0x007F4230;
// -1 otherwise; hypothesis).
extern int unknown_placing_house_7f4230;
// Smudges are always placed when this is positive (0x00A40774; hypothesis:
// a scenario-loading or editor flag).
// Forces image reloads (0x00A40D13; also declared by shared/anim_type.hpp).
// The INI section name "Smudge" (a pointer variable at 0x007AB558).
extern char const *unknown_smudge_section_7ab558;

class SmudgeClass : public ObjectClass {
public:
    SmudgeClass(SmudgeTypeClass *type, CoordStruct const &coord, int house = -1);   // 0x006875C0
    SmudgeClass(NoInitClass const &noinit) : ObjectClass(noinit) {}     // inline (Load)
    virtual ~SmudgeClass();                                             // 0x006876B0

    static void __fastcall Read_INI(CCINIClass &ini);                   // 0x006877F0 ([Smudge] entries)
    static void __fastcall Write_INI(CCINIClass &ini);                  // 0x00687930

    virtual HRESULT __stdcall GetClassID(GUID *clsid)                   // 0x00687AB0 slot 3 (inline)
    {
        if (clsid == 0) {
            return E_POINTER;
        }
        *clsid = CLSID_SmudgeClass;
        return S_OK;
    }
    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x00687A00 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x00687A60 slot 6
    virtual int Kind_Of() const { return 0x1D; }                        // 0x00687AA0 slot 11 (inline)
    virtual int Size_Of() const { return sizeof(SmudgeClass); }         // 0x00687A90 slot 12 (inline)
    virtual ObjectTypeClass *Class_Of() const { return Class; }         // 0x00687A80 slot 33 (inline)
    virtual void unknown_slot67(int arg1, int arg2) {}                  // 0x00687AF0 (inline)
    virtual bool unknown_slot71(int arg1);                              // 0x00687750

    SmudgeTypeClass *Class;                 // +0x098
};

// The list of smudges (0x00A3D240; defined by the unit at 0x004D2BA0).
extern DynamicVectorClass<SmudgeClass *> Smudges;

#endif
