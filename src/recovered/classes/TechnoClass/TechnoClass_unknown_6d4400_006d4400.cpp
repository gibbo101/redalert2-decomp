// TechnoClass 0x006D4400 (RA2-only DistributedFire target spreading; called from slot 209
// 0x006D46D0): drops spread targets that left the candidate list, collects the candidates not
// yet fired on with their threat values, and assigns the most valuable one (all candidates
// again, after clearing the fired list, once every candidate has been fired on).
// unknown_3a8 = candidate targets, unknown_390 = their values, unknown_3c0 = targets fired on.
// The membership tests are written-out loops (an inlined ID compared with -1 does not thread
// the found branch); the two local vectors' vtables, slots and out-of-line base constructors
// are bound by @ref (they are emitted outside their home population).
#include "shared/techno.hpp"
void TechnoClass::unknown_6d4400()
{
    if (unknown_3a8.Count() == 0) {
        unknown_3c0.Clear();
        return;
    }
    for (int index = unknown_3c0.Count() - 1; index >= 0; index--) {
        AbstractClass *target = unknown_3c0[index];
        bool found = false;
        for (int k = 0; k < unknown_3a8.Count(); k++) {
            if (target == unknown_3a8[k]) {
                found = true;
                break;
            }
        }
        if (!found) {
            unknown_3c0.Delete(index);
        }
    }
    DynamicVectorClass<AbstractClass *> targets;
    DynamicVectorClass<int> values;
    int fired = unknown_3c0.Count();
    if (fired > 0) {
        int count = unknown_3a8.Count();
        for (int i = 0; i < count; i++) {
            AbstractClass *target = unknown_3a8[i];
            bool found = false;
            for (int k = 0; k < fired; k++) {
                if (target == unknown_3c0[k]) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                targets.Add(target);
                values.Add(unknown_390[i]);
            }
        }
    }
    if (targets.Count() == 0) {
        unknown_3c0.Clear();
        int best = 0;
        AbstractClass *best_target = 0;
        for (int i = 0; i < unknown_3a8.Count(); i++) {
            if (unknown_390[i] > best) {
                best = unknown_390[i];
                best_target = unknown_3a8[i];
            }
        }
        unknown_slot220(best_target);
    } else {
        int best = 0;
        AbstractClass *best_target = 0;
        for (int i = 0; i < targets.Count(); i++) {
            AbstractClass *target = targets[i];
            if (values[i] > best) {
                best_target = target;
                best = values[i];
            }
        }
        unknown_slot220(best_target);
    }
}
// @ref ??0?$VectorClass@PAVAbstractClass@@@@QAE@IPBQAVAbstractClass@@@Z=004ceb90
// @ref ??0?$VectorClass@H@@QAE@IPBH@Z=0046d020
// @ref ??_7?$DynamicVectorClass@PAVAbstractClass@@@@6B@=007a177c
// @ref ??_7?$VectorClass@PAVAbstractClass@@@@6B@=007a179c
// @ref ??_7?$DynamicVectorClass@H@@6B@=0079da94
// @ref ??_7?$VectorClass@H@@6B@=0079d9d4
// @ref ??_E?$DynamicVectorClass@PAVAbstractClass@@@@UAEPAXI@Z=004cdf30
// @ref ??_G?$DynamicVectorClass@PAVAbstractClass@@@@UAEPAXI@Z=004cdf30
// @ref ??_E?$VectorClass@PAVAbstractClass@@@@UAEPAXI@Z=004cdf90
// @ref ??_G?$VectorClass@PAVAbstractClass@@@@UAEPAXI@Z=004cdf90
// @ref ??8?$VectorClass@PAVAbstractClass@@@@UBE_NABV0@@Z=004cdfe0
// @ref ?Resize@?$DynamicVectorClass@PAVAbstractClass@@@@UAE_NHPBQAVAbstractClass@@@Z=004ce160
// @ref ?Clear@?$DynamicVectorClass@PAVAbstractClass@@@@UAEXXZ=004cde30
// @ref ?ID@?$DynamicVectorClass@PAVAbstractClass@@@@UAEHABQAVAbstractClass@@@Z=004ce260
// @ref ?ID@?$DynamicVectorClass@PAVAbstractClass@@@@UAEHPBQAVAbstractClass@@@Z=004cde60
// @ref ?Fetch@?$VectorClass@PAVAbstractClass@@@@UBEPAVAbstractClass@@H@Z=004cde80
// @ref ?Resize@?$VectorClass@PAVAbstractClass@@@@UAE_NHPBQAVAbstractClass@@@Z=004ce020
// @ref ?Clear@?$VectorClass@PAVAbstractClass@@@@UAEXXZ=004ce0d0
// @ref ?ID@?$VectorClass@PAVAbstractClass@@@@UAEHABQAVAbstractClass@@@Z=004ce100
// @ref ?ID@?$VectorClass@PAVAbstractClass@@@@UAEHPBQAVAbstractClass@@@Z=004ce140
// @ref ??_E?$DynamicVectorClass@H@@UAEPAXI@Z=0046cf50
// @ref ??_G?$DynamicVectorClass@H@@UAEPAXI@Z=0046cf50
// @ref ??_E?$VectorClass@H@@UAEPAXI@Z=0046da70
// @ref ??_G?$VectorClass@H@@UAEPAXI@Z=0046da70
// @ref ??8?$VectorClass@H@@UBE_NABV0@@Z=0046d070
// @ref ?Resize@?$DynamicVectorClass@H@@UAE_NHPBH@Z=0046d250
// @ref ?Clear@?$DynamicVectorClass@H@@UAEXXZ=0046cc80
// @ref ?ID@?$DynamicVectorClass@H@@UAEHABH@Z=0046d350
// @ref ?ID@?$DynamicVectorClass@H@@UAEHPBH@Z=0046ccb0
// @ref ?Fetch@?$VectorClass@H@@UBEHH@Z=0046ccd0
// @ref ?Resize@?$VectorClass@H@@UAE_NHPBH@Z=0046d0b0
// @ref ?Clear@?$VectorClass@H@@UAEXXZ=0046d160
// @ref ?ID@?$VectorClass@H@@UAEHABH@Z=0046d190
// @ref ?ID@?$VectorClass@H@@UAEHPBH@Z=0046d1d0
