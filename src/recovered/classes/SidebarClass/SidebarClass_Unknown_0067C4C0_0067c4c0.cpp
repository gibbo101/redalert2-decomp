bool SidebarClass::Unknown_0067C4C0(int control)
{
    bool old = unknown_4ee5;
    if (control == -1) {
        control = !old;
    }
    switch (control) {
    case 1:
        unknown_4ee5 = true;
        break;
    default:
        unknown_4ee5 = false;
        break;
    }
    if (old != unknown_4ee5) {
        Flag_To_Redraw(false);
        unknown_4ee2 = true;
        if (!unknown_4ee5) {
            Set_Default_Mouse(0, false);
        }
    }
    return old;
}
