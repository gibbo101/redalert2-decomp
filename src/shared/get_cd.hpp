// GetCDClass: the CD drives found at start-up ("GetCDClass constructor" in its debug
// output, 0x004D2940). Hypothesis: Westwood's drive enumerator; the drives are the
// letters (as 0..25) of the CD-ROM drives, first C: to Z:, else A: and B:.
#ifndef RA2_SHARED_GET_CD_HPP
#define RA2_SHARED_GET_CD_HPP

class GetCDClass {
public:
    GetCDClass();                   // 0x004D2940
    ~GetCDClass();                  // 0x004D2A10 (empty)

    int Drives[26];                 // +0x00 (only the first 26 bytes are set to -1)
    int Count;                      // +0x68
    int Cursor;                     // +0x6C
};

// The CD drive list (0x00A408A8; CD_Search_Disk 0x004985C0 reads it as
// cd_drives_00a408a8).
extern GetCDClass CDList;

#endif
