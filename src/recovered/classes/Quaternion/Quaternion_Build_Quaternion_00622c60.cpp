// ?Build_Quaternion@@YI?AVQuaternion@@ABVMatrix3D@@@Z (0x00622C60)
// The rotation quaternion of a matrix's rotation part.
#include "shared/quaternion.hpp"

Quaternion __fastcall Build_Quaternion(Matrix3D const &mat)
{
    float const *m = (float const *)&mat;
    double s, tr;
    int i, j, k;
    Quaternion q;
    int tab1[3] = { (4 * 0) + 0, (4 * 1) + 1, (4 * 2) + 2 };
    int tab2[3][4] = {
        { (4 * 0) + 0, (4 * 0) + 1, (4 * 0) + 2, (4 * 0) + 3 },
        { (4 * 1) + 0, (4 * 1) + 1, (4 * 1) + 2, (4 * 1) + 3 },
        { (4 * 2) + 0, (4 * 2) + 1, (4 * 2) + 2, (4 * 2) + 3 },
    };

    tr = m[tab1[0]] + (m[tab1[1]] + m[tab1[2]]);
    if (tr == 0.0) {
        return q;
    }

    if (tr > 0.0) {
        s = Fast_Sqrt(tr + 1.0);
        q[3] = (s * 0.5);
        s = 0.5 / s;
        q[0] = (m[tab2[2][1]] - m[tab2[1][2]]) * s;
        q[1] = (m[tab2[0][2]] - m[tab2[2][0]]) * s;
        q[2] = (m[tab2[1][0]] - m[tab2[0][1]]) * s;
    } else {
        i = 0;
        if ((double)m[tab1[1]] > (double)m[tab1[i]]) i = 1;
        if ((double)m[tab1[2]] > (double)m[tab1[i]]) i = 2;
        switch (i) {
            case 1:
                j = 2;
                k = 0;
                break;
            case 2:
                j = 0;
                k = 1;
                break;
            default:
                j = 1;
                k = 2;
                break;
        }
        double di = m[tab1[i]];
        double dj = m[tab1[j]];
        double dk = m[tab1[k]];
        s = Fast_Sqrt(di - (dj + dk) + 1.0);
        q[i] = (s * 0.5);
        s = 0.5 / s;
        q[3] = (m[tab2[k][j]] - m[tab2[j][k]]) * s;
        q[j] = (m[tab2[j][i]] + m[tab2[i][j]]) * s;
        q[k] = (m[tab2[k][i]] + m[tab2[i][k]]) * s;
    }
    return q;
}
// @ref ?Fast_Sqrt@@YAMN@Z=004ba410
// @ref __real@8@00000000000000000000=0079b610
// @ref __real@8@3ffe8000000000000000=0079a728
// @ref __real@8@3fff8000000000000000=0079a708
