// AlphaShapeClass: an alpha (lighting) image drawn at an object (RTTI vtable
// 0x0079BFD4, AbstractClass base; unit 0x0041E970). Layout from the
// constructors 0x0041EBE0 and 0x0041ED70.
#ifndef RA2_SHARED_ALPHA_SHAPE_HPP
#define RA2_SHARED_ALPHA_SHAPE_HPP
#include "shared/abstract.hpp"
#include "shared/rect.hpp"
class ObjectClass;
struct ShapeFileStruct;

extern "C" GUID const CLSID_AlphaShapeClass;      // 0x007A1EE0

// The product of two 8-bit values over 127, clamped (0x0083C670;
// index first * 256 + second) and whether it is built (0x0084C684).
extern unsigned char unknown_alpha_table_83c670[0x10000];
extern bool unknown_alpha_table_ready_84c684;

class AlphaShapeClass : public AbstractClass {
public:
    AlphaShapeClass(ObjectClass *object, int x, int y);         // 0x0041EBE0
    AlphaShapeClass();                                          // 0x0041ED70
    AlphaShapeClass(NoInitClass const &noinit);                 // 0x0041EED0
    virtual ~AlphaShapeClass();                                 // 0x0041EF00 (deleting 0x0041F9C0)
    virtual HRESULT __stdcall GetClassID(GUID *clsid);          // slot 3 0x0041EFC0
    virtual HRESULT __stdcall Load(IStream *stream);            // slot 5 0x0041F060
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty);   // slot 6 0x0041F0C0
    virtual void Detach(AbstractClass *target, bool all = true);    // slot 10 0x0041F0F0
    virtual int Kind_Of() const;                                // slot 11 0x0041F000 (0x3E)
    virtual int Size_Of() const;                                // slot 12 0x0041F010 (0x40)
    virtual void Compute_CRC(WWCRCEngine &crc) const;           // slot 13 0x0041F020

    static void Init_Alpha_Table();                             // 0x0041F950

    ObjectClass *Owner;         // +0x24
    Rect Bounds;                // +0x28 x, y and the image's width and height
    ShapeFileStruct *Image;     // +0x38
    bool unknown_3c;            // +0x3C (set when the owner is detached)
    char unknown_3d[3];
};
typedef char AlphaShapeClass_size_40[(sizeof(AlphaShapeClass) == 0x40) ? 1 : -1];

// The unit's list of alpha shapes (unknown_AlphaShapeClass_list_0083c648) is defined in the unit.

#endif
