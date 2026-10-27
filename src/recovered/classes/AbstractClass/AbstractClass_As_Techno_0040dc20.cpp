// Actual direct dependency of canonical Aircraft setter, original0040DC20.
// Original guarded Kind_Of classifier: 41code+3alignment+8jump+15index=67body,13NOP.
// Existing AbstractClass::As_Techno spelling/Techno subtype remain source hypotheses.
#include "shared/techno.hpp"

TechnoClass *AbstractClass::As_Techno()
{
    if (this) {
        switch (Kind_Of()) {
        case 1:
        case 2:
        case 6:
        case 15:
            return static_cast<TechnoClass *>(this);
        }
    }
    return 0;
}
