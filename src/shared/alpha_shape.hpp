// AlphaShapeClass: original RTTI79BFD4, AbstractClass base at0.
// Private compatible declaration for Object placement;no foreign body recovered.
#ifndef RA2_SHARED_ALPHA_SHAPE_HPP
#define RA2_SHARED_ALPHA_SHAPE_HPP
#include "shared/abstract.hpp"
#include "shared/rect.hpp"
class ObjectClass;
struct ShapeFileStruct;
class AlphaShapeClass : public AbstractClass {
public:
    AlphaShapeClass(ObjectClass *object, int x, int y); // 0041EBE0,ECX,RET12
    virtual ~AlphaShapeClass(); // interface declaration;body address not claimed
    virtual HRESULT __stdcall GetClassID(GUID *clsid); // slot3 0041EFC0
    virtual HRESULT __stdcall Load(IStream *stream); // slot5 0041F060
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty); // slot6 0041F0C0
    virtual int Kind_Of() const; // slot11 0041F000 returns3E
    virtual int Size_Of() const; // slot12 0041F010 returns40
    ObjectClass *Owner; // +24
    Rect Bounds; // +28..37,constructor stores x/y/width/height
    ShapeFileStruct *Image; // +38
    bool unknown_3c;
    char unknown_3d[3];
};
typedef char AlphaShapeClass_size_40[(sizeof(AlphaShapeClass) == 0x40) ? 1 : -1];
#endif
