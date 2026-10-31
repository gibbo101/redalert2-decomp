// VectorClass<rc_ptr<WorldDominationTour::Conflict>>::VectorClass(unsigned, rc_ptr<Conflict> const *) (0x00727040).
// The generic body of shared/vector_class.hpp written as an explicit specialization (VC6 cannot
// explicitly instantiate a constructor alone, and the whole-class instantiation would emit an
// out-of-line ~VectorClass the original does not have). The Campaign unit's copy (the
// Campaign constructor 0x00725F40 calls it); its vtable 0x007AF034 comes with it.
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??0rc_ptr_base@@QAE@XZ=006394e0
// @ref ?Set@rc_ptr_base@@QAEXPAVReferenceCounted@@@Z=00639530
// @ref ?Fetch@?$VectorClass@V?$rc_ptr@VConflict@WorldDominationTour@@@@@@UBE?AV?$rc_ptr@VConflict@WorldDominationTour@@@@H@Z=00726a80
// @ref ??8?$VectorClass@V?$rc_ptr@VConflict@WorldDominationTour@@@@@@UBE_NABV0@@Z=00726ba0
// @ref ?Resize@?$VectorClass@V?$rc_ptr@VConflict@WorldDominationTour@@@@@@UAE_NHPBV?$rc_ptr@VConflict@WorldDominationTour@@@@@Z=00726bf0
// @ref ?Clear@?$VectorClass@V?$rc_ptr@VConflict@WorldDominationTour@@@@@@UAEXXZ=00726d10
// @ref ?ID@?$VectorClass@V?$rc_ptr@VConflict@WorldDominationTour@@@@@@UAEHABV?$rc_ptr@VConflict@WorldDominationTour@@@@@Z=00726d40
// @ref ?ID@?$VectorClass@V?$rc_ptr@VConflict@WorldDominationTour@@@@@@UAEHPBV?$rc_ptr@VConflict@WorldDominationTour@@@@@Z=00726d80
// @ref ?ID@?$VectorClass@U?$rc_ptr@VConflict@WorldDominationTour@@@@@@UAEHPBU?$rc_ptr@VConflict@WorldDominationTour@@@@@Z=00726d80
// @ref ??_G?$VectorClass@V?$rc_ptr@VConflict@WorldDominationTour@@@@@@UAEPAXI@Z=00726f10
// @ref ??_E?$VectorClass@V?$rc_ptr@VConflict@WorldDominationTour@@@@@@UAEPAXI@Z=00726f10
// @ref ??_E?$rc_ptr@VConflict@WorldDominationTour@@@@UAEPAXI@Z=00726f60
// @ref ??_7?$rc_ptr@VConflict@WorldDominationTour@@@@6B@=007aefec
// @ref ??_7?$VectorClass@V?$rc_ptr@VConflict@WorldDominationTour@@@@@@6B@=007af034
#define VECTOR_IMPLEMENT_VECTOR_CONSTRUCTOR
#define VECTOR_IMPLEMENT_VECTOR_DESTRUCTOR
#include "shared/vector_class.hpp"
class INIClass;
#include "shared/wdt_campaign_layout.hpp"

template <>
VectorClass<rc_ptr<WorldDominationTour::Conflict> >::VectorClass(unsigned size, rc_ptr<WorldDominationTour::Conflict> const *array)
    : Vector(0), VectorMax(size), IsValid(true), IsAllocated(false)
{
    if (size) {
        if (array) {
            Vector = new ((void *)array) rc_ptr<WorldDominationTour::Conflict>[size];
        } else {
            Vector = new rc_ptr<WorldDominationTour::Conflict>[size];
            IsAllocated = true;
        }
    }
}
