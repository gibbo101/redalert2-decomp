// 0043B660: selected-building text and the cameo of a spied-on factory's product.
#include "shared/building.hpp"
#include "shared/house.hpp"
#include "shared/house_type.hpp"
#include "shared/factory_class_decl.hpp"
// Declaration-only use of the canonical palette.hpp shape API.
// The caller needs pointers to these real classes, not their full file/palette internals.
struct ShapeFileStruct;
class ConvertClass;
class Surface;
void __fastcall CC_Draw_Shape(Surface *surface, ConvertClass *drawer, ShapeFileStruct const *shape, int frame,
    Point2D const &point, Rect const &window, int flags, int unknown8, int unknown9, int unknown10,
    int brightness, int unknown12, int unknown13, Point2D offset);
extern ConvertClass *unknown_drawer_8323c4;
// @ref ?unknown_drawer_8323c4@@=008323c4
// @ref ?unknown_surface_83995c@@=0083995c
void BuildingClass::Draw_Selection_Overlay_0043b660(Point2D const &point, Rect const &bounds)
{
    unknown_slot104();
    if (unknown_77 && (House->Is_Ally(unknown_player_a35db4) ||
        (unknown_1a8 & (1 << unknown_player_a35db4->Type->House)))) {
        Point2D text = point + Point2D(-10, 10);
        // Slot251's existing declaration carries the three physical pointer words.
        unknown_slot251(text, point, bounds);
    }
    if ((unknown_1a8 & (1 << unknown_player_a35db4->Type->House)) && unknown_77) {
        FactoryClass *factory;
        if (House->unknown_func_4f52f0()) factory = House->unknown_func_4eb580(Type->Factory, Type->Naval, 0);
        else factory = static_cast<FactoryClass *>(unknown_41c);
        if (factory) {
            TechnoClass *product = factory->Get_Object();
            if (product) {
                CC_Draw_Shape(unknown_surface_83995c, unknown_drawer_8323c4,
                    reinterpret_cast<ShapeFileStruct const *>(product->unknown_slot32()->unknown_slot38()),
                    0, point, bounds, 0xe00, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
            }
        }
    }
}
