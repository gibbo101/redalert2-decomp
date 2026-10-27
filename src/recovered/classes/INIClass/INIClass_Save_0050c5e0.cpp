// INIClass::Save (0x0050C5E0)
// Writes the database as INI text to a file through a FilePipe.
#include "shared/ini_class.hpp"

int INIClass::Save(FileClass &file) const
{
    FilePipe pipe(file);
    return Save(pipe);
}
