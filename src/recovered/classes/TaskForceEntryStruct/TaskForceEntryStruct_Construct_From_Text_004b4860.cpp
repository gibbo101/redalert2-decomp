#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#include "shared/task_force.hpp"
#include "shared/infantry_type.hpp"
#include "shared/unit_type.hpp"
#include "shared/aircraft_type.hpp"
extern "C" int __cdecl sscanf(char const *,char const *,...);
extern "C" char TaskForceFormat_007d6510[];
// @ref _TaskForceFormat_007d6510=007d6510
// @ref ?From_Name@InfantryTypeClass@@=0050a070
// @ref ?From_Name@UnitTypeClass@@=0070a890
// @ref ?From_Name@AircraftTypeClass@@=0041be60
// @ref ?InfantryTypes@@=00a40350
// @ref ?UnitTypes@@=00a35d48
// @ref ?AircraftTypes@@=00a3d278
TaskForceEntryStruct::TaskForceEntryStruct(char const *text):Amount(0),Type(0) {
 char name[64];
 int count;
 sscanf(text,TaskForceFormat_007d6510,&count,name);
 Amount=count;
 int index=InfantryTypeClass::From_Name(name);
 if(index!=-1) { Type=InfantryTypes[index];return; }
 index=UnitTypeClass::From_Name(name);
 if(index!=-1) { Type=UnitTypes[index];return; }
 index=AircraftTypeClass::From_Name(name);
 if(index!=-1) Type=AircraftTypes[index];
}
extern "C" int __cdecl sprintf(char *,char const *,...);
extern "C" char TaskForceText_00855960[64];
// @ref _TaskForceText_00855960=00855960
