// CoordStruct InfantryTypeClass::unknown_slot31() const (0x0050A940)
// 0x55 leptons square, twice the 0x00A411B0 height.
#include "shared/infantry_type.hpp"
// @ref ?unknown_a411b0@@3HA=00a411b0

CoordStruct InfantryTypeClass::unknown_slot31() const
{
    return CoordStruct(0x55, 0x55, unknown_a411b0 * 2);
}
