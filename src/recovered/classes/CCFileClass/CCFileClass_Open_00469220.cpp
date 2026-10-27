// CCFileClass::Open(int) (0x00469220, virtual slot 7)
// Writes, and names found on disk, open normally. A name found only inside
// a mixfile opens the archive with a bias window over the member, or, when
// the archive is cached in memory, serves the member from that memory.
#include "shared/cc_file_class.hpp"
#include "shared/mix_file_class.hpp"
#include "shared/crt_new.hpp"

int CCFileClass::Open(int rights)
{
    Close();
    if ((rights & FILE_RIGHTS_WRITE) || CDFileClass::Is_Available()) {
        return CDFileClass::Open(rights);
    }
    MixFileClass<CCFileClass> *mixfile = 0;
    void *pointer = 0;
    long length = 0;
    long start = 0;
    if (MixFileClass<CCFileClass>::Offset(File_Name(), &pointer, &mixfile, &start, &length)) {
        if (pointer == 0 && mixfile != 0) {
            char *name = _strdup(File_Name());
            Open(mixfile->Filename, FILE_RIGHTS_READ);
            IsDisabled = true;
            Set_Name(name);
            IsDisabled = false;
            free(name);
            Bias(0);
            Bias(start, length);
            Seek(0, FILE_SEEK_START);
        } else {
            new (&Data) ::Buffer(pointer, length);
            Position = 0;
        }
        return true;
    }
    return CDFileClass::Open(rights);
}
