// Apply_Endpoint_Map_0075C570: two peer records followed by random-map setup.
#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/multi_mission.hpp"
#include "shared/session_state.hpp"
#include "shared/unknown_map_generator.hpp"
#include "shared/crt_tokens.hpp"
extern "C" long __cdecl atol(char const *text);
void __fastcall Set_Player_Endpoint_0075c470(char const *name, char const *address, char const *value, char const *other);
int __fastcall Set_Channel_Player_Options_0073d550(Wstring const &name, int country, int color);
void __fastcall Do_Random_Map_00577880(HWND dialog, bool (*callback)());
extern char const random_map_file_007e16e8[]; // RandMap.Sed, existing original pool.
extern char const endpoint_delimiters_008003cc[]; // :,
extern char const field_delimiter_007ce9c0[]; // ,
// Same real container operation, with a named capacity value for this element type.
// No additional call or forced-inlining mechanism is introduced.
template<> inline bool DynamicVectorClass<MultiMission *>::Add(MultiMission *const &object)
{
    if (ActiveCount >= Length()) {
        if ((IsAllocated || !VectorMax) && GrowthStep > 0) {
            int new_length = Length();
            new_length += GrowthStep;
            if (!Resize(new_length)) return false;
        } else {
            return false;
        }
    }
    (*this)[ActiveCount++] = object;
    return true;
}
void __fastcall Apply_Endpoint_Map_0075c570(char const *text)
{
    char data[256];
    strcpy(data, text);
    char *name = strtok(data, endpoint_delimiters_008003cc);
    int country = atol(strtok(0, field_delimiter_007ce9c0));
    int color = atol(strtok(0, field_delimiter_007ce9c0));
    char *address = strtok(0, field_delimiter_007ce9c0);
    char *value = strtok(0, field_delimiter_007ce9c0);
    char *other = strtok(0, field_delimiter_007ce9c0);
    Set_Player_Endpoint_0075c470(name, address, value, other);
    Set_Channel_Player_Options_0073d550(name, country, color);
    name = strtok(0, field_delimiter_007ce9c0);
    country = atol(strtok(0, field_delimiter_007ce9c0));
    color = atol(strtok(0, field_delimiter_007ce9c0));
    address = strtok(0, field_delimiter_007ce9c0);
    value = strtok(0, field_delimiter_007ce9c0);
    other = strtok(0, field_delimiter_007ce9c0);
    Set_Player_Endpoint_0075c470(name, address, value, other);
    Set_Channel_Player_Options_0073d550(name, country, color);
    unknown_map_generator_a6fd68.SeedOptions.NumPlayers = 4;
    strcpy(unknown_session_a3d298.ScenarioFileName_658, random_map_file_007e16e8);
    unknown_session_a3d298.ScenarioIndex = -1;
    HWND dialog = (HWND)Unknown_00735940(0x11f);
    Do_Random_Map_00577880(dialog, Unknown_0073c120);
    unknown_map_generator_a6fd68.SeedOptions.Save_Or_Prompt_00578ed0(random_map_file_007e16e8);
    bool found = false;
    int index = 0;
    for (; index < unknown_session_a3d298.Scenarios.Count(); index++) {
        if (unknown_session_a3d298.Scenarios[index]->Unknown_006720C0()) {
            found = true;
            break;
        }
    }
    char *digest = Random_Map_CRC_005c8420();
    if (!found) {
        unknown_session_a3d298.Scenarios.Add(new MultiMission(random_map_file_007e16e8,
            unknown_map_generator_a6fd68.SeedOptions.DescriptionBuffer, digest, true, 0, 2, 4));
    } else {
        unknown_session_a3d298.Scenarios[index]->Set_Digest(digest);
        unknown_session_a3d298.Scenarios[index]->Set_Description_00671FA0(unknown_map_generator_a6fd68.SeedOptions.DescriptionBuffer);
    }
    delete digest;
    if (Select_Scenario_005c7c30(index) == true) unknown_session_a3d298.ScenarioIndex = index;
}
// @ref ?random_map_file_007e16e8@@3QBDB=007e16e8
// @ref ?endpoint_delimiters_008003cc@@3QBDB=008003cc
// @ref ?field_delimiter_007ce9c0@@3QBDB=007ce9c0
// @ref ?Do_Random_Map_00577880@@YIXPAUHWND__@@P6A_NXZ@Z=00577880
// @ref ?Set_Player_Endpoint_0075c470@@YIXPBD000@Z=0075c470
// @ref ?Set_Channel_Player_Options_0073d550@@YIHABVWstring@@HH@Z=0073d550
// @ref ?Save_Or_Prompt_00578ed0@MapSeedClass@@QAE_NPBD@Z=00578ed0
// @ref ?Unknown_006720C0@MultiMission@@QAE_NXZ=006720c0
// @ref ?Set_Description_00671FA0@MultiMission@@QAEXPBG@Z=00671fa0
// @ref ??0MultiMission@@QAE@PBDPBG0_N0HH@Z=00671c50
// @ref ??0Wstring@@QAE@PBD@Z=0076d920
// @ref ??1Wstring@@QAE@XZ=0076d9e0
// @ref ??2@YAPAXI@Z=00782017
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?Random_Map_CRC_005c8420@@YIPADXZ=005c8420
// @ref ?Select_Scenario_005c7c30@@YI_NH@Z=005c7c30
// @ref ?Set_Digest@MultiMission@@QAEXPBD@Z=00672050
// @ref ?Unknown_00735940@@YIPAXH@Z=00735940
// @ref ?Unknown_0073c120@@YA_NXZ=0073c120
// @ref ?unknown_map_generator_a6fd68@@3VUnknownMapGenerator@@A=00a6fd68
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref _atol=00782d72
// @ref _strtok=00782ec2
