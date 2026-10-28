// void AlphaShapeClass::Compute_CRC(WWCRCEngine &crc) const (0x0041F020, slot 13)
#include "shared/alpha_shape.hpp"
// @ref ??_7AlphaShapeClass@@6BIPersistStream@@@=0079bfd4
// @ref ??_7AlphaShapeClass@@6BIRTTITypeInfo@@@=0079bfb8
// @ref ??_7AlphaShapeClass@@6BINoticeSink@@@=0079bfb0
// @ref ??_7AlphaShapeClass@@6BINoticeSource@@@=0079bfa8
// @ref ?Compute_CRC@AbstractClass@@UBEXAAVWWCRCEngine@@@Z=004101b0
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30

void AlphaShapeClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractClass::Compute_CRC(crc);
    crc((long)Bounds.X);
    crc((long)Bounds.Y);
    crc((long)Bounds.Width);
    crc((long)Bounds.Height);
}
