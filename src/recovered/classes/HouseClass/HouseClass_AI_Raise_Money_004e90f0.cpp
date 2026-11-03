// @ref ?AI_Building@HouseClass@@QAEHXZ=004e9660
// Sell base assets to restore a refinery/harvester; original004E90F0.
#include "shared/building_class.hpp"
#include "shared/unit.hpp"
#include "shared/factory_class_decl.hpp"
#include "shared/rules.hpp"
void __fastcall Building_Refresh_House_Buildings_0044fa40(HouseClass *house);
bool HouseClass::AI_Raise_Money_004e90f0(int urgency)
{
    int refund=0;
    int needed;
    bool can_build_harvester=(unknown_5460.unknown_func_491d10(Rules->BuildRefinery[0]->ArrayIndex)>0 ||
                              unknown_5460.unknown_func_491d10(Rules->BuildRefinery[1]->ArrayIndex)>0) &&
                             (unknown_5460.unknown_func_491d10(Rules->BuildWeapons[0]->ArrayIndex)>0 ||
                              unknown_5460.unknown_func_491d10(Rules->BuildWeapons[1]->ArrayIndex)>0);
    if (can_build_harvester) needed=Unknown_004EF6F0(Rules->unknown_9ec)->unknown_slot33((int)this);
    else needed=unknown_func_4ef600(Rules->BuildRefinery)->unknown_slot33((int)this);
    int i=unknown_55f0.Nodes.Count()-1;
    for (;i>=0;--i) {
        BuildingClass *building=unknown_55f0.Get_Building(i);
        if (building) {
            char level=building->unknown_5c6;
            if (level!=0) {
                int cost=((BuildingTypeClass *)building->unknown_4c0[level-1])->unknown_slot46(this,true);
                Balance+=cost;
                building->unknown_44c860();
                unknown_5668=true;
                unknown_5669=true;
                Building_Refresh_House_Buildings_0044fa40(this);
            } else {
                building->unknown_slot98(1);
                if (building->Type->Gate) unknown_55f0.Nodes.Delete(i);
                refund+=building->unknown_slot167();
            }
        } else if (unknown_55f0.Is_Built(i)) {
            Sell_Wall(unknown_55f0.Nodes[i].Cell,false);
            unknown_55f0.Nodes.Delete(i);
        }
        if (refund+Balance>needed) {
            for (int j=Factories.Count()-1;j>=0;--j) {
                FactoryClass *factory=Factories[j];
                if (factory->Owner==this) {
                    Factories[j]->Suspend_004B9630(true);
                    Factories[j]->Abandon_Production_004B97C0();
                    delete Factories[j];
                }
            }
            unknown_5540=-1;
            unknown_5544=-1;
            unknown_5548=-1;
            unknown_553c=-1;
            if (can_build_harvester) {
                unknown_5540=Unknown_004EF6F0(Rules->unknown_9ec)->ArrayIndex;
                unknown_12c=2;
            } else {
                int next=unknown_55f0.Next_Buildable_Index();
                if (next!=0) {
                    if (next==-1) {
                        if (unknown_55f0.Nodes.Length()<2) goto GO_HUNT;
                        next=1;
                    }
                    BaseNodeClass node(unknown_func_4ef600(Rules->BuildRefinery)->ArrayIndex,Cell(0,0));
                    unknown_55f0.Nodes.Insert_After(node,next-1);
                    for (int j=unknown_55f0.Nodes.Count()-1;j>next;--j) {
                        if (unknown_55f0.Nodes[j].Type==unknown_func_4ef600(Rules->BuildRefinery)->ArrayIndex)
                            unknown_55f0.Nodes.Delete(j);
                    }
                    unknown_12c=1;
                    AI_Building();
                } else goto GO_HUNT;
            }
            break;
        }
    }
    if (i<=0) {
GO_HUNT:
        All_To_Hunt();
    }
    return false;
}
