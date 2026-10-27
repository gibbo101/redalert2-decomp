// INIClass::Load (0x0050BBE0)
// Loads the INI text of a file (see Load(Straw &)) by reading it
// through a FileStraw.
#include "shared/ini_class.hpp"

int INIClass::Load(FileClass &file, bool keep_comments)
{
    FileStraw straw(file);
    return Load(straw, keep_comments);
}
