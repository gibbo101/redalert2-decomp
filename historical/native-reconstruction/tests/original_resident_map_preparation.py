# SPDX-License-Identifier: GPL-3.0-or-later
"""Original ordinary map pass over supplied general resident TMP records."""
from original_map_preparation import MapPreparationOracle, TYPES, REGISTRY, pack

IMAGES = 0x3200000

class ResidentMapPreparationOracle(MapPreparationOracle):
    def __init__(self, exe):
        super().__init__(exe)
        self.u.mem_map(IMAGES, 0x400000)

    def install_types(self, types):
        # Host pointer relocation, not original loading/heap/type construction.
        for i, row in enumerate(types):
            present, columns, rows, width, height, *samples = row
            p, image = TYPES+i*1024, IMAGES+i*4096
            self.put(p, 0x7a51a8)
            self.put(p+0xa4, image if present else 0)
            self.put(p+0x298, -1)
            self.put(REGISTRY+i*4, p)
            self.u.mem_write(image, bytes(4096))
            self.u.mem_write(image, pack([columns, rows, width, height]))
            for j in range(columns*rows):
                valid, land, ramp, y, extra_y, extra = samples[j*6:j*6+6]
                sub = image+256+j*64
                self.put(image+16+j*4, sub if valid else 0)
                self.put(sub+4, y)
                self.put(sub+0x18, extra_y)
                self.put(sub+0x24, extra)
                self.u.mem_write(sub+0x29, bytes([land, ramp]))
        self.u.mem_write(REGISTRY+len(types)*4, b'\xa7'*64)
        return IMAGES, len(types)*4096
