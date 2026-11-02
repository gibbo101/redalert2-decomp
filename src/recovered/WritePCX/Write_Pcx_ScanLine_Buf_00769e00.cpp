// int __fastcall Write_Pcx_ScanLine_Buf_00769e00(int scansize, char *ptr, char *buffer) (0x00769E00): run-length
// encodes one scan line into buffer and returns the byte count (the hi-colour planes of Write_PCX_File).
// The full-run code is read through a cast pointer (a load from 0x007AF9F0, not a folded constant).

int __fastcall Write_Pcx_ScanLine_Buf_00769e00(int scansize, char *ptr, char *buffer)
{
    unsigned char last = *ptr;
    unsigned char rle = 1;
    unsigned char c;
    int size = 0;

    for (int i = 1; i < scansize; i++) {
        unsigned char color = (unsigned char)(0xff & *++ptr);
        if (color == last) {
            rle++;
            if (rle == rle_max_run) {
                buffer[size++] = *(unsigned char *)&rle_full_run;
                buffer[size++] = color;
                rle = 0;
            }
        } else {
            if (rle) {
                if (rle == 1 && (rle_code != (rle_code & last))) {
                    buffer[size++] = last;
                } else {
                    c = (unsigned char)(rle | rle_code);
                    buffer[size++] = c;
                    buffer[size++] = last;
                }
            }
            last = color;
            rle = 1;
        }
    }

    if (rle) {
        if (rle == 1 && (rle_code != (rle_code & last))) {
            buffer[size++] = last;
        } else {
            c = (unsigned char)(rle | rle_code);
            buffer[size++] = c;
            buffer[size++] = last;
        }
    }
    return size;
}
