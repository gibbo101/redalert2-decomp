// FactoryClass production frame, original282+6; primary RTTI virtualslot23.
#include "shared/factory_class.hpp"
// @ref ?Value@?$CDTimerClass@VFrameTimerClass@@@@QBEJXZ=00453eb0
inline bool Factory_Can_Advance_Production(FactoryClass const &factory)
{
    return !factory.unknown_6c && (factory.Object!=0 || factory.unknown_64!=0) && !factory.Is_Complete_004B9900();
}
void FactoryClass::AI()
{
    if(Factory_Can_Advance_Production(*this)) {
        if(StageClass::Advance_Stage_When_Ready()) {
            unknown_59=true;
            int amount=Cost_Per_Tick_004B9950();
            if(amount>=UnspentCost) amount=UnspentCost;
            if(amount>Owner->Available_Money()) {
                unknown_58=true;
                Stage=(int)((unsigned int)Stage-1U);
            } else {
                Owner->Unknown_004E5280(amount);
                unknown_58=false;
                UnspentCost=(int)((unsigned int)UnspentCost-(unsigned int)amount);
            }
            if(Stage==54) {
                unknown_6c=true;
                Set_Rate(0);
                Owner->Unknown_004E5280(UnspentCost);
                UnspentCost=0;
            }
        }
    }
}
