// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/Bytes.hpp"
namespace ra2 {
struct ShpFrame {
    int x=0,y=0,width=0,height=0;
    Bytes pixels; // Exact cropped dimensions; no OpenRA export padding.
    int format=3; // Keep raw (1) versus RLE (3): their clipped depth phases differ.
    // Retain encoded row boundaries: an auxiliary-depth span's left skip can
    // consume the remainder of a zero run without advancing its depth pointer.
    std::vector<Bytes> rleRows;
};
struct ShpImage {
    int width=0,height=0;
    std::vector<ShpFrame> frames;
};
// Bounded TS/RA2 raw format 1 and RLE format 3 frames.
// Reference interpretation: OpenRA ShpTSLoader/RLEZerosCompression, GPLv3+.
ShpImage readShp(const Data&);
}
