// HRESULT __stdcall SuperWeaponTypeClass::Load(IStream *stream) (0x0069F230)
// Rebuilds the type in place, fixes up the pointers and reloads the sidebar icon.
// @ref ??_C@_04BOIE@?4SHP?$AA@=007ced14
// @ref ??_C@_0L@PJAI@XXICON?4SHP?$AA@=007d61bc

HRESULT __stdcall SuperWeaponTypeClass::Load(IStream *stream)
{
    HRESULT result = AbstractClass::Load(stream);
    if (FAILED(result)) {
        return result;
    }
    new (this) SuperWeaponTypeClass(NoInitClass());
    SwizzleManager.Swizzle((void **)&WeaponType);
    SwizzleManager.Swizzle((void **)&AuxBuilding);
    char fullname[512];
    _makepath(fullname, 0, 0, SidebarImage, ".SHP");
    SidebarIcon = MixFileClass<CCFileClass>::Retrieve(fullname);
    if (SidebarIcon == 0) {
        SidebarIcon = MixFileClass<CCFileClass>::Retrieve("XXICON.SHP");
    }
    return S_OK;
}
