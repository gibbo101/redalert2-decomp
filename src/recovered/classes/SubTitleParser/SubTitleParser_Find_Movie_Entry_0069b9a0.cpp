// bool SubTitleParser::Find_Movie_Entry(char const *moviename) (0x0069B9A0): skips to the line
// "BeginMovie <moviename>".
// @ref ??_C@_1BG@DJJM@?$AAB?$AAe?$AAg?$AAi?$AAn?$AAM?$AAo?$AAv?$AAi?$AAe?$AA?$AA@=007f649c
// @ref ??_C@_0BG@LAIB@Found?5movie?5entry?5?$CFs?6?$AA@=007f6484
bool SubTitleParser::Find_Movie_Entry(char const *moviename)
{
    unsigned short name[32];
    mbstowcs(name, moviename, 32);
    unsigned short *string;
    do {
        string = Get_Next_Line();
        if (string != 0 && _wcsnicmp(string, L"BeginMovie", wcslen(L"BeginMovie")) == 0) {
            unsigned short *ptr = wcschr(string, ' ');
            if (ptr != 0) {
                wcstrim(ptr);
                if (_wcsicmp(ptr, name) == 0) {
                    Debug_Printf("Found movie entry %s\n", moviename);
                    return true;
                }
            }
        }
    } while (string != 0);
    return false;
}
