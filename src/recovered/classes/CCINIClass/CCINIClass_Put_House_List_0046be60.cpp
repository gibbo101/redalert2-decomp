// CCINIClass::Put_House_List (0x0046BE60; TibSun ccini.cpp): stores a list of house types as a
// comma separated list of their IDs.

bool CCINIClass::Put_House_List(char const *section, char const *entry, TypeList<int> value)
{
    char buffer[128] = "";

    for (int index = 0; index < value.Count(); index++) {
        if (buffer[0] != '\0') {
            strcat(buffer, ",");
        }
        strcat(buffer, HouseTypes[value[index]]->ID);
    }
    return Put_String(section, entry, buffer);
}
