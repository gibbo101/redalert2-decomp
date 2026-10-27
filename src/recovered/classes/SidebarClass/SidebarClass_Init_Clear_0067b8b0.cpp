void SidebarClass::Init_Clear()
{
    PowerClass::Init_Clear();
    unknown_4ee2 = true;
    unknown_4ee6 = false;
    unknown_4ee5 = false;
    for (int index = 0; index < 4; index++) {
        Column[index].Unknown_0067E770();
    }
    unknown_4ed8 = 0;
    unknown_4edc = 0;
    unknown_slot54(0);
}
