// static void __fastcall SmudgeClass::Read_INI(CCINIClass &ini) (0x006877F0)
// Creates the smudges listed in the [Smudge] section ("type,x,y,piece");
// only first pieces (piece 0) are created, the type marks its other cells.
#include "shared/smudge.hpp"
#include "shared/crt_tokens.hpp"
// @ref ?unknown_smudge_section_7ab558@@3PBDB=007ab558
// @ref ??_C@_01KMAE@?0?$AA@=007ce9c0
// @ref ??0SmudgeClass@@QAE@PAVSmudgeTypeClass@@ABUCoordStruct@@H@Z=006875c0
// @ref ?From_Name@SmudgeTypeClass@@SIHPBD@Z=00687f60
// @ref _strtok=00782ec2
// @ref _atoi=00782dfd
// @ref ??2@YAPAXI@Z=00782017

void __fastcall SmudgeClass::Read_INI(CCINIClass &ini)
{
    int count = ini.Entry_Count(unknown_smudge_section_7ab558);
    for (int index = 0; index < count; index++) {
        char const *entry = ini.Get_Entry(unknown_smudge_section_7ab558, index);
        char buffer[128];
        ini.Get_String(unknown_smudge_section_7ab558, entry, 0, buffer, sizeof(buffer));
        int type = SmudgeTypeClass::From_Name(strtok(buffer, ","));
        if (type != -1) {
            char *token = strtok(0, ",");
            if (token != 0) {
                Cell cell;
                short x = atoi(token);
                cell.Y = atoi(strtok(0, ","));
                cell.X = x;
                token = strtok(0, ",");
                if (token == 0 || atoi(token) == 0) {
                    new SmudgeClass(SmudgeTypes[type], CoordStruct(cell.X * 256 + 128, cell.Y * 256 + 128, 0), -1);
                }
            }
        }
    }
}
