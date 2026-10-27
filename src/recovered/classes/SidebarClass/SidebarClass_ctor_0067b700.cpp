SidebarClass::SidebarClass() :
    unknown_4ed8(0),
    unknown_4edc(0),
    unknown_4ee0(false),
    unknown_4ee1(false),
    unknown_4ee2(true),
    unknown_4ee4(false),
    unknown_4ee5(false),
    unknown_4ee6(false)
{
    for (int index = 0; index < 4; index++) {
        new (&Column[index]) StripClass(InitClass());
    }
}
