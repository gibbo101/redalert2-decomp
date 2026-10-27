// TriColorGaugeClass::TriColorGaugeClass(unsigned id, int x, int y, int w, int h) (0x004D0630)
#include "shared/gadget.hpp"

TriColorGaugeClass::TriColorGaugeClass(unsigned id, int x, int y, int w, int h) :
    GaugeClass(id, x, y, w, h),
    RedLimit(0),
    YellowLimit(0)
{
}
