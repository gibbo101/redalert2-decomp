// Reads the version label from VERSION.TXT (empty without the file), dropping trailing
// carriage returns (0x00713090).
void UnknownVersionObject::Read_Text_String()
{
    RawFileClass file("VERSION.TXT");

    if (file.Is_Available()) {
        file.Read(VersionText, sizeof(VersionText));
        VersionText[sizeof(VersionText) - 1] = '\0';
        while (VersionText[strlen(VersionText) - 1] == '\r') {
            VersionText[strlen(VersionText) - 1] = '\0';
        }
    } else {
        VersionText[0] = '\0';
    }
}
