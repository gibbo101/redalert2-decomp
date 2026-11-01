// DynamicVectorClass<SubTitle *> *SubTitleParser::Get_Sub_Titles(char const *moviename) (0x0069B6D0): the
// "<...>" entries of the movie's section up to EndMovie; 0 when there is no section or it is empty.
// @ref ??_C@_1BC@EAML@?$AAE?$AAn?$AAd?$AAM?$AAo?$AAv?$AAi?$AAe?$AA?$AA@=007f6470
// @ref ??_C@_0CC@JCPF@?$CK?$CK?$CK?$CK?$CK?5Failed?5to?5create?5SubTitle?$CB@=007f644c
// @ref ??_7?$DynamicVectorClass@PAVSubTitle@@@@6B@=007ac194
// @ref ??_G?$DynamicVectorClass@PAVSubTitle@@@@UAEPAXI@Z=0069c180
// @ref ??8?$VectorClass@PAVSubTitle@@@@UBE_NABV0@@Z=0069bfe0
// @ref ?Resize@?$DynamicVectorClass@PAVSubTitle@@@@UAE_NHPBQAVSubTitle@@@Z=0069c020
// @ref ?Clear@?$DynamicVectorClass@PAVSubTitle@@@@UAEXXZ=0069bf80
// @ref ?ID@?$DynamicVectorClass@PAVSubTitle@@@@UAEHABQAVSubTitle@@@Z=0069c0d0
// @ref ?ID@?$DynamicVectorClass@PAVSubTitle@@@@UAEHPBQAVSubTitle@@@Z=0069bfb0
// @ref ?Fetch@?$VectorClass@PAVSubTitle@@@@UBEPAVSubTitle@@H@Z=0069bfd0
DynamicVectorClass<SubTitle *> *SubTitleParser::Get_Sub_Titles(char const *moviename)
{
    DynamicVectorClass<SubTitle *> *subtitles = 0;
    if (Find_Movie_Entry(moviename) == true) {
        subtitles = new DynamicVectorClass<SubTitle *>;
        if (subtitles != 0) {
            for (;;) {
                unsigned short *string = Get_Next_Line();
                if (string == 0 || wcslen(string) <= 0) {
                    continue;
                }
                if (string[0] == '<' && string[wcslen(string) - 1] == '>') {
                    unsigned short *entry = string + 1;
                    entry[wcslen(entry) - 1] = 0;
                    wcstrim(entry);
                    if (wcslen(entry) == 0) {
                        continue;
                    }
                    SubTitle *subtitle = new SubTitle;
                    if (subtitle == 0) {
                        Debug_Printf("***** Failed to create SubTitle!\n");
                        break;
                    }
                    if (Parse_Sub_Title(entry, subtitle) == true) {
                        subtitles->Add(subtitle);
                    } else {
                        delete subtitle;
                    }
                } else if (_wcsnicmp(string, L"EndMovie", wcslen(L"EndMovie")) == 0) {
                    break;
                }
            }
            if (subtitles->Count() == 0) {
                delete subtitles;
                subtitles = 0;
            }
        }
    }
    return subtitles;
}
