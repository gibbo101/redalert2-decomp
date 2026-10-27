int SidebarClass::Unknown_00681980()
{
    for (int index = 0; index < 4; index++) {
        if (Column[index].BuildableCount > 0) {
            return index;
        }
    }
    return -1;
}
