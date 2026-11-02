// bool __fastcall Write_PCX_File(FileClass &file, Surface &pic, PaletteClass *palette) (0x007698C0):
// writes the surface as a PCX file (Westwood WRITEPCX.CPP, TibSun shape): a 128-byte header, the
// RLE scan lines (three colour planes per line for a hi-colour surface) and, for an 8-bit surface,
// the palette. Opens the file for writing when it is not open yet. Returns true on an error.
#include "shared/raw_file_class.hpp"
#include "shared/surface.hpp"
#include "shared/hicolor.hpp"
#include "shared/crt_string.hpp"
// @ref _memmove=00783290
// @ref _rle_full_run=007af9f0

class PaletteClass;

#pragma pack(push, 1)
struct PCXRGB {
    unsigned char Red;
    unsigned char Green;
    unsigned char Blue;
};

// The PCX file header (Westwood PCX.H).
struct PCX_HEADER {
    char id;
    char version;
    char encoding;
    char pixelsize;
    unsigned short x;
    unsigned short y;
    unsigned short width;
    unsigned short height;
    short xres;
    short yres;
    PCXRGB ega_palette[16];
    char nothing;
    unsigned char color_planes;
    unsigned short byte_per_line;
    short palette_type;
    short horz_screen_size;
    short vert_screen_size;
    char filler[54];
};
#pragma pack(pop)

static void __fastcall Write_Pcx_ScanLine(FileClass &file, int scansize, char *ptr);
int __fastcall Write_Pcx_ScanLine_Buf_00769e00(int scansize, char *ptr, char *buffer);

static unsigned char const rle_code = 0xC0;                         // Run code.
static unsigned char const rle_max_run = 0x2F;                      // Maximum run allowed.
static unsigned char const rle_full_run = (rle_max_run | rle_code); // Full character run (0x007AF9F0).

bool __fastcall Write_PCX_File(FileClass &file, Surface &pic, PaletteClass *palette)
{
    unsigned char palcopy[256 * sizeof(PCXRGB)];
    char *ptr;
    PCX_HEADER header = {
        10,
        5,
        1,
        8,
        0,
        0,
        (unsigned short)(pic.Get_Width() - 1),
        (unsigned short)(pic.Get_Height() - 1),
        (short)pic.Get_Width(),
        (short)pic.Get_Height(),
        {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
         {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
        0,
        (unsigned char)(pic.Bytes_Per_Pixel() == 2 ? 3 : 1),
        (unsigned short)pic.Get_Width(),
        1,
        (short)pic.Get_Width(),
        (short)pic.Get_Height(),
        {0}
    };

    bool open = false;
    if (!file.Is_Open()) {
        file.Open(FILE_RIGHTS_WRITE);
        open = true;
    }
    file.Write(&header, sizeof(header));

    if (pic.Bytes_Per_Pixel() == 2) {
        unsigned char *line1 = new unsigned char[pic.Get_Width()];
        unsigned char *line2 = new unsigned char[pic.Get_Width()];
        unsigned char *line3 = new unsigned char[pic.Get_Width()];
        unsigned char *file_ptr = new unsigned char[pic.Get_Width() * ((4 + 1) * 2)];
        for (int line = 0; line < header.height + 1; line++) {
            unsigned short *buffer = (unsigned short *)pic.Lock(Point2D(0, line));
            if (buffer == 0) {
                return true;
            }
            for (int j = 0; j < pic.Get_Width(); j++) {
                RGBClass color = Unpack_Hicolor_Pixel(*buffer++);
                line1[j] = color.Red;
                line2[j] = color.Green;
                line3[j] = color.Blue;
            }
            pic.Unlock();
            int size = 0;
            size += Write_Pcx_ScanLine_Buf_00769e00(pic.Get_Width(), (char *)line1, (char *)file_ptr + size);
            size += Write_Pcx_ScanLine_Buf_00769e00(pic.Get_Width(), (char *)line2, (char *)file_ptr + size);
            size += Write_Pcx_ScanLine_Buf_00769e00(pic.Get_Width(), (char *)line3, (char *)file_ptr + size);
            file.Write(file_ptr, size);
        }
        delete [] line1;
        delete [] line2;
        delete [] line3;
        delete [] file_ptr;
    } else {
        for (int line = 0; line < header.height + 1; line++) {
            ptr = (char *)pic.Lock(Point2D(0, line));
            Write_Pcx_ScanLine(file, header.byte_per_line, ptr);
            pic.Unlock();
        }
    }

    unsigned char ender = 0x0C;
    file.Write(&ender, sizeof(ender));

    if (pic.Bytes_Per_Pixel() == 1) {
        memmove(palcopy, palette, sizeof(palcopy));
        file.Write(palcopy, sizeof(palcopy));
    }

    if (open) {
        file.Close();
    }
    return false;
}

// Writes one scan line RLE-compressed to the file (inline in Write_PCX_File).
static void __fastcall Write_Pcx_ScanLine(FileClass &file, int scansize, char *ptr)
{
    unsigned char last = *ptr;
    unsigned char rle = 1;
    unsigned char c;

    for (int i = 1; i < scansize; i++) {
        unsigned char color = (unsigned char)(0xff & *++ptr);
        if (color == last) {
            rle++;
            if (rle == rle_max_run) {
                file.Write(&rle_full_run, sizeof(rle_full_run));
                file.Write(&color, sizeof(color));
                rle = 0;
            }
        } else {
            if (rle) {
                if (rle == 1 && (rle_code != (rle_code & last))) {
                    file.Write(&last, sizeof(last));
                } else {
                    c = (unsigned char)(rle | rle_code);
                    file.Write(&c, sizeof(c));
                    file.Write(&last, sizeof(last));
                }
            }
            last = color;
            rle = 1;
        }
    }

    if (rle) {
        if (rle == 1 && (rle_code != (rle_code & last))) {
            file.Write(&last, sizeof(last));
        } else {
            c = (unsigned char)(rle | rle_code);
            file.Write(&c, sizeof(c));
            file.Write(&last, sizeof(last));
        }
    }
}
