// Rect __fastcall Coord_Bounds_005d4f20(DynamicVectorClass<ObjectClass *> const &objects) (0x005D4F20)
// The X/Y rectangle the objects' coordinates span (left, top, width, height), from the first object's
// coordinate grown over the list from its end. Nothing calls it directly; name and purpose hypotheses.
// The unit's earlier sources define the vector and dynamic vector accessors.
#include "shared/object.hpp"
#include "shared/vector_class.hpp"
#include "shared/rect.hpp"

Rect __fastcall Coord_Bounds_005d4f20(DynamicVectorClass<ObjectClass *> const &objects)
{
    Rect bounds(0, 0, 0, 0);
    if (objects.Count() > 0) {
        bounds.X = CoordStruct(objects[0]->Coord).X;
        bounds.Y = CoordStruct(objects[0]->Coord).Y;
        for (int index = objects.Count() - 1; index >= 0; index--) {
            CoordStruct coord = objects[index]->Coord;
            if (coord.X < bounds.X) {
                bounds.Width += bounds.X - coord.X;
                bounds.X = coord.X;
            }
            if (coord.Y < bounds.Y) {
                bounds.Height += bounds.Y - coord.Y;
                bounds.Y = coord.Y;
            }
            if (coord.X > bounds.X + bounds.Width) {
                bounds.Width = coord.X - bounds.X;
            }
            if (coord.Y > bounds.Y + bounds.Height) {
                bounds.Height = coord.Y - bounds.Y;
            }
        }
    }
    return bounds;
}
