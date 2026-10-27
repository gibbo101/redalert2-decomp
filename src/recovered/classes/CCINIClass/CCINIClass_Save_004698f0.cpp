// CCINIClass::Save (0x004698F0).
// Layout and behaviour: shared/ccini_class.hpp, shared/ccini_extra.hpp.
// @ref ?Put_UUBlock@INIClass@@QAE_NPBDPBXH@Z=0050cfc0
// @ref ??1FilePipe@@UAE@XZ=00773790
// @ref ??_7FilePipe@@6B@=0079d9bc
// @ref ??_EFilePipe@@UAEPAXI@Z=0046cbd0
// @ref ??_GFilePipe@@UAEPAXI@Z=0046cbd0
// @ref ?End@FilePipe@@UAEHXZ=007737c0
// @ref ?Put@FilePipe@@UAEHPBXH@Z=007737f0

int CCINIClass::Save(FileClass &file, bool withdigest)
{
    FilePipe pipe(file);
    return Save(pipe, withdigest);
}
