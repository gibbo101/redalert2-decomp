// MSBinkAnim::MSBinkAnim(Wstring const &name, Surface *surface, DynamicVectorClass<MSAnim *> *anims, Rect const &rect, bool unknown_38) (0x005AD8E0)
// Opens the movie (when a name is given) and places it at the rectangle.
#include "shared/ms_anim.hpp"
#include "shared/wstring.hpp"
// @ref ??_7MSBinkAnim@@6B@=007a6ddc
// @ref ??0BinkClass@@QAE@PBDPAVSurface@@@Z=0042fea0
// @ref ?Unknown_00430280@BinkClass@@QAEXHH@Z=00430280

MSBinkAnim::MSBinkAnim(Wstring const &name, Surface *surface, DynamicVectorClass<MSAnim *> *anims,
                       Rect const &rect, bool unknown_38) :
    MSAnim(rect.X, rect.Y),
    Movie(0),
    Target(surface),
    MovieRect(rect),
    Anims(anims),
    unknown_38(unknown_38)
{
    if (name.Length() > 0) {
        Movie = new BinkClass(name.Peek_Buffer(), surface);
        Movie->Unknown_00430280(rect.X, rect.Y);
    }
}
