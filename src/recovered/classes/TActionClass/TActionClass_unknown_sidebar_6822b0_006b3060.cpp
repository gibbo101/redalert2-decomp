// bool TActionClass::unknown_sidebar_6822b0(...) (0x006B3060)
// Map.Unknown_006822B0 with techno type Data.Value (when valid) and +0x48; true then.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/taction.hpp"
#include "shared/techno_type.hpp"
#include "shared/map_view.hpp"
// @ref ?Unknown_006822B0@SidebarClass@@QAEXPAVTechnoTypeClass@@H@Z=006822b0

bool TActionClass::unknown_sidebar_6822b0(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    if (Data.Value < TechnoTypes.Count() && Data.Value >= 0) {
        Map.Unknown_006822B0(TechnoTypes[Data.Value], unknown_48);
        return true;
    }
    return false;
}


