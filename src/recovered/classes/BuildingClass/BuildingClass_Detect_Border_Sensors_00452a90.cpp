// Test the foundation border for sensors belonging to another house.
#include "shared/building.hpp"
#include "shared/building_map.hpp"
#include "shared/cell.hpp"
// @ref ?unknown_slot161@TechnoClass@@=006c8ef0
// @ref ?Width@BuildingTypeClass@@=00458930
// @ref ?Foundation_Height@BuildingTypeClass@@=00458940
// @ref ?unknown_471660@CellClass@@=00471660
// @ref ?Cell_Infantry@CellClass@@=00473ed0
bool BuildingClass::unknown_slot161()
{
    if(TechnoClass::unknown_slot161()) goto detected;
    {
        Cell origin=unknown_slot104();
        int width=Type->Width();
        int height=Type->Foundation_Height(false);
        for(int x=-1;x<=width;++x) {
            for(int y=-1;y<=height;++y) {
                TechnoClass *object=static_cast<TechnoClass *>(Cell_At(Cell((short)(origin.X+x),(short)(origin.Y+y))).unknown_471660(Point2D(0,0),false,0));
                if(object==this) object=static_cast<TechnoClass *>(Cell_At(Cell((short)(origin.X+x),(short)(origin.Y+y))).Cell_Infantry(false));
                if(object && object->House!=House && object->unknown_slot32()->Sensors) goto detected;
            }
        }
        return false;

    }
detected:
    return true;
}
