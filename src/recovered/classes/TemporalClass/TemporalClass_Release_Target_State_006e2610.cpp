#include "shared/temporal.hpp"
#include "shared/techno.hpp"
namespace seed_0044d380 { void __fastcall FUN_0044d380(int building); }

void TemporalClass::Unknown_006E2610()
{
    if(Target!=0) {
        Target->unknown_20c=0;
        Target->unknown_204=false;
        if(Target->Kind_Of()==6) {
            TechnoClass *building=Target;
            building->House->unknown_5668=true;
            seed_0044d380::FUN_0044d380((int)building);
            building->House->unknown_144=true;
        }
        Target->unknown_slot71(2);
    }
}
// @ref ?FUN_0044d380@seed_0044d380@@YIXH@Z=0044d380

// External references checked against complete original body operands.
// @ref ?FUN_0044d380@seed_0044d380@@YIXH@Z=0044d380
