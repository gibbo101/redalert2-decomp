// ConvertClass::Select_Blitter_00485AA0 (0x00485AA0; TibSun Blitter_From_Flags):
// the blitter for a combination of shape drawing flags (remap 0x10, darken 1,
// translucency 2/4/6, plain 0x20, z write 0x4000, z read 0x1000|0x2000,
// alpha 0x800, warp 8); the blitters are made on first use.
Blitter *ConvertClass::Select_Blitter_00485AA0(unsigned flags)
{
    static unsigned z_read_flags = 0x3000;

    if (Blitters[0] == 0) {
        Initialize_Blitters_00483B00();
    }

    if (flags & 0x10) {
        if (flags & 0x4000) {
            if (flags & 0x800) {
                return Blitters[46];
            }
            return Blitters[20];
        }
        if (flags & z_read_flags) {
            if (flags & 0x800) {
                return Blitters[37];
            }
            return Blitters[10];
        }
        if (flags & 0x800) {
            return Blitters[26];
        }
        return Blitters[3];
    }

    switch (flags & 6) {
    case 2:
        if (flags & 0x4000) {
            if (flags & 0x800) {
                return Blitters[49];
            }
            return Blitters[23];
        }
        if (flags & z_read_flags) {
            if (flags & 8) {
                if (flags & 0x800) {
                    return Blitters[43];
                }
                return Blitters[16];
            }
            if (flags & 0x800) {
                return Blitters[40];
            }
            return Blitters[13];
        }
        if (flags & 0x800) {
            return Blitters[29];
        }
        return Blitters[6];

    case 4:
        if (flags & 0x4000) {
            if (flags & 0x800) {
                return Blitters[48];
            }
            return Blitters[22];
        }
        if (flags & z_read_flags) {
            if (flags & 8) {
                if (flags & 0x800) {
                    return Blitters[42];
                }
                return Blitters[15];
            }
            if (flags & 0x800) {
                return Blitters[39];
            }
            return Blitters[12];
        }
        if (flags & 0x800) {
            return Blitters[28];
        }
        if (flags & 0x10000) {
            return Blitters[34];
        }
        if (flags & 0x20000) {
            return Blitters[33];
        }
        return Blitters[5];

    case 6:
        if (flags & 0x4000) {
            if (flags & 0x800) {
                return Blitters[47];
            }
            return Blitters[21];
        }
        if (flags & z_read_flags) {
            if (flags & 8) {
                if (flags & 0x800) {
                    return Blitters[41];
                }
                return Blitters[14];
            }
            if (flags & 0x800) {
                return Blitters[38];
            }
            return Blitters[11];
        }
        if (flags & 0x800) {
            return Blitters[27];
        }
        return Blitters[4];
    }

    if (flags & 1) {
        if (flags & 0x4000) {
            return Blitters[19];
        }
        if (flags & z_read_flags) {
            return Blitters[9];
        }
        return Blitters[2];
    }

    if (flags & 0x20) {
        if (flags & 0x4000) {
            if (flags & 0x800) {
                return Blitters[45];
            }
            return Blitters[18];
        }
        if (flags & z_read_flags) {
            if (flags & 0x800) {
                return Blitters[36];
            }
            return Blitters[8];
        }
        if (flags & 0x800) {
            return Blitters[24];
        }
        return Blitters[0];
    }

    if (flags & 0x4000) {
        if (flags & 0x800) {
            return Blitters[45];
        }
        return Blitters[18];
    }
    if (flags & z_read_flags) {
        if (flags & 0x800) {
            return Blitters[36];
        }
        return Blitters[8];
    }
    if (flags & 0x8000) {
        return Blitters[30];
    }
    if (flags & 0x100) {
        return Blitters[31];
    }
    if (flags & 0x40) {
        return Blitters[32];
    }
    if (flags & 0x800) {
        return Blitters[25];
    }
    return Blitters[1];
}
// @ref _?z_read_flags@?1??Select_Blitter_00485AA0@ConvertClass@@QAEPAVBlitter@@I@Z@4IA=007d3a74
