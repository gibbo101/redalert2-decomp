#ifndef RA2_SHARED_VIDEO_MODE_SIZE_HPP
#define RA2_SHARED_VIDEO_MODE_SIZE_HPP
// Original mode-query allocates8bytes per entry and passes8to qsort.
// Both comparisons in its comparator are signed32-bit.
struct VideoModeSize { int Width; int Height; };
#endif
