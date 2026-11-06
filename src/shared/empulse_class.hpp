#ifndef RA2_SHARED_EMPULSE_CLASS_HPP
#define RA2_SHARED_EMPULSE_CLASS_HPP
#include "shared/vector_class_decl.hpp"
#include "shared/abstract_class.hpp"
#include "shared/coord.hpp"
#include "shared/cd_timer.hpp"
class TechnoClass;
// Original RTTI EMPulseClass, primary vtable 0x7A0DB8.
// Constructor 0x4B4C00 and CRC 0x4B52F0 establish the four fields.
class EMPulseClass : public AbstractClass {
public:
    static DynamicVectorClass<EMPulseClass *> Array; // 00855a28, existing population534
    EMPulseClass(); // 004b4cc0
    EMPulseClass(Cell position, int radius, int duration, TechnoClass *source); // 004b4c00
    EMPulseClass(NoInitClass const &noinit); // 004b4d00
    virtual ~EMPulseClass(); // 004b4d30
    virtual HRESULT __stdcall GetClassID(GUID *clsid); // 004b5340
    virtual HRESULT __stdcall Load(IStream *stream); // 004b5380
    virtual HRESULT __stdcall Save(IStream *stream, BOOL clear_dirty); // 004b53d0
    virtual int Kind_Of() const; // 004b5400
    virtual int Size_Of() const; // 004b53f0
    virtual void Compute_CRC(WWCRCEngine &crc) const; // 004b52f0
    void Apply_004B4E30(TechnoClass *source);
    void Clear_Cells_004B5210();
    static void Delete_All_004B4DC0();
    static void Expire_004B4DF0();
    Cell Position; // +24
    int Radius; // +28
    int CreatedFrame; // +2c
    int Duration; // +30
};
#endif
