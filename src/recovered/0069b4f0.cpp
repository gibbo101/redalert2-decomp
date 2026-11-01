// void VQAMovieCompanion::Unknown_0069B4F0(int unknown) (0x0069B4F0): the callback that shows subtitles
// instead of the surface.
void VQAMovieCompanion::Unknown_0069B4F0(int unknown)
{
    Callback = (void (__fastcall *)(SubTitle *))unknown;
}
