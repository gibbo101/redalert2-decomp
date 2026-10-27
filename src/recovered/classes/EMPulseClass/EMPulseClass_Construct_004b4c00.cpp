#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_OBJECT
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#include "shared/empulse_class.hpp"
// @ref ??_7EMPulseClass@@6BIPersistStream@@@=007a0db8
// @ref ??_7EMPulseClass@@6BIRTTITypeInfo@@@=007a0d9c
// @ref ??_7EMPulseClass@@6BINoticeSink@@@=007a0d94
// @ref ??_7EMPulseClass@@6BINoticeSource@@@=007a0d8c
// @ref ?Array@EMPulseClass@@=00855a28
// @ref ?GetClassID@EMPulseClass@@=004b5340
// @ref ?Save@EMPulseClass@@=004b53d0
// @ref ?Kind_Of@EMPulseClass@@=004b5400
// @ref ?Size_Of@EMPulseClass@@=004b53f0
// @ref ?unknown_flag_a40958@@=00a40958
// @ref ?Apply_004B4E30@EMPulseClass@@=004b4e30
// @ref ?Clear_Cells_004B5210@EMPulseClass@@=004b5210
// @ref ?Frame@@=00a40d2c

EMPulseClass::~EMPulseClass()
{
    if (unknown_flag_a40958) Clear_Cells_004B5210();
    Unknown_006ECB90(this, true);
    Array.Delete(this);
}
EMPulseClass::EMPulseClass(Cell position, int radius, int duration, TechnoClass *source)
    : Position(position), Radius(radius), CreatedFrame(Frame), Duration(duration)
{
    Create_ID();
    Array.Add(this);
    Apply_004B4E30(source);
}
EMPulseClass::EMPulseClass(NoInitClass const &noinit) : AbstractClass(noinit)
{
}
void EMPulseClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractClass::Compute_CRC(crc);
    crc(Position.X);
    crc(Position.Y);
    crc((long)Radius);
    crc((long)CreatedFrame);
    crc((long)Duration);
}
HRESULT __stdcall EMPulseClass::Load(IStream *stream)
{
    HRESULT result = AbstractClass::Load(stream);
    if (result >= 0) {
        NoInitClass noinit;
        new(this) EMPulseClass(noinit);
        result = 0;
    }
    return result;
}
void EMPulseClass::Delete_All_004B4DC0()
{
    while (Array.Count()) delete Array[0];
}
void EMPulseClass::Expire_004B4DF0()
{
    for (int index=Array.Count()-1; index>=0; --index) {
        EMPulseClass *pulse=Array[index];
        if (Frame >= pulse->Duration + pulse->CreatedFrame) delete pulse;
    }
}
