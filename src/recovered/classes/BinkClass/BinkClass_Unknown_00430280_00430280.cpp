// void BinkClass::Unknown_00430280(int x, int y) (0x00430280)
// Places the movie at x, y, clipped to the target surface.
#include "shared/movie.hpp"

void BinkClass::Unknown_00430280(int x, int y)
{
    Area = Intersect(Target->Get_Rect(), Rect(x, y, Handle->Width, Handle->Height), 0, 0);
}
