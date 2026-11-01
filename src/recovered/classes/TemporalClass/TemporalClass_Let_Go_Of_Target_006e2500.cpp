#include "shared/temporal.hpp"
#include "shared/techno.hpp"

// Existing accepted BuildingClass helper's legacy integer-this interface.
namespace seed_0044d380 { void __fastcall FUN_0044d380(int building); }

void TemporalClass::Let_Go_Of_Target()
{
    if(unknown_40==0) {
        if(unknown_44!=0) {
            if(Target!=0) Target->unknown_20c=unknown_44;
            unknown_44->unknown_40=0;
            unknown_44->unknown_48=unknown_48;
        } else if(Target!=0) {
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
    } else {
        if(unknown_44!=0) {
            unknown_44->unknown_40=unknown_40;
            if(unknown_40!=0) unknown_40->unknown_44=unknown_44;
        } else unknown_40->unknown_44=0;
    }
    Target=0;
    unknown_44=0;
    unknown_40=0;
    unknown_3c=0;
    unknown_38=0;
}
// @ref ?FUN_0044d380@seed_0044d380@@YIXH@Z=0044d380

// External references checked against complete original body operands.
// @ref ?FUN_0044d380@seed_0044d380@@YIXH@Z=0044d380
