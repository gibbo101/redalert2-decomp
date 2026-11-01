// Westwood's INCDEC.H templates (wwlib; TibSun incdec.h): increment and decrement for enumerated
// types such as FacingType (`for (FacingType facing = FACING_N; facing < FACING_COUNT; facing++)`).
#ifndef RA2_SHARED_INCDEC_HPP
#define RA2_SHARED_INCDEC_HPP

template<class T> inline T operator++(T &a)
{
    a = (T)((int)a + (int)1);
    return a;
}

template<class T> inline T operator++(T &a, int)
{
    T aa = a;
    a = (T)((int)a + (int)1);
    return aa;
}

template<class T> inline T operator--(T &a)
{
    a = (T)((int)a - (int)1);
    return a;
}

template<class T> inline T operator--(T &a, int)
{
    T aa = a;
    a = (T)((int)a - (int)1);
    return aa;
}

#endif
