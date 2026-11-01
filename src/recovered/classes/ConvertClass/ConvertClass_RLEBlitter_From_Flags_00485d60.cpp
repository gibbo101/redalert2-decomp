// ConvertClass::RLEBlitter_From_Flags_00485d60 (0x00485D60; TibSun
// RLEBlitter_From_Flags): the RLE blitter for a combination of shape drawing
// flags (see Select_Blitter_00485AA0); the blitters are made on first use.
RLEBlitter const *ConvertClass::RLEBlitter_From_Flags_00485d60(unsigned flags) const
{
    static unsigned z_read_flags = 0x3000;

    if (Blitters[0] == 0) {
        ((ConvertClass *)this)->Initialize_Blitters_00483B00();
    }

    if (flags & 0x10) {
        if (flags & 0x4000) {
            if (flags & 0x800) {
                return RLEBlitters[35];
            }
            return RLEBlitters[16];
        }
        if (flags & z_read_flags) {
            if (flags & 0x800) {
                return RLEBlitters[27];
            }
            return RLEBlitters[7];
        }
        if (flags & 0x800) {
            return RLEBlitters[22];
        }
        return RLEBlitters[2];
    }

    switch (flags & 6) {
    case 2:
        if (flags & 0x4000) {
            if (flags & 0x800) {
                return RLEBlitters[38];
            }
            return RLEBlitters[20];
        }
        if (flags & z_read_flags) {
            if (flags & 8) {
                if (flags & 0x800) {
                    return RLEBlitters[33];
                }
                return RLEBlitters[14];
            }
            if (flags & 0x800) {
                return RLEBlitters[30];
            }
            return RLEBlitters[11];
        }
        if (flags & 0x800) {
            return RLEBlitters[25];
        }
        return RLEBlitters[5];

    case 4:
        if (flags & 0x4000) {
            if (flags & 0x800) {
                return RLEBlitters[37];
            }
            return RLEBlitters[19];
        }
        if (flags & z_read_flags) {
            if (flags & 8) {
                if (flags & 0x800) {
                    return RLEBlitters[32];
                }
                return RLEBlitters[13];
            }
            if (flags & 0x800) {
                return RLEBlitters[29];
            }
            return RLEBlitters[10];
        }
        if (flags & 0x800) {
            return RLEBlitters[24];
        }
        return RLEBlitters[4];

    case 6:
        if (flags & 0x4000) {
            if (flags & 0x800) {
                return RLEBlitters[36];
            }
            return RLEBlitters[18];
        }
        if (flags & z_read_flags) {
            if (flags & 8) {
                if (flags & 0x800) {
                    return RLEBlitters[31];
                }
                return RLEBlitters[12];
            }
            if (flags & 0x800) {
                return RLEBlitters[28];
            }
            return RLEBlitters[9];
        }
        if (flags & 0x800) {
            return RLEBlitters[23];
        }
        return RLEBlitters[3];
    }

    if (flags & 1) {
        if (flags & 0x4000) {
            return RLEBlitters[17];
        }
        if (flags & z_read_flags) {
            return RLEBlitters[8];
        }
        return RLEBlitters[1];
    }

    if (flags & 0x20) {
        if (flags & 0x4000) {
            if (flags & 0x800) {
                return RLEBlitters[34];
            }
            return RLEBlitters[15];
        }
        if (flags & z_read_flags) {
            if (flags & 0x800) {
                return RLEBlitters[26];
            }
            return RLEBlitters[6];
        }
        if (flags & 0x800) {
            return RLEBlitters[21];
        }
        return RLEBlitters[0];
    }

    if (flags & 0x4000) {
        if (flags & 0x800) {
            return RLEBlitters[34];
        }
        return RLEBlitters[15];
    }
    if (flags & z_read_flags) {
        if (flags & 0x800) {
            return RLEBlitters[26];
        }
        return RLEBlitters[6];
    }
    if (flags & 0x800) {
        return RLEBlitters[21];
    }
    return RLEBlitters[0];
}
// @ref _?z_read_flags@?1??RLEBlitter_From_Flags_00485d60@ConvertClass@@QBEPBVRLEBlitter@@I@Z@4IA=007d3a78
