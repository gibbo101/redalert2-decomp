// ObjectClass *__fastcall Closest_Object_005d5090(DynamicVectorClass<ObjectClass *> const &objects,
//     CoordStruct const &coord) (0x005D5090)
// The object of the list nearest to coord, scanning from the end (0x0062941B calls it). The first
// distance is written out with double components (the original's Y, Z, X loads); the others go
// through Coord_Distance. Name and purpose hypotheses.
// The unit's earlier sources define the vector and dynamic vector accessors.
#include "shared/object.hpp"
#include "shared/vector_class.hpp"
#include "shared/coord_distance.hpp"

ObjectClass *__fastcall Closest_Object_005d5090(DynamicVectorClass<ObjectClass *> const &objects, CoordStruct const &coord)
{
    ObjectClass *best = 0;
    int best_distance = 99999999;
    for (int index = objects.Count() - 1; index >= 0; index--) {
        if (best == 0) {
            best = objects[index];
            CoordStruct d = coord - CoordStruct(best->Coord);
            double y = d.Y;
            double z = d.Z;
            double x = d.X;
            best_distance = (int)unknown_sqrt_4ba410(x * x + (y * y + z * z));
        } else {
            int distance = Coord_Distance(coord, CoordStruct(objects[index]->Coord));
            if (distance < best_distance) {
                best = objects[index];
                best_distance = distance;
            }
        }
    }
    return best;
}
