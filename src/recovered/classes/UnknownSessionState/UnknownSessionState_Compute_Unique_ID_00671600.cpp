unsigned int Query_Free_Disk_Kilobytes_00482c80();
extern "C" char *__cdecl getenv(char const *name);
// @ref _getenv=00784e11

unsigned long UnknownSessionState::Compute_Unique_ID()
{
    unsigned long id = timeGetTime();
    unsigned long free = Query_Free_Disk_Kilobytes_00482c80();
    Add_CRC(&id, free);
    char *path = getenv("PATH");
    if (path != 0) {
        for (unsigned i = 0; i < strlen(path); i++) {
            Add_CRC(&id, path[i]);
        }
    }
    return id;
}
// @ref ??_C@_04LNMG@PATH?$AA@=007f3408
