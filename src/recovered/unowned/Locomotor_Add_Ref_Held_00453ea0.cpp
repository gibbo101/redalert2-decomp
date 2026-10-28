// Adds one reference to a held locomotor; compiler COM support reconstructed from original operations.
// OriginalBuilding4496B1 supplies its FootClass::Locomotor holder at+564.
// The zero-stack-argument member versus freefastcall spelling is not distinguishable at this ABI.
#include "shared/foot.hpp"
void __fastcall Locomotor_Add_Ref_Held_00453ea0(
    UnknownComPtr<ILocomotion, &unknown_uuid_ILocomotion_7ce600> const &holder)
{
    if (holder.Pointer != 0) {
        holder.Pointer->AddRef();
    }
}
