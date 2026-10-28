// CCINIClass::Put_Anim_Target_List (0x0046B680).
// Layout and behaviour: shared/ccini_class.hpp; TargetClass in
// CCINIClass_Get_Anim_Target_List_0046b460.cpp.

bool CCINIClass::Put_Anim_Target_List(char const *section, char const *entry, TypeList<int> const &list)
{
    char buffer[512] = "";
    for (int index = 0; index < list.Count(); index++) {
        if (buffer[0] != '\0') {
            strcat(buffer, ",");
        }
        TargetClass target;
        target = TargetClass(list[index]);
        AbstractTypeClass *type = target.As_TechnoType();
        strcat(buffer, type->ID);
    }
    return Put_String(section, entry, buffer);
}
