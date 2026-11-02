// CCINIClass *MultiplayerGameMode::unknown_ini_5b7840() -- 0x005B7840
// The mode's INI: made on first use and read from the mode's INI file when it is there. The
// three-argument CCINIClass::Load is called directly (the two-argument inline wrapper would
// spend the inline budget that expands the List/GenericList constructors here).
#include "shared/multiplayer_game_mode.hpp"
#include "shared/ccini_class.hpp"
#include "shared/cc_file_class.hpp"

CCINIClass *MultiplayerGameMode::unknown_ini_5b7840()
{
    if (unknown_ini_38 == 0) {
        unknown_ini_38 = new CCINIClass;
        CCFileClass file(unknown_2c);
        if (file.Is_Available()) {
            unknown_ini_38->Load(file, false, false);
        }
    }
    return unknown_ini_38;
}
