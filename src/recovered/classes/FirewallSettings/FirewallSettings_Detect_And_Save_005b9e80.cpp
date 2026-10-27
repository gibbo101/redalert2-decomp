// Detects the firewall type once (0x005B9E80) and, when the detection found one,
// writes type and delta to [MultiPlayer] of the INI object 0x00839740 and saves RA2.INI.
#include "shared/raw_file_class.hpp"
#include "shared/ccini_class.hpp"
#include "shared/firewall_settings.hpp"
// @ref ??0RawFileClass@@QAE@PBD@Z=00638b40
// @ref ??1RawFileClass@@UAE@XZ=00638ac0
// @ref ?Put_Int@INIClass@@QAE_NPBD0HH@Z=0050d6e0
// @ref ?Save@CCINIClass@@QAEHAAVFileClass@@_N@Z=004698f0
// @ref ?Detect_005ba2c0@FirewallSettings@@QAEHPA_N@Z=005ba2c0
// @ref ?unknown_ini_839740@@3VCCINIClass@@A=00839740
// @ref ??_C@_07IBND@RA2?4INI?$AA@=007db8b8
// @ref ??_C@_0M@MLEF@MultiPlayer?$AA@=007dbce4
// @ref ??_C@_0BB@DHMB@FirewallSettings?$AA@=007e63ec
// @ref ??_C@_0O@OMOI@FirewallDelta?$AA@=007e63dc


void FirewallSettings::Detect_And_Save_005b9e80()
{
    bool found = false;
    if (unknown_00 == 0) {
        unknown_00 = Detect_005ba2c0(&found);
        if (found) {
            RawFileClass file("RA2.INI");
            unknown_ini_839740.Put_Int("MultiPlayer", "FirewallSettings", unknown_00, 0);
            unknown_ini_839740.Put_Int("MultiPlayer", "FirewallDelta", unknown_08, 0);
            unknown_ini_839740.Save(file, false);
        }
    }
}
