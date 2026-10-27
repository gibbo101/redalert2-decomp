// bool TechnoClass::unknown_6d9710() const (0x006D9710)
// Whether the timer at +0x148 has no time left.
#include "shared/techno.hpp"
// @ref ?Frame@@3HA=00a40d2c

bool TechnoClass::unknown_6d9710() const
{
    return unknown_148.Value() == 0;
}
