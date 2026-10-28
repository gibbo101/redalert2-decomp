// SmudgeTypeClass: the type of a smudge (craters and scorch marks;
// SmudgeType.cpp, members 0x00687DA0-0x00688CAC; RTTI vtables 0x007AB7A0
// primary (41 slots), 0x007AB784 IRTTITypeInfo at +4, 0x007AB77C
// INoticeSink, 0x007AB774 INoticeSource).
//
// Layout (from the constructor 0x00687DA0, Read_INI 0x006881B0 and
// Compute_CRC 0x006882B0; INI key names are the original strings):
//   +0x000  ObjectTypeClass (0x264)
//   +0x264  int ArrayIndex   index in SmudgeTypes (slot 16 returns it)
//   +0x268  int Width        "Width" (cells, 1)
//   +0x26C  int Height       "Height" (cells, 1)
//   +0x270  bool Crater      "Crater"
//   +0x271  bool Burn        "Burn"
//   size 0x274
// Every type is in SmudgeTypes (0x00A40BC8, a DynamicVectorClass defined by
// the global-list unit at 0x004D2BA0).
#ifndef RA2_SHARED_SMUDGE_TYPE_HPP
#define RA2_SHARED_SMUDGE_TYPE_HPP

#include "shared/object_type.hpp"

class SmudgeClass;
class SmudgeTypeClass;

extern "C" GUID const CLSID_SmudgeTypeClass;    // 0x007A1B80

// The type list (0x00A40BC8; the name is the global-list unit's).
extern DynamicVectorClass<SmudgeTypeClass *> SmudgeTypes;

class SmudgeTypeClass : public ObjectTypeClass {
public:
    SmudgeTypeClass(char const *ini_name);                              // 0x00687DA0
    SmudgeTypeClass(NoInitClass const &noinit);                         // 0x00687EB0
    virtual ~SmudgeTypeClass();                                         // 0x00687EE0

    static int __fastcall From_Name(char const *name);                  // 0x00687F60
    static void __fastcall Init(int theater);                           // 0x00687FB0
    static SmudgeTypeClass *__fastcall Find_Or_Make(char const *name);  // 0x006883D0
    static bool __fastcall Create_Scorch(CoordStruct const &coord, int width, int height, bool big);   // 0x00688460
    static bool __fastcall Create_Crater(CoordStruct const &coord, int width, int height, bool big);   // 0x00688750

    virtual HRESULT __stdcall GetClassID(GUID *clsid);                  // 0x00688390 slot 3
    virtual HRESULT __stdcall Load(IStream *stream);                    // 0x00688310 slot 5
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);  // 0x00688370 slot 6
    virtual int Kind_Of() const { return 0x1E; }                        // 0x00688BF0 slot 11 (inline)
    virtual int Size_Of() const { return sizeof(SmudgeTypeClass); }     // 0x00688C00 slot 12 (inline)
    virtual void Compute_CRC(WWCRCEngine &crc) const;                   // 0x006882B0 slot 13
    virtual int unknown_slot16() const { return ArrayIndex; }           // 0x00688C10 (inline)
    virtual bool Read_INI(CCINIClass &ini);                             // 0x006881B0 slot 25
    virtual bool unknown_slot32(Cell const &cell, HouseClass *house) const;   // 0x00688030 (creates a smudge at the cell)
    virtual ObjectClass *unknown_slot35(HouseClass *house) const;       // 0x006880A0 (creates a smudge)
    virtual void unknown_slot40(Point2D const *point, Rect const *window, int piece, int height, Cell const *cell);   // 0x006880D0 (draws one piece of the image; new slot)

    bool Can_Place(Cell const &cell, bool arg2) const;            // 0x00688A40 (name hypothesis)
    void Place(Cell const &cell) const;                           // 0x00688B40 (name hypothesis)

    int ArrayIndex;                         // +0x264
    int Width;                              // +0x268
    int Height;                             // +0x26C
    bool Crater;                            // +0x270
    bool Burn;                              // +0x271
};

#endif
