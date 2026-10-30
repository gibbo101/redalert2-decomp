// VQA32 player library: IFF chunk identifiers of the VQA file format.
// Names follow the Tiberian Sun reconstruction of the same library
// (vqafile.h, iff.h); values are verified against the RA2 loader.
#ifndef RA2_SHARED_VQA_IFF_HPP
#define RA2_SHARED_VQA_IFF_HPP

// Chunk identifier from four characters, first character in the low byte.
#define MAKE_ID(a, b, c, d) ((long)((long)(d) << 24) | ((long)(c) << 16) | ((long)(b) << 8) | (long)(a))

// Byte-swaps a big-endian IFF chunk size.
#define REVERSE_LONG(id) (unsigned long)((((unsigned long)(id) >> 24) & 0x000000FFL) | \
    (((unsigned long)(id) >> 8) & 0x0000FF00L) | (((unsigned long)(id) << 8) & 0x00FF0000L) | \
    (((unsigned long)(id) << 24) & 0xFF000000L))

#define ID_FORM MAKE_ID('F', 'O', 'R', 'M')
#define ID_WVQA MAKE_ID('W', 'V', 'Q', 'A')
#define ID_VQHD MAKE_ID('V', 'Q', 'H', 'D')
#define ID_FINF MAKE_ID('F', 'I', 'N', 'F')
#define ID_VQFR MAKE_ID('V', 'Q', 'F', 'R')
#define ID_VQFK MAKE_ID('V', 'Q', 'F', 'K')
#define ID_VQFL MAKE_ID('V', 'Q', 'F', 'L')
#define ID_CBF0 MAKE_ID('C', 'B', 'F', '0')
#define ID_CBFZ MAKE_ID('C', 'B', 'F', 'Z')
#define ID_CBP0 MAKE_ID('C', 'B', 'P', '0')
#define ID_CBPZ MAKE_ID('C', 'B', 'P', 'Z')
#define ID_CPL0 MAKE_ID('C', 'P', 'L', '0')
#define ID_CPLZ MAKE_ID('C', 'P', 'L', 'Z')
#define ID_VPT0 MAKE_ID('V', 'P', 'T', '0')
#define ID_VPTZ MAKE_ID('V', 'P', 'T', 'Z')
#define ID_VPTK MAKE_ID('V', 'P', 'T', 'K')
#define ID_VPTD MAKE_ID('V', 'P', 'T', 'D')
#define ID_VPTR MAKE_ID('V', 'P', 'T', 'R')
#define ID_VPRZ MAKE_ID('V', 'P', 'R', 'Z')
#define ID_VPDZ MAKE_ID('V', 'P', 'D', 'Z')
#define ID_VPKZ MAKE_ID('V', 'P', 'K', 'Z')
#define ID_SND0 MAKE_ID('S', 'N', 'D', '0')
#define ID_SND1 MAKE_ID('S', 'N', 'D', '1')
#define ID_SND2 MAKE_ID('S', 'N', 'D', '2')
#define ID_SNA0 MAKE_ID('S', 'N', 'A', '0')
#define ID_SNA1 MAKE_ID('S', 'N', 'A', '1')
#define ID_SNA2 MAKE_ID('S', 'N', 'A', '2')
#define ID_SN2J MAKE_ID('S', 'N', '2', 'J')
#define ID_CLIP MAKE_ID('C', 'L', 'I', 'P')
#define ID_LINF MAKE_ID('L', 'I', 'N', 'F')
#define ID_LINH MAKE_ID('L', 'I', 'N', 'H')
#define ID_LIND MAKE_ID('L', 'I', 'N', 'D')
#define ID_CINF MAKE_ID('C', 'I', 'N', 'F')
#define ID_CINH MAKE_ID('C', 'I', 'N', 'H')
#define ID_CIND MAKE_ID('C', 'I', 'N', 'D')
#define ID_PINF MAKE_ID('P', 'I', 'N', 'F')
#define ID_PINH MAKE_ID('P', 'I', 'N', 'H')
#define ID_PIND MAKE_ID('P', 'I', 'N', 'D')
#define ID_MFCI MAKE_ID('M', 'F', 'C', 'I')
#define ID_MFCH MAKE_ID('M', 'F', 'C', 'H')
#define ID_MFCD MAKE_ID('M', 'F', 'C', 'D')
#define ID_MFCT MAKE_ID('M', 'F', 'C', 'T')
#define ID_MSCI MAKE_ID('M', 'S', 'C', 'I')
#define ID_MSCH MAKE_ID('M', 'S', 'C', 'H')
#define ID_MSCT MAKE_ID('M', 'S', 'C', 'T')

#endif
