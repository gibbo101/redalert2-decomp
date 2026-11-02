// The version class (RTTI VersionClass; Tiberian Sun's version.cpp): the program version
// (1.006, MAJOR 1 / MINOR 6), the VERSION.TXT label, version clipping for multiplayer
// and the Windows ProductVersion text. The global object is version_object_00a40c88.
#define RA2_VERSION_CLASS_MEMBERS
#include "shared/lobby.hpp"
#include "shared/raw_file_class.hpp"
#include "shared/crt_string.hpp"
#include "shared/win32_api.hpp"
#include "shared/win32_window.hpp"
// @ref ??_7UnknownVersionObject@@6B@=007a2abc
// @ref ??_GUnknownVersionObject@@UAEPAXI@Z=004d4980
// @ref ??_EUnknownVersionObject@@UAEPAXI@Z=004d4980
// @ref ??0RawFileClass@@QAE@PBD@Z=00638b40
// @ref ?Is_Available@RawFileClass@@UAE_NH@Z=00638ca0
// @ref ?Read@RawFileClass@@UAEJPAXJ@Z=00638d90
// @ref ??1RawFileClass@@UAE@XZ=00638ac0
// @ref ??_C@_0M@CNNK@VERSION?4TXT?$AA@=007f991c
// @ref ?version_object_00a40c88@@3UUnknownVersionObject@@A=00a40c88

UnknownVersionObject::UnknownVersionObject() :
    Version(0),
    MajorVer(0),
    MinorVer(0),
    MinClipVer(0),
    MaxClipVer(0),
    VersionInit(false),
    MajorInit(false),
    MinorInit(false),
    TextInit(false)
{
    VersionText[0] = '\0';
    VersionName[0] = '\0';
}
