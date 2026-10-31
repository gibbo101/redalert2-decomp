// void DisplayClass::Unknown_0049E3B0() (0x0049E3B0)
// Centers the tactical view on the selected objects: their average
// coordinate, or with more than two of them the average of the others than
// the one farthest from it (TibSun DisplayClass::Center_Map).
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/display.hpp"
#include "shared/object.hpp"
#include "shared/tactical.hpp"
// @ref ?unknown_objects_a40c60@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00a40c60
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ?Unknown_006A66B0@Tactical@@QAEXABUCoordStruct@@@Z=006a66b0
// @ref ??0UnknownVector3@@QAE@HHH@Z=0041b630
// @ref ?Length@UnknownVector3@@QBEHXZ=0041b780

void DisplayClass::Unknown_0049E3B0()
{
    int index;

    if (unknown_objects_a40c60.Count() > 0) {
        CoordStruct center(0, 0, 0);
        for (index = 0; index < unknown_objects_a40c60.Count(); index++) {
            CoordStruct position = unknown_objects_a40c60[index]->Coord;
            center += position;
        }

        CoordStruct sum = center;

        center /= unknown_objects_a40c60.Count();

        if (unknown_objects_a40c60.Count() > 2) {
            CoordStruct farthest(0, 0, 0);
            int farthest_distance = 0;
            for (index = 0; index < unknown_objects_a40c60.Count(); index++) {
                CoordStruct position = unknown_objects_a40c60[index]->Coord;
                UnknownVector3 delta = UnknownVector3(center.X - position.X, center.Y - position.Y, center.Z - position.Z);
                int d = delta.Length();
                if (d > farthest_distance) {
                    farthest = unknown_objects_a40c60[index]->Coord;
                    farthest_distance = d;
                }
            }

            sum -= farthest;
            center = sum / (unknown_objects_a40c60.Count() - 1);
        }

        unknown_tactical_83996c->Unknown_006A66B0(center);
    }
}
