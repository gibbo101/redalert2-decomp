// VQAMovieCompanion *__fastcall unknown_create_companion_69b190(char const *filename) (0x0069B190): a
// manager with the subtitles of the movie file's base name and a 640x255 16-bit surface to draw them on.
VQAMovieCompanion *__fastcall unknown_create_companion_69b190(char const *filename)
{
    if (filename == 0 || strlen(filename) == 0) {
        return 0;
    }
    VQAMovieCompanion *manager = new VQAMovieCompanion;
    if (manager != 0) {
        char name[256];
        _splitpath(filename, 0, 0, name, 0);
        if (manager->Load_Sub_Titles(name) == true) {
            BSurface *surface = new BSurface(640, 255, 2);
            if (surface != 0) {
                surface->Fill(0);
                manager->unknown_10 = surface;
            }
        }
    }
    return manager;
}
