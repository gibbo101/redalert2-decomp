// void GraphicMenuImageItem::Play_Sound(int unknown) (0x004DFE70)
// Plays the hover sound, then, when the item's movie file exists, plays that movie
// (a 640x400 VQA) on the background surface and waits for it (up to 300000 ms).
// The argument is the screen engine (MSEngine *) whose animation list the movie joins.
#include "shared/graphic_menu.hpp"
#include "shared/cc_file_class.hpp"

void GraphicMenuImageItem::Play_Sound(int unknown)
{
    MSEngine *engine = (MSEngine *)unknown;
    GraphicMenuItem::Play_Sound(unknown);
    if (CCFileClass(unknown_name_34).Is_Available()) {
        MSVQAnim *movie = new MSVQAnim(unknown_name_34, unknown_surface_839958, &engine->Anims, true);
        if (movie != 0) {
            engine->Wait_For(movie, 300000);
        }
    }
}
