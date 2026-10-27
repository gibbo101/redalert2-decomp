// Change the building animation state and restart its frame countdown.
#include "shared/building.hpp"
#include "shared/options.hpp"
// @ref ?Normalize_Delay@OptionsClass@@=005d9760
// @ref ?Options@@=00a40b18
// @ref _unknown_a40774=00a40774
// @ref ?Health_Ratio@ObjectClass@@=005d4540
void BuildingClass::unknown_443d60(int state)
{
    unknown_430=state;
    if(unknown_42c==-1 || state==0 || unknown_a40774) {
        unknown_430=-1;
        unknown_42c=state;
        BuildingTriple const *control=&Type->AnimFrames[state];
        if(unknown_a40774) {
            unknown_44c920(17,Health_Ratio()<=Rules->unknown_1368,unknown_554.Count()>0,0);
            if(unknown_a40774) {
                unknown_44c920(3,Health_Ratio()<=Rules->unknown_1368,unknown_554.Count()>0,0);
                if(unknown_a40774) {
                    unknown_44c920(4,Health_Ratio()<=Rules->unknown_1368,unknown_554.Count()>0,0);
                    if(unknown_a40774) {
                        unknown_44c920(5,Health_Ratio()<=Rules->unknown_1368,unknown_554.Count()>0,0);
                        if(unknown_a40774) {
                            unknown_44c920(6,Health_Ratio()<=Rules->unknown_1368,unknown_554.Count()>0,0);
                        }
                    }
                }
            }
        }
        int rate=control->unknown_08;
        if(Type->Normalized && state!=0)
            rate=Options.Normalize_Delay(rate);
        AnimationStage.Set_Rate(rate);
        AnimationStage.Value=control->unknown_00;
    }
}
