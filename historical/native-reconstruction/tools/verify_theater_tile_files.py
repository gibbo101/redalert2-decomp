#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-3.0-or-later
"""Pin complete nonlazy theater binding and actual loaded TMP preparation."""
import hashlib
import pefile
from verify_theater_tile_inputs import verify as verify_theater,RANGES as THEATER_RANGES
from verify_tile_image import verify as verify_image,RANGES as IMAGE_RANGES
RANGES={**THEATER_RANGES,**IMAGE_RANGES}
def verify(data):
    theater=verify_theater(data);image=verify_image(data);pe=pefile.PE(data=data)
    extensions=[]
    for i in range(3):
        raw=pe.get_data(0x79abac+i*104-0x400000,8)
        if raw!=((b'TEM\0MMT\0',b'SNO\0MMS\0',b'URB\0MMU\0')[i]):raise ValueError('Theater extensions differ')
        extensions.append(raw.hex())
    return {'ranges':{**theater['ranges'],**image['ranges']},'extensions':extensions,'color_constants':image['constants'],
      'scope':'Complete nonlazy theater root and actual type constructor/color preparation. Supplied INI/base constructor/file cache/heap/vector storage/graphics/timer services; theater 0..2, no animation, bounded contiguous base/a..z images, local relative TMP references. Compare ordered file requests, primary/all-type membership, next links, remaining variant counts, selected metadata and every prepared color word. No original file cache/archive/INI parsing, lazy path, cell variant selection, ownership/lifetime, full map initialization, runtime or frame claim.'}
