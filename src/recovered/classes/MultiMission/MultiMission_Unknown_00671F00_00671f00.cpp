bool MultiMission::Unknown_00671F00(int cd)
{
    if (cd == -2) {
        return RawFileClass(unknown_58).Is_Available();
    }
    if (Is_On_Disk(DiskIDs, (DiskID)-1)) {
        return true;
    }
    if (Is_On_Disk(DiskIDs, (DiskID)cd)) {
        return true;
    }
    return false;
}
// @ref ??0RawFileClass@@QAE@PBD@Z=00638b40
// @ref ??1RawFileClass@@UAE@XZ=00638ac0
