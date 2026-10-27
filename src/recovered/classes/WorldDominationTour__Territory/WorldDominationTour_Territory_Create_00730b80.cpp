// rc_ptr<Territory> __fastcall WorldDominationTour::Territory::Create(...) (0x00730B80)
#include "shared/world_domination_tour.hpp"

namespace WorldDominationTour {

rc_ptr<Territory> __fastcall Territory::Create(int index, INIClass const &ini, Wstring const &section,
                                               Wstring const &shape_prefix, Wstring const &name_prefix)
{
    return rc_ptr<Territory>(new Territory(index, ini, section, shape_prefix, name_prefix));
}

}
