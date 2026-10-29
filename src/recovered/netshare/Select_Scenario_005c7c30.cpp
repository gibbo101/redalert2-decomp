// bool Select_Scenario_005c7c30(int index) (0x005C7C30)
// Selects the multiplayer map with this unknown_multi_missions_a3d8d8 index (-1 clears the
// selection). A map file that is not available asks for its disk (or reports
// TXT_UNABLE_READ_SCENARIO when files come from the hard disk); the session takes the map's
// name, file name, digest, official flag and file size, and the player rows are the map's slot limit
// (Scenario_Slot_Limit_005c65a0).
#include "shared/lobby.hpp"
#include "shared/multi_mission.hpp"
#include "shared/cc_file_class.hpp"
#include "shared/cd.hpp"
#include "shared/ww_message_box.hpp"
#include "shared/multiplayer_game_mode.hpp"
#include "shared/id_source.hpp"
// @ref ??_C@_06DN@TXT_OK?$AA@=007db8f4
// @ref ??_C@_0BE@EJOA@D?3?2Ra2?2netshare?4cpp?$AA@=007e6ebc
// @ref ??_C@_0BJ@IMPI@TXT_UNABLE_READ_SCENARIO?$AA@=007e7180
// @ref ??_C@_13ECNF@?$AA?5?$AA?$AA@=007d64f4

bool __fastcall Select_Scenario_005c7c30(int index)
{
    if (index == -1) {
        unknown_session_a3d298.ScenarioFileName_658[0] = 0;
        unknown_session_a3d298.ScenarioDigest_85a[0] = 0;
        unknown_session_a3d298.ScenarioFileLength_87c = 0;
        unknown_session_a3d298.ScenarioIsOfficial_880 = false;
        unknown_int_a3db1c = 0;
        unknown_map_name_a3d342[0] = 0;
        return false;
    }
    bool missing = !CCFileClass(unknown_session_a3d298.Scenarios[index]->unknown_58).Is_Available();
    if (missing) {
        if (CD::RequiredCD != -2) {
            if (!unknown_session_a3d298.Scenarios[index]->Unknown_00671F00(Unknown_0046E4C0(60))
                && !CD().Force_Available(unknown_session_a3d298.Scenarios[index]->Unknown_00671F90())) {
                return false;
            }
        } else {
            WWMessageBox(L" ").Process(StringTable::Load_String("TXT_UNABLE_READ_SCENARIO", 0, "D:\\Ra2\\netshare.cpp", 0xCF0),
                StringTable::Load_String("TXT_OK", 0, "D:\\Ra2\\netshare.cpp", 0xCF0), 0, 0, false);
            return false;
        }
    }
    wcscpy(unknown_map_name_a3d342, unknown_session_a3d298.Scenarios[index]->Description);
    strcpy(unknown_session_a3d298.ScenarioDigest_85a, unknown_session_a3d298.Scenarios[index]->unknown_15c);
    strcpy(unknown_session_a3d298.ScenarioFileName_658, unknown_session_a3d298.Scenarios[index]->unknown_58);
    strcpy(unknown_id_source_a3d290->FileName, unknown_session_a3d298.ScenarioFileName_658);
    unknown_session_a3d298.ScenarioIsOfficial_880 = unknown_session_a3d298.Scenarios[index]->unknown_17c;
    int players = Scenario_Slot_Limit_005c65a0(index);
    unknown_int_a3db1c = players;
    unknown_session_a3d298.ScenarioFileLength_87c = CCFileClass(unknown_session_a3d298.ScenarioFileName_658).Size();
    unknown_session_a3d298.ScenarioFileLength_87c = CCFileClass(unknown_session_a3d298.ScenarioFileName_658).Size();
    return true;
}
// @ref ??_EWstring@@QAEPAXI@Z=0040af40
// @ref ??_I@YGXPAXIHP6EX0@Z@Z=0040af00
