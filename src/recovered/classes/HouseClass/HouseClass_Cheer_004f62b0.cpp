// void HouseClass::Cheer() (0x004F62B0)
// Every techno of the house cheers (TechnoClass slot 205), then Rules'
// CheerSound plays (name hypothesis).
#include "shared/techno.hpp"
#include "shared/rules.hpp"

void HouseClass::Cheer()
{
    int count = Technos.Count();
    for (int index = 0; index < count; index++) {
        TechnoClass *techno = Technos[index];
        if (techno != 0 && techno->House == this) {
            techno->unknown_slot205();
        }
    }
    Unknown_00713DB0(Rules->CheerSound, 1.0f, 0x2000, 0);
}
