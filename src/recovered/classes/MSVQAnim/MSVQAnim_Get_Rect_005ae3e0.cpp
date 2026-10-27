// Rect MSVQAnim::Get_Rect() (0x005AE3E0, slot 6)
// The movie's destination rectangle, or an empty one without a movie.
#include "shared/ms_anim.hpp"
// @ref _?$S9@?1??Get_Rect@MSVQAnim@@UAE?AVRect@@XZ@4EA=00a71800
// @ref _?empty@?1??Get_Rect@MSVQAnim@@UAE?AVRect@@XZ@4V3@A=00a71818
// @ref _atexit=0078298a

Rect MSVQAnim::Get_Rect()
{
    static Rect empty(0, 0, 0, 0);
    return Movie != 0 ? Movie->Dest : empty;
}
