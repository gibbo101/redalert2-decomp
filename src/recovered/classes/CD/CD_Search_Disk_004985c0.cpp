#include "shared/cd.hpp"
#include "shared/cd_file_class.hpp"
// Searches the current, previous and enumerated CD drives, prompting as needed.
// Layout hypothesis: 26 drive indices, count and rotating cursor at +68/+6C.
struct CDDriveList_004985C0 {
    int Drives[26];
    int Count;
    int Cursor;
    int Next() {
        if (Count != 0) {
            if (Cursor == Count) Cursor=0;
            return Drives[Cursor++];
        }
        return -1;
    }
};
extern CDDriveList_004985C0 cd_drives_00a408a8;
extern int loaded_cd_007d5c54;
// @ref ?cd_drives_00a408a8@@3UCDDriveList_004985C0@@A=00a408a8
// @ref ?loaded_cd_007d5c54@@3HA=007d5c54
bool CD::Unknown_004985C0(int cd)
{
    int found_drive = 0;
    if (cd != -2) {
        int drive = CDFileClass::CurrentCDDrive;
        int index = Get_CD_Index(drive,60);
        if (index <= -1 || (cd != index && cd != -1) || (found_drive = drive) == 0) {
            if (CDFileClass::LastCDDrive != 0 && CDFileClass::LastCDDrive != CDFileClass::CurrentCDDrive) {
                index = Get_CD_Index(CDFileClass::LastCDDrive,600);
                if (index > -1) {
                    if (cd == index) goto available;
                    if (cd == -1) goto done;
                }
            }
            int timeout = 120;
            for (;;) {
                for (int i=0;i<cd_drives_00a408a8.Count;++i) {
                    drive = cd_drives_00a408a8.Next();
                    index = Get_CD_Index(drive,timeout);
                    if (index > -1 && (cd == index || cd == -1)) {
                        found_drive = drive;
                        break;
                    }
                }
                if (found_drive > 0) break;
                if (!Insert_Disk(cd)) return false;
                timeout = 300;
            }
            CDFileClass::Set_CD_Drive(found_drive);
            CDFileClass::Refresh_Search_Drives();
        }
    available:
        if (cd > -1 && loaded_cd_007d5c54 != cd) {
            loaded_cd_007d5c54 = cd;
            return Swap_Disk(cd);
        }
    }
done:
    return true;
}
