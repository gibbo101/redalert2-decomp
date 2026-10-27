// void FootClass::unknown_4ca1a0() (0x004CA1A0; never called)
// Replaces the locomotor with a new drop pod locomotor that carries the old
// one (the new one is linked to this unit and begins piggybacking it).
#include "shared/foot.hpp"
#include "shared/locomotion.hpp"
#include "shared/droppod_locomotion.hpp"
// @ref __com_issue_error@4=00795940
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref _CLSID_DropPodLocomotionClass=007a1fb0
// @ref ?CreateInstance@?$UnknownComPtr@UILocomotion@@$1?unknown_uuid_ILocomotion_7ce600@@3UGUID@@B@@QAEJABUGUID@@PAUIUnknown@@K@Z=0041b650
// @ref _unknown_uuid_IPiggyback_7cfc30=007cfc30
// @ref ?Query@?$UnknownComPtr@UIPiggyback@@$1?unknown_uuid_IPiggyback_7cfc30@@3UGUID@@B@@QAEJABV?$UnknownComPtr@UILocomotion@@$1?unknown_uuid_ILocomotion_7ce600@@3UGUID@@B@@@Z=00454c70

extern "C" GUID const unknown_uuid_IPiggyback_7cfc30;

void FootClass::unknown_4ca1a0()
{
    UnknownComPtr<ILocomotion, &unknown_uuid_ILocomotion_7ce600> old(Locomotor);
    UnknownComPtr<ILocomotion, &unknown_uuid_ILocomotion_7ce600> pod(CLSID_DropPodLocomotionClass);
    pod.Checked()->Link_To_Object(this);
    UnknownComPtr<IPiggyback, &unknown_uuid_IPiggyback_7cfc30> piggyback(pod);
    piggyback.Checked()->Begin_Piggyback(old);
    Locomotor = pod;
}
