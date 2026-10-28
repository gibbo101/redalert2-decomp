// CCINIClass::Put_Target_Type (0x0046C3B0).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.

bool CCINIClass::Put_Target_Type(char const *section, char const *entry, TargetClass const &target)
{
    AbstractTypeClass *type = target.As_TechnoType();
    if (type != 0) {
        return Put_String(section, entry, type->ID);
    }
    return Put_String(section, entry, "<none>");
}
