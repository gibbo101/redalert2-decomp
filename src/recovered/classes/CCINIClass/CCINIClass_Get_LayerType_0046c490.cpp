// CCINIClass::Get_LayerType (0x0046C490).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ?Name_From_Layer@@YIPBDW4LayerType@@@Z=00482fc0
// @ref ?Layer_From_Name@@YI?AW4LayerType@@PBD@Z=00482f80

LayerType CCINIClass::Get_LayerType(char const *section, char const *entry, LayerType defvalue)
{
    char buffer[128];
    if (Get_String(section, entry, Name_From_Layer(defvalue), buffer, sizeof(buffer))) {
        return Layer_From_Name(buffer);
    }
    return defvalue;
}
