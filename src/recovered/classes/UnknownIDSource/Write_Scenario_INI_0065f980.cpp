// void __fastcall Write_Scenario_INI_0065f980(char const *filename, bool flag) (0x0065F980)
// Writes the scenario INI file (Westwood's Write_Scenario_INI; called by the
// map saver 0x0057823B with flag set): starts from the existing file when
// unknown_a40d13 is set, writes [Basic] and the rest of the scenario's
// sections, the preview (or the houses without flag), the map, the objects,
// the teams and AI triggers (unless flag and not unknown_a40d13), the triggers
// and tags, and saves the INI.
// @ref ?unknown_preview_a6fee4@@3PAVUnknownPreview_0061D430@@A=00a6fee4
// @ref ??0UnknownPreview_0061D430@@QAE@XZ=0061d430
// @ref ??1UnknownPreview_0061D430@@QAE@XZ=0061d440
// @ref ?Unknown_0061D660@UnknownPreview_0061D430@@QAEXXZ=0061d660
// @ref ?Write_INI_0061DC80@UnknownPreview_0061D430@@QAEXAAVCCINIClass@@@Z=0061dc80
// @ref ?Write_INI_0049D910@DisplayClass@@QAEXAAVCCINIClass@@@Z=0049d910
// @ref ?Write_INI@TubeClass@@SIXAAVCCINIClass@@@Z=006ef480
// @ref ?Unknown_00668EA0@@YIXAAVCCINIClass@@H@Z=00668ea0
// @ref ?Write_INI@OverlayClass@@SIXAAVCCINIClass@@@Z=005dba30
#include "shared/id_source.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/ccini_class.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/raw_file_class.hpp"
#include "shared/map_preview.hpp"
#include "shared/house.hpp"
#include "shared/map_view.hpp"
#include "shared/terrain.hpp"
#include "shared/unit_type.hpp"
#include "shared/infantry_type.hpp"
#include "shared/aircraft_type.hpp"
#include "shared/building_class.hpp"
#include "shared/overlay.hpp"
#include "shared/smudge.hpp"
#include "shared/tube.hpp"
#include "shared/task_force.hpp"
#include "shared/team_type.hpp"
#include "shared/ai_trigger_type.hpp"
#include "shared/trigger_type.hpp"
#include "shared/tag_type.hpp"

void __fastcall Write_Scenario_INI_0065f980(char const *filename, bool flag)
{
    CCINIClass ini;
    if (unknown_a40d13) {
        if (CCFileClass(filename).Is_Available()) {
            CCFileClass file(filename);
            ini.Load(file, true, false);
        }
    }
    unknown_id_source_a3d290->Write_Basic(ini, flag);
    if (flag) {
        if (unknown_preview_a6fee4 != 0 && unknown_preview_a6fee4->Is_Present()) {
            unknown_preview_a6fee4->Write_INI_0061DC80(ini);
        } else {
            UnknownPreview_0061D430 preview;
            preview.Unknown_0061D660();
            preview.Write_INI_0061DC80(ini);
        }
    } else {
        HouseClass::Write_Scenario_INI(ini);
    }
    Map.Write_INI_0049D910(ini);
    TerrainClass::Write_INI(ini);
    UnitClass::Write_INI(ini);
    InfantryClass::Write_INI(ini);
    AircraftClass::Write_INI_0041A6C0(ini);
    Building_Write_All_INI_0044b200(&ini);
    OverlayClass::Write_INI(ini);
    SmudgeClass::Write_INI(ini);
    TubeClass::Write_INI(ini);
    if (!flag || unknown_a40d13) {
        Unknown_00668EA0(ini, 0);
        TaskForceClass::Write_Scenario_INI(ini, 0);
        TeamTypeClass::Write_Scenario_INI(ini, 0);
        AITriggerTypeClass::Write_Scenario_INI(ini, 0);
    }
    TriggerTypeClass::Write_Scenario_INI(ini);
    TagTypeClass::Write_Scenario_INI(ini);
    RawFileClass file(filename);
    ini.Save(file, true);
}
