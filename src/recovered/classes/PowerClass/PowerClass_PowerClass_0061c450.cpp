// PowerClass::PowerClass() (0x0061C450)
// Constructs the radar, then the power bar's timers (started on the system
// clock) and counters.
// Power.CPP sees the full HouseClass (the AI and the bar segments call its
// IHouse power methods); included first, it takes the place of
// shared/house_screen.hpp, the view shared/power.hpp gives the other units.
#include "shared/house.hpp"
#include "shared/power.hpp"
// @ref ??0RadarClass@@QAE@XZ=0062ede0
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430
// @ref ??_7PowerClass@@6B@=007a832c

PowerClass::PowerClass()
    : unknown_1508(false), unknown_1518(0), unknown_1528(0), unknown_152c(0), unknown_1530(0), unknown_1534(false),
      unknown_1538(-1), unknown_153c(-1)
{
}
