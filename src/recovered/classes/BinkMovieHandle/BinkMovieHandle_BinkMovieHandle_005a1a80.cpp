// BinkMovieHandle::BinkMovieHandle(BinkClass *bink) (0x005A1A80)
// @ref ??_7BinkMovieHandle@@6B@=007a6684
#include "shared/movie.hpp"

BinkMovieHandle::BinkMovieHandle(BinkClass *bink)
{
    Bink = bink;
    Width = Bink->Handle->Width;
    Height = Bink->Handle->Height;
}
