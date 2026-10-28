// GetCDClass: the CD drives found at start-up ("GetCDClass constructor" in its debug
// output, 0x004D2940). Hypothesis: Westwood's drive enumerator; the drives are the
// letters (as 0..25) of the CD-ROM drives, first C: to Z:, else A: and B:.
#ifndef RA2_SHARED_GET_CD_HPP
#define RA2_SHARED_GET_CD_HPP

class GetCDClass {
public:
    GetCDClass();                   // 0x004D2940

    int Drives[26];                 // +0x00 (only the first 26 bytes are set to -1)
    int Count;                      // +0x68
    int Cursor;                     // +0x6C
};

#endif
