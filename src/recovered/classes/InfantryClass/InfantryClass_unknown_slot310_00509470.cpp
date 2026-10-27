// bool InfantryClass::unknown_slot310() (0x00509470, slot 310)
// Whether a Deployer type is playing one of the deploy sequences (27-30).
#include "shared/infantry.hpp"

bool InfantryClass::unknown_slot310()
{
    return Type->Deployer && (Sequence == 27 || Sequence == 28 || Sequence == 29 || Sequence == 30);
}
