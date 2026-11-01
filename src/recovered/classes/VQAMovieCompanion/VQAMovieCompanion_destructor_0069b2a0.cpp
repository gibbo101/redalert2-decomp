// VQAMovieCompanion::~VQAMovieCompanion() (0x0069B2A0): deletes the subtitles, their list and the surface.
VQAMovieCompanion::~VQAMovieCompanion()
{
    if (SubTitles != 0) {
        for (int index = 0; index < SubTitles->Count(); index++) {
            SubTitle *subtitle = (*SubTitles)[index];
            if (subtitle != 0) {
                delete subtitle;
            }
        }
        delete SubTitles;
    }
    delete unknown_10;
}
