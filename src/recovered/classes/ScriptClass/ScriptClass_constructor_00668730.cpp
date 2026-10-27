// ScriptClass::ScriptClass(ScriptTypeClass *type) (0x00668730)
// A script positioned before the first line of type; registered in Scripts.
#include "shared/script.hpp"
// @ref ??0AbstractClass@@QAE@XZ=0040ff10
// @ref ??_7ScriptClass@@6BIPersistStream@@@=007a9328
// @ref ??_7ScriptClass@@6BIRTTITypeInfo@@@=007a930c
// @ref ??_7ScriptClass@@6BINoticeSink@@@=007a9304
// @ref ??_7ScriptClass@@6BINoticeSource@@@=007a92fc
// @ref ?Scripts@@3V?$DynamicVectorClass@PAVScriptClass@@@@A=00839900

ScriptClass::ScriptClass(ScriptTypeClass *type) :
    Class(type),
    unknown_28(0),
    CurrentMission(-1)
{
    Scripts.Add(this);
}
