// TaskForceClass::TaskForceClass(char const *ini_name) (0x006B6850)
// An empty task force named ini_name, registered in TaskForces.
#include "shared/task_force.hpp"
// @ref ??_7TaskForceClass@@6BIPersistStream@@@=007ac8a0
// @ref ??_7TaskForceClass@@6BIRTTITypeInfo@@@=007ac884
// @ref ??_7TaskForceClass@@6BINoticeSink@@@=007ac87c
// @ref ??_7TaskForceClass@@6BINoticeSource@@@=007ac874
// @ref ??0AbstractTypeClass@@QAE@PBD@Z=00410580
// @ref ?TaskForces@@3V?$DynamicVectorClass@PAVTaskForceClass@@@@A=00a40890

TaskForceClass::TaskForceClass(char const *ini_name) :
    AbstractTypeClass(ini_name),
    Group(-1),
    CountEntries(0),
    IsGlobal(0)
{
    TaskForces.Add(this);
    for (int index = 0; index < 6; index++) {
        Entries[index] = TaskForceEntryStruct(0, 0);
    }
}
