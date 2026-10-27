// CCINIClass::Get_Integers (0x0046C880).
// Layout and behaviour: shared/ccini_class.hpp.

void CCINIClass::Get_Integers(char const *section, char const *entry, int &first, int &second, int &third)
{
    char buffer[512] = "";
    if (Get_String(section, entry, "", buffer, sizeof(buffer))) {
        char *token = strtok(buffer, ",");
        if (token != 0) {
            first = atoi(token);
        }
        token = strtok(0, ",");
        if (token != 0) {
            second = atoi(token);
        }
        token = strtok(0, ",");
        if (token != 0) {
            third = atoi(token);
        }
    }
}
