#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"
#include "shared/multi_mission.hpp"
#include "shared/serial_settings.hpp"
#include "shared/session_state.hpp"

// Red Alert's Free_Scenario_Descriptions: deletes the maps, the init strings and the phone book entries.
// Deleting a MultiMission expands its destructor (GameModes, then DiskIDs); the VectorClass<Wstring> and
// VectorClass<DiskID> vtables and their slots are emitted here.
void UnknownSessionState::Free_Scenario_Descriptions()
{
    int i;

    for (int index = 0; index < Scenarios.Count(); index++) {
        delete Scenarios[index];
    }
    Scenarios.Clear();

    for (i = 0; i < InitStrings.Count(); i++) {
        delete InitStrings[i];
    }
    InitStrings.Clear();

    for (i = 0; i < PhoneBook.Count(); i++) {
        delete PhoneBook[i];
    }
    PhoneBook.Clear();
}
// @ref ??_7?$VectorClass@VWstring@@@@6B@=007a9644
// @ref ??_7?$VectorClass@W4DiskID@@@@6B@=007a9624
// @ref ?Clear@?$VectorClass@VWstring@@@@UAEXXZ=00673e30
// @ref ?Clear@?$VectorClass@W4DiskID@@@@UAEXXZ=00673b30
// @ref ??_G?$VectorClass@W4DiskID@@@@UAEPAXI@Z=00674790
// @ref ??_I@YGXPAXIHP6EX0@Z@Z=0040af00
// @ref ??_EWstring@@QAEPAXI@Z=0040af40
// @ref ??1Wstring@@QAE@XZ=0076d9e0
// @ref ??3@YAXPAX@Z=00781d3b
