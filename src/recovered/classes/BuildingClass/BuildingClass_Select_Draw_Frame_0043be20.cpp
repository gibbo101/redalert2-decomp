// Select the building's SHP frame from its stage, state, health and occupants.
// This original body establishes that the old palette/converter label was provisional.
#include "shared/building.hpp"
#include "shared/rules.hpp"
// @ref ?Health_Ratio@ObjectClass@@QBENXZ=005d4540
// @ref ?Rules@@3PAVRulesClass@@A=00839848
int BuildingClass::unknown_43be20()
{
    BuildingTypeClass *type=Type;
    unsigned int frame=(unsigned int)AnimationStage.Value;
    if(type->LaserFence) return unknown_4ec;
    if(type->FirestormWall) return unknown_4f0;
    if(unknown_42c==0) {
        if(type->Gate) frame=(unsigned int)type->AnimFrames[0].unknown_04+(unsigned int)type->AnimFrames[0].unknown_00-frame-1;
        if(unknown_slot91()==19) {
            frame=(unsigned int)Type->AnimFrames[unknown_42c].unknown_04+(unsigned int)Type->AnimFrames[unknown_42c].unknown_00-frame-1;
        }
    } else {
        if(type->CanBeOccupied) {
            if(Health_Ratio()<=Rules->unknown_1370) return 1;
            return unknown_554.Count()>0?2:0;
        }
        if(type->Gate) {
            if(Health_Ratio()<=Rules->unknown_1368) return (unsigned int)Type->GateStages+1;
            return 0;
        }
        if(Health_Ratio()<=Rules->unknown_1368) {
            if(unknown_42c==1) ++frame;
            else {
            type=Type;
            int end=(int)((unsigned int)type->AnimFrames[1].unknown_04+(unsigned int)type->AnimFrames[1].unknown_00);
            int other=(int)((unsigned int)type->AnimFrames[2].unknown_04+(unsigned int)type->AnimFrames[2].unknown_00);
            if(end<=other) end=other;
            other=(int)((unsigned int)type->AnimFrames[4].unknown_04+(unsigned int)type->AnimFrames[4].unknown_00);
            if(end<=other) end=other;
            other=(int)((unsigned int)type->AnimFrames[5].unknown_04+(unsigned int)type->AnimFrames[5].unknown_00);
            if(end<=other) end=other;
            frame+=(unsigned int)end;
            }
        }
    }
    return frame;
}
