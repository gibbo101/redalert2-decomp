// bool SuperWeaponTypeClass::Read_INI(CCINIClass &ini) (0x0069F450)
// @ref ?Find_Or_Make@WeaponTypeClass@@SIPAV1@PBD@Z=00733ea0
// @ref ?BuildingTypeClass_Find_Or_Make@@YIPAVBuildingTypeClass@@PBD@Z=0045e0e0
// @ref ?Get_ActionType@CCINIClass@@QBEHPBD0H@Z=0046a3a0
// @ref ??_C@_0L@GMMI@WeaponType?$AA@=007cdcb4
// @ref ??_C@_06NMFG@Action?$AA@=007cdcc8
// @ref ??_C@_09MOIO@IsPowered?$AA@=007f6734
// @ref ??_C@_0BF@DLOH@DisableableFromShell?$AA@=007f671c
// @ref ??_C@_08OABN@PreClick?$AA@=007f6710
// @ref ??_C@_09IJCF@PostClick?$AA@=007f6704
// @ref ??_C@_09BEDK@ShowTimer?$AA@=007f66f8
// @ref ??_C@_04FCOP@Type?$AA@=007d9eec
// @ref ??_C@_0N@NMHE@PreDependent?$AA@=007f66e8
// @ref ??_C@_0M@GIBM@AuxBuilding?$AA@=007f66dc
// @ref ??_C@_0P@INHI@UseChargeDrain?$AA@=007f66cc
// @ref ??_C@_0O@NIFP@ManualControl?$AA@=007f66bc
// @ref ??_C@_0N@OABL@RechargeTime?$AA@=007f66ac
// @ref ??_C@_0N@KDGD@SidebarImage?$AA@=007f669c
// @ref __real@4@4008e100000000000000=007ac328
// @ref ??_C@_04BOIE@?4SHP?$AA@=007ced14
// @ref ??_C@_0L@PJAI@XXICON?4SHP?$AA@=007d61bc

bool SuperWeaponTypeClass::Read_INI(CCINIClass &ini)
{
    if (AbstractTypeClass::Read_INI(ini)) {
    char buffer[128];
    WeaponTypeClass *weapon = WeaponType;
    WeaponType = ini.Get_String(ID, "WeaponType", "", buffer, sizeof(buffer)) ? WeaponTypeClass::Find_Or_Make(buffer) : weapon;
    Action = ini.Get_ActionType(ID, "Action", Action);
    IsPowered = ini.Get_Bool(ID, "IsPowered", IsPowered);
    DisableableFromShell = ini.Get_Bool(ID, "DisableableFromShell", DisableableFromShell);
    PreClick = ini.Get_Bool(ID, "PreClick", PreClick);
    PostClick = ini.Get_Bool(ID, "PostClick", PostClick);
    ShowTimer = ini.Get_Bool(ID, "ShowTimer", ShowTimer);

    char name[40];
    ini.Get_String(ID, "Type", "", name, sizeof(name));
    if (strlen(name) != 0) {
        int type = Type_From_Name(name);
        if (type != -1) {
            Type = type;
        }
    }
    char dependent[40];
    ini.Get_String(ID, "PreDependent", "", dependent, sizeof(dependent));
    if (strlen(dependent) != 0) {
        int type = Type_From_Name(dependent);
        if (type != -1) {
            PreDependent = type;
        }
    }

    BuildingTypeClass *building = AuxBuilding;
    AuxBuilding = ini.Get_String(ID, "AuxBuilding", "", buffer, sizeof(buffer)) ? BuildingTypeClass_Find_Or_Make(buffer) : building;
    UseChargeDrain = ini.Get_Bool(ID, "UseChargeDrain", UseChargeDrain);
    ManualControl = ini.Get_Bool(ID, "ManualControl", ManualControl);
    double minutes = ini.Get_Double(ID, "RechargeTime", 0.0);
    if (minutes != 0.0) {
        RechargeTime = (float)minutes * 900.0f;
    }

    char image[256];
    ini.Get_String(ID, "SidebarImage", SidebarImage, image, sizeof(image));
    SidebarImage = image;
    char fullname[512];
    _makepath(fullname, 0, 0, SidebarImage, ".SHP");
    SidebarIcon = MixFileClass<CCFileClass>::Retrieve(fullname);
    if (SidebarIcon == 0) {
        SidebarIcon = MixFileClass<CCFileClass>::Retrieve("XXICON.SHP");
    }
    return true;
    }
    return false;
}
