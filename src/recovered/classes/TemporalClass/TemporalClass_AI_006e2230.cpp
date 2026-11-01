#include "shared/temporal.hpp"
#include "shared/techno.hpp"
#include "shared/anim.hpp"
#include "shared/super.hpp"

void TemporalClass::AI()
{
    if(Target!=0 && Target->unknown_20c==this && unknown_40!=0) {
        Target->unknown_20c=0;
        Target->unknown_204=false;
        Just_Let_Go();
        return;
    }
    unknown_48-=Get_Warp_Per_Step(0);
    if(unknown_48<=0) {
        if(Target==0) {
            Target=0;unknown_44=0;unknown_40=0;unknown_3c=0;unknown_38=0;
        } else {
            new AnimClass(Rules->WarpAway,Target->Position_Coord_004f3f40(),0,1,0x600,0);
        }
        if(Owner->unknown_slot32()->Trainable) {
            TechnoTypeClass *target_type=Target->unknown_slot32();
            TechnoTypeClass *owner_type=Owner->unknown_slot32();
            Owner->unknown_118.Unknown_00713360(owner_type->unknown_slot33((int)Owner->House),target_type->unknown_slot33((int)Target->House));
        }
        if(Target!=0) {
            if(Target->Kind_Of()==6) {
                BuildingClass *building=(BuildingClass *)Target;
                if(building!=0) {
                    if(building->unknown_4532f0()>0) building->Unknown_004536D0(0);
                    if(unknown_a40774==0) {
                        while(building->Cargo.Object!=0) {
                            ObjectClass *passenger=building->Cargo.unknown_4689f0();
                            delete passenger;
                        }
                    }
                }
                if(unknown_3c!=0) {
                    ((SuperClass *)unknown_3c)->Suspend(false);
                    unknown_3c=0;
                }
                Target->unknown_slot216((int)Owner);
                Target->unknown_slot55(Owner);
                Target->unknown_slot60();
                building->House->unknown_144=true;
            } else {
                Target->unknown_slot216((int)Owner);
                Target->unknown_slot55(Owner);
                Target->unknown_slot60();
            }
        }
        Target=0;unknown_44=0;unknown_40=0;unknown_3c=0;unknown_38=0;
    }
}

// External references checked against complete original body operands.
// @ref ??0AnimClass@@QAE@PBVAnimTypeClass@@ABUCoordStruct@@HHHH@Z=00420110
// @ref ??2@YAPAXI@Z=00782017
// @ref ?Get_Warp_Per_Step@TemporalClass@@QAEHH@Z=006e2470
// @ref ?Just_Let_Go@TemporalClass@@QAEXXZ=006e2710
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Suspend@SuperClass@@QAE_N_N@Z=0069cc60
// @ref ?Unknown_004536D0@BuildingClass@@QAEXPAVInfantryClass@@@Z=004536d0
// @ref ?Unknown_00713360@UnknownTechnoPair@@QAEXHH@Z=00713360
// @ref ?unknown_4532f0@BuildingClass@@QAEHXZ=004532f0
// @ref ?unknown_4689f0@UnknownCargo@@QAEPAVObjectClass@@XZ=004689f0
// @ref ?unknown_a40774@@3HA=00a40774
