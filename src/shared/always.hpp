// Westwood's always.h min and max templates (TibSun always.h; the Westwood code
// uses MIN/MAX macros in its own sources and these templates where the windows.h
// macros are switched off). Do not include this after a windows.h that defines the
// min/max macros.
#ifndef RA2_SHARED_ALWAYS_HPP
#define RA2_SHARED_ALWAYS_HPP

template <class T> T min(T a, T b)
{
    if (a < b) {
        return(a);
    } else {
        return(b);
    }
}

template <class T> T max(T a, T b)
{
    if (a > b) {
        return(a);
    } else {
        return(b);
    }
}

#endif
