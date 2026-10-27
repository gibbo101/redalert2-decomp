SidebarClass::StripClass::StripClass(InitClass const &) :
    unknown_1c(0),
    unknown_20(0),
    unknown_24(unknown_rect_ab9688),
    unknown_34(0),
    unknown_38(true),
    unknown_39(false),
    unknown_3a(false),
    unknown_3b(false),
    unknown_3c(-1),
    unknown_40(0),
    unknown_44(0),
    unknown_48(0),
    unknown_4c(0),
    BuildableCount(0)
{
    for (int index = 0; index < 75; index++) {
        Buildables[index].unknown_00 = 0;
        Buildables[index].unknown_04 = 0;
        Buildables[index].unknown_08 = 0;
        Buildables[index].Factory = 0;
    }
}
