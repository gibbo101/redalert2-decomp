void SidebarClass::StripClass::Unknown_00682400(int id, int delay)
{
    for (int index = 0; index < 75; index++) {
        if (Buildables[index].unknown_00 == id) {
            Buildables[index].unknown_2c = Frame + delay;
            return;
        }
    }
}
