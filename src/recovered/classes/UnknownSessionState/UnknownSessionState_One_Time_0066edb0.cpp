// @ref _unknown_session_a3d298=00a3d298

void UnknownSessionState::One_Time()
{
    Read_Scenario_Descriptions();
    UniqueID = Compute_Unique_ID();
    Debug_Printf("Session one time init. UniqueID is %08x\n", UniqueID);
}
// @ref ??_C@_04LNMG@PATH?$AA@=007f3408
// @ref ??_C@_0CJ@CFNB@Session?5one?5time?5init?4?5UniqueID?5@=007f33dc
// @ref ?Read_Scenario_Descriptions@UnknownSessionState@@QAEXXZ=00670c50
// @ref _getenv=00784e11
// @ref ?Add_CRC@@YIXPAKK@Z=0062a340
// @ref __imp__timeGetTime@0=0079a524
// @ref ?Query_Free_Disk_Kilobytes_00482c80@@YAIXZ=00482c80
