// House super-weapon target cell, original004F65A0. Independently authored from target flow.
#include "shared/house.hpp"
#include "shared/building_class.hpp"
#include "shared/unit.hpp"
#include "shared/infantry.hpp"
#include "shared/factory_class_decl.hpp"
#include "shared/rules.hpp"
Cell HouseClass::unknown_func_4f65a0()
{
    HouseClass *enemy=Houses[unknown_54f0];
    DynamicVectorClass<AbstractClass *> targets;
    int best=0;
    for (int i=0;i<Technos.Count();++i) {
        int value=0;
        bool valid=false;
        TechnoClass *techno=Technos[i];
        if (techno->House==enemy) {
            value=1;
            if (techno->unknown_slot29()==2 && techno->unknown_7d && !techno->unknown_76) valid=true;
            else if (unknown_c8==0) {
                for (int j=0;j<Factories.Count();++j) {
                    FactoryClass *factory=Factories[j];
                    if (factory->Get_Object()==techno && factory->Rate && !factory->unknown_6c) valid=true;
                }
            }
            switch (techno->Kind_Of()) {
            case 15: {
                InfantryTypeClass *type=((InfantryClass *)techno)->Type;
                if (type->Engineer) value=Rules->AIIonCannonEngineerValue[unknown_c8];
                else if (type->VehicleThief) value=Rules->AIIonCannonThiefValue[unknown_c8];
                else value=2;
                break;
            }
            case 6: {
                BuildingTypeClass *type=((BuildingClass *)techno)->Type;
                if (type->Factory==7) value=Rules->AIIonCannonConYardValue[unknown_c8];
                else if (type->Factory==40) value=Rules->AIIonCannonWarFactoryValue[unknown_c8];
                else if (type->Power>type->PowerDrain_c6c) value=Rules->AIIonCannonPowerValue[unknown_c8];
                else if (type->IsBaseDefense) value=Rules->AIIonCannonBaseDefenseValue[unknown_c8];
                else if (type->IsPlug) value=Rules->AIIonCannonPlugValue[unknown_c8];
                else if (type->IsTemple) value=Rules->AIIonCannonTempleValue[unknown_c8];
                else if (type->HoverPad) value=Rules->AIIonCannonHelipadValue[unknown_c8];
                else value=4;
                break;
            }
            case 1: {
                UnitTypeClass *type=((UnitClass *)techno)->Type;
                if (type->Harvester) value=Rules->AIIonCannonHarvesterValue[unknown_c8];
                else {
                    for (int j=0;j<Rules->unknown_7c8.Count();++j) {
                        if (Rules->unknown_7c8[j]==type->DeploysInto) {
                            value=Rules->AIIonCannonMCVValue[unknown_c8];
                            goto CLASSIFIED;
                        }
                    }
                    if (type->Passengers>0) value=Rules->AIIonCannonAPCValue[unknown_c8];
                    else value=2;
                }
                break;
            }
            }
        }
CLASSIFIED:
        if (techno->unknown_1b8==2 || (techno->Kind_Of()==6 && ((BuildingClass *)techno)->unknown_5bd==15)) value=Random_Pick(0,best+10);
        if (valid) {
            if (value>best) {
                targets.Clear();
                targets.Add(techno);
                best=value;
            } else if (value==best) targets.Add(techno);
        }
    }
    if (targets.Count()>0) {
        AbstractClass *target=targets[Random_Pick(0,targets.Count()-1)];
        if (target) return Coord_Cell(target->Center_Coord());
    }
    return unknown_cell_a40f10;
}
