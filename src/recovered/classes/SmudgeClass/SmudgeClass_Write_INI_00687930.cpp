// static void __fastcall SmudgeClass::Write_INI(CCINIClass &ini) (0x00687930)
// Rewrites the [Smudge] section from the first piece of every smudged cell
// of the 512 x 512 map ("type,x,y,piece").
#include "shared/smudge.hpp"
// @ref ?unknown_smudge_section_7ab558@@3PBDB=007ab558
// @ref ??_C@_02MECO@?$CFd?$AA@=007ce9bc
// @ref ??_C@_0M@NJFN@?$CFs?0?$CFd?0?$CFd?0?$CFd?$AA@=007f4254
// @ref _sprintf=007820f4

void __fastcall SmudgeClass::Write_INI(CCINIClass &ini)
{
    ini.Clear(unknown_smudge_section_7ab558);
    int index = 0;
    for (int y = 0; y < 512; y++) {
        for (int x = 0; x < 512; x++) {
            CellClass &cell = Map_Cell(Cell((short)x, (short)y));
            if (cell.SmudgeIndex != -1 && cell.SmudgeData == 0) {
                SmudgeTypeClass *type = SmudgeTypes[cell.SmudgeIndex];
                char entry[12];
                char value[128];
                sprintf(entry, "%d", index);
                sprintf(value, "%s,%d,%d,%d", (char const *)type->ID, x, y, cell.SmudgeData);
                ini.Put_String(unknown_smudge_section_7ab558, entry, value);
                index++;
            }
        }
    }
}
