// VQMovieHandle::VQMovieHandle(VQAMovie *movie) (0x005A17B0)
// Wraps an opened VQA movie and takes its frame size from the player.
// @ref ??_7VQMovieHandle@@6B@=007a6624
// @ref ?Unknown_0071D300@VQAClass@@QAEHXZ=0071d300
// @ref ?Unknown_0071D310@VQAClass@@QAEHXZ=0071d310
#include "shared/movie.hpp"

VQMovieHandle::VQMovieHandle(VQAMovie *movie) :
    Finished(false)
{
    Movie = movie;
    Width = Movie->Player->Unknown_0071D300();
    Height = Movie->Player->Unknown_0071D310();
}
