// 0x0051FC60: true exactly when the original DWORD at 0x00A5193C equals one.
// The state's role and the original developer name remain unknown.
extern "C" unsigned int DAT_00a5193c;

bool Unknown_0051FC60()
{
    return DAT_00a5193c == 1;
}
