// ScriptTypeClass::ScriptTypeClass(char const *ini_name) (0x00668A20)
// An empty script type, registered in ScriptTypes; ArrayIndex is its index.
#include "shared/script.hpp"
// @ref ??0AbstractTypeClass@@QAE@PBD@Z=00410580
// @ref ??_7ScriptTypeClass@@6BIPersistStream@@@=007a93b8
// @ref ??_7ScriptTypeClass@@6BIRTTITypeInfo@@@=007a939c
// @ref ??_7ScriptTypeClass@@6BINoticeSink@@@=007a9394
// @ref ??_7ScriptTypeClass@@6BINoticeSource@@@=007a938c
// @ref ?ScriptTypes@@3V?$DynamicVectorClass@PAVScriptTypeClass@@@@A=00866258

ScriptTypeClass::ScriptTypeClass(char const *ini_name) :
    AbstractTypeClass(ini_name),
    IsGlobal(0),
    MissionCount(0)
{
    ScriptTypes.Add(this);
    ArrayIndex = ScriptTypes.ID(this);
}
