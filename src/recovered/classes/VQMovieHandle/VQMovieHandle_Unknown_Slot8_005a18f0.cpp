// void VQMovieHandle::Unknown_Slot8(int unknown) (0x005A18F0)
// Passes the value to the movie's companion object.
// @ref ?Unknown_0069B4F0@VQAMovieCompanion@@QAEXH@Z=0069b4f0
#include "shared/movie.hpp"

void VQMovieHandle::Unknown_Slot8(int unknown)
{
    Movie->Companion->Unknown_0069B4F0(unknown);
}
