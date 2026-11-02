// The program's ProductVersion text from its version resource, read once ("zzz" without
// one) (0x007131D0).
// @ref __imp__GetModuleFileNameA@12=0079a198
// @ref ?ProgramInstance@@3PAXA=00b26180
// @ref _GetFileVersionInfoSizeA@8=00781bf0
// @ref _GetFileVersionInfoA@16=00781bea
// @ref _VerQueryValueA@16=00781be4
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref _sprintf=007820f4
// @ref _?buffer@?1??Version_Name_007131d0@@YIPBDXZ@4PADA=007f9718
// @ref _?empty@?1??Version_Name_007131d0@@YIPBDXZ@4_NA=007f9918
// @ref ??_C@_0BJ@KCFH@?2VarFileInfo?2Translation?$AA@=007f995c
// @ref ??_C@_0CI@PPOP@?2StringFileInfo?2?$CF04d?$CF04d?2Product@=007f9934
extern "C" unsigned long __stdcall GetFileVersionInfoSizeA(char const *filename, unsigned long *handle);
extern "C" int __stdcall GetFileVersionInfoA(char const *filename, unsigned long handle, unsigned long size,
    void *data);
extern "C" int __stdcall VerQueryValueA(void const *block, char const *sub_block, void **buffer,
    unsigned int *length);

char const *__fastcall Version_Name_007131d0()
{
    static char buffer[512] = {"zzz"};
    static bool empty = true;
    int size;
    void *block;
    unsigned int translate_len;
    unsigned long handle;
    struct LANGANDCODEPAGE {
        unsigned short wLanguage;
        unsigned short wCodePage;
    } *translate;
    char query[128];
    char filename[260];

    if (empty) {
        empty = false;
        if (GetModuleFileNameA(ProgramInstance, filename, sizeof(filename)) > 0) {
            handle = 1;
            size = GetFileVersionInfoSizeA(filename, &handle);
            if (size > 0) {
                block = new unsigned char[size];
                if (GetFileVersionInfoA(filename, handle, size, block)) {
                    VerQueryValueA(block, "\\VarFileInfo\\Translation", (void **)&translate, &translate_len);
                    if (translate_len > 0) {
                        sprintf(query, "\\StringFileInfo\\%04d%04d\\ProductVersion", translate->wLanguage,
                            translate->wCodePage);
                        VerQueryValueA(block, query, (void **)&translate, &translate_len);
                        if (translate_len > 0) {
                            strcpy(buffer, (char const *)translate);
                        }
                    }
                }
                delete [] block;
            }
        }
    }
    return buffer;
}
