// int __fastcall SideClass::Find_Index(char const *name) (0x0067AF90)

int __fastcall SideClass::Find_Index(char const *name)
{
    for (int index = 0; index < Sides.Count(); index++) {
        if (_stricmp(Sides[index]->ID, name) == 0) {
            return index;
        }
    }
    return -1;
}
