bool UnknownPreview_0061D430::Unknown_0061E2A0(char const *filename)
{
    CCFileClass file(filename);
    if (file.Is_Available() && file.Open(FILE_RIGHTS_READ)) {
        int percent_load = 0;
        char *buffer = 0;

        while (percent_load < 100) {
            percent_load += 25;

            int length = percent_load * file.Size() / 100;
            if (buffer != 0) {
                delete [] buffer;
            }
            buffer = new char[length + 1];
            if (buffer == 0) {
                return false;
            }

            file.Seek(0, 0);
            file.Read(buffer, length);
            buffer[length] = '\0';

            char *section = strstr(buffer, "[Map]");
            if (section != 0) {
                section[0] = '\0';
                CCINIClass ini;
                BufferStraw straw(buffer, section - buffer - 1);
                ini.Load(straw, false, false);
                bool result = Read_INI(ini);
                delete [] buffer;
                return result;
            }
        }
        delete [] buffer;
    }
    return false;
}
// @ref ??_C@_05PMLP@?$FLMap?$FN?$AA@=007ebf50
// @ref ?Read_INI@UnknownPreview_0061D430@@QAE_NABVCCINIClass@@@Z=0061ded0
// @ref ??_GCCINIClass@@UAEPAXI@Z=0040e2e0
// @ref ??0?$List@PAUINISection@INIClass@@@@QAE@XZ=00490ff0
// @ref ??_GGenericNode@@UAEPAXI@Z=0040e1d0
// @ref ??_GGenericList@@UAEPAXI@Z=0040e220
// @ref ??_G?$List@PAUINISection@INIClass@@@@UAEPAXI@Z=0040e300
// @ref ??0?$IndexClass@HPAUINISection@INIClass@@@@QAE@XZ=004910c0
// @ref ??_H@YGXPAXIHP6EX0@Z@Z=0040aed0
// @ref ??0Buffer@@QAE@PAXJ@Z=004382c0
// @ref ??0CCFileClass@@QAE@PBD@Z=00468f50
// @ref ??1Buffer@@QAE@XZ=00438410
// @ref ??1BufferIOFileClass@@UAE@XZ=0042f350
// @ref ??1INIClass@@UAE@XZ=0050b8d0
// @ref ??1Straw@@UAE@XZ=0069b010
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??_7BufferStraw@@6B@=0079e9e8
// @ref ??_7CCFileClass@@6B@=0079a6a0
// @ref ??_7CCINIClass@@6B@=0079aae4
// @ref ??_7CDFileClass@@6B@=0079a658
// @ref ??_7Straw@@6B@=0079e9f8
// @ref ?Is_Available@CCFileClass@@UAE_NH@Z=004691a0
// @ref ?Load@CCINIClass@@QAEHAAVStraw@@_N1@Z=004697e0
// @ref ?Open@CCFileClass@@UAEHH@Z=00469220
// @ref ?Read@CCFileClass@@UAEJPAXJ@Z=00469060
// @ref ?Seek@CCFileClass@@UAEJJH@Z=004690f0
// @ref ?Size@CCFileClass@@UAEJXZ=00469150
// @ref _strstr=007836b0
