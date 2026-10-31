// RadioClass::RadioClass() (0x00636830): no contact (one empty radio link)
// and no messages remembered.
#include "shared/radio.hpp"
// @ref ??_7RadioClass@@6BIPersistStream@@@=007a88e8
// @ref ??_7RadioClass@@6BIRTTITypeInfo@@@=007a88cc
// @ref ??_7RadioClass@@6BINoticeSink@@@=007a88c4
// @ref ??_7RadioClass@@6BINoticeSource@@@=007a88bc
// @ref ??_7?$VectorClass@PAVTechnoClass@@@@6B@=0079a7fc
// @ref ??0MissionClass@@QAE@XZ=00594500
// @ref ??0ObjectClass@@QAE@ABVNoInitClass@@@Z=005d2500
// @ref ??_G?$VectorClass@PAVTechnoClass@@@@UAEPAXI@Z=0040bb70
// @ref ??_E?$VectorClass@PAVTechnoClass@@@@UAEPAXI@Z=0040bb70
// @ref ??8?$VectorClass@PAVTechnoClass@@@@UBE_NABV0@@Z=0040b870
// @ref ?Resize@?$VectorClass@PAVTechnoClass@@@@UAE_NHPBQAVTechnoClass@@@Z=0040b8b0
// @ref ?Clear@?$VectorClass@PAVTechnoClass@@@@UAEXXZ=0040b960
// @ref ?ID@?$VectorClass@PAVTechnoClass@@@@UAEHPBQAVTechnoClass@@@Z=0040b9d0
// @ref ?ID@?$VectorClass@PAVTechnoClass@@@@UAEHABQAVTechnoClass@@@Z=0040b990
// @ref ?Fetch@?$VectorClass@PAVTechnoClass@@@@UBEPAVTechnoClass@@H@Z=0040b600
// @ref ?unknown_radio_param_a40be0@@3HA=00a40be0

RadioClass::RadioClass() :
    RadioLinks(1)
{
    RadioLinks[0] = 0;
    for (int i = 0; i < 3; i++) {
        Old[i] = 0;
    }
}
// @ref ??_GMissionClass@@UAEPAXI@Z=00595130
// @ref ?unknown_slot122@MissionClass@@UAE_NXZ=004cdde0
// @ref ?unknown_slot67@ObjectClass@@UAEXHH@Z=00595120
// @ref ?unknown_slot151@RadioClass@@UAEHHPAHPAVTechnoClass@@@Z=00636a50
