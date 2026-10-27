// CCINIClass::Calculate_Message_Digest (0x0046C260).
// Layout and behaviour: shared/ccini_class.hpp, shared/sha_pipe.hpp.
// @ref ??_7SHAPipe@@6B@=0079d994
// @ref ??_ESHAPipe@@UAEPAXI@Z=0046cb90
// @ref ??_GSHAPipe@@UAEPAXI@Z=0046cb90
// @ref ?End@Pipe@@UAEHXZ=0046cb80
// @ref ?Flush@Pipe@@UAEHXZ=0060eb10
// @ref ?Put@SHAPipe@@UAEHPBXH@Z=00675380
// @ref ?Put_To@Pipe@@UAEXPAV1@@Z=0060eaa0
// @ref ?Result@SHAPipe@@QBEHPAX@Z=006753b0
// @ref ?Clear@INIClass@@QAE_NPBD0@Z=0050b9a0
// @ref ??1Pipe@@UAE@XZ=0060ea60
// @ref ?Save@INIClass@@QBEHAAVPipe@@@Z=0050c620

void CCINIClass::Calculate_Message_Digest()
{
    SHAPipe sha;
    INIClass::Save(sha);
    sha.Result(Digest);
    IsDigestValid = true;
}
