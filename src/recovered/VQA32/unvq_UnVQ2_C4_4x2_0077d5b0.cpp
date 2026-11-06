// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 ra2-decomp contributors
// Copyright 2025 Electronic Arts Inc.; 2026 OpenTS contributors
// Derived from Electronic Arts source code; EA's GPL Section 7 terms apply (COPYING.md).
// From ra2-decomp (YR 0x007C43A0).
#include "shared/vqa_player.hpp"

typedef signed int int32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

void __cdecl UnVQ2_C4_4x2(unsigned char * codebook, unsigned char * pointers, unsigned char * buffer, unsigned long blocksperrow, unsigned long numrows, unsigned long bufwidth)
{
	bufwidth *= 2u;
	uint32_t block_row_stride = bufwidth * 2u;

	uint8_t * end = (uint8_t *)buffer + ((uint32_t)numrows * bufwidth * 2u);
	uint8_t * dst = (uint8_t *)buffer;

	uint8_t * row_base = (uint8_t *)buffer;
	uint8_t * row_end = row_base + ((uint32_t)blocksperrow * 8u);

	uint8_t * src = pointers;

	uint32_t height;
	uint32_t code;
	uint32_t idx;

	while (dst < end) {

		uint32_t command = (*(uint16_t *)src & 0xE000);
		uint16_t cb_index = (*(uint16_t *)src & 0x1FFF);
		src += 2;

		switch (command) {

		case 0x4000u: {
			uint32_t repeat = ((cb_index >> 7) & 0x3Eu) + 2u;
			const uint8_t * cb = codebook + (*(src - 2) << 4);
			uint8_t * rowp = dst;
			uint32_t step = 4u * (bufwidth >> 2);

			for (uint32_t r = 0; r < 2; ++r) {
				uint32_t lo = ((uint32_t)*(uint16_t *)(cb + 2) << 16) | *(uint16_t *)(cb + 0);
				cb += 4;
				*(uint32_t *)(rowp + 0) = lo;

				uint32_t hi = ((uint32_t)*(uint16_t *)(cb + 2) << 16) | *(uint16_t *)(cb + 0);
				cb += 4;
				*(uint32_t *)(rowp + 4) = hi;

				rowp += step;
			}

			uint8_t * cursor = src;
			dst += 8;

			for (int32_t i = 0; i < repeat; i++) {
				uint32_t idx = *cursor;
				cursor += 1;
				uint8_t * p = dst;
				const uint8_t * cb2 = codebook + (idx << 4);

				for (uint32_t r = 0; r < 2; ++r) {
					uint32_t lo = ((uint32_t)*(uint16_t *)(cb2 + 2) << 16) | *(uint16_t *)(cb2 + 0);
					cb2 += 4;
					*(uint32_t *)(p + 0) = lo;

					uint32_t hi = ((uint32_t)*(uint16_t *)(cb2 + 2) << 16) | *(uint16_t *)(cb2 + 0);
					cb2 += 4;
					*(uint32_t *)(p + 4) = hi;

					p += step;
				}

				dst += 8;
			}

			src = cursor;
		} break;

		case 0x2000u: {
			code = cb_index;
			code &= 0xFFFFu;
			height = ((code >> 7) & 0x3Eu) + 2u;
		label_check:
			if (height == 0u) {
				idx = cb_index;
				height = *src;
				src += 1;
				goto label_vertical_fill;
			} else {
				goto label_masked_index;
			}

		}

		case 0x0000u: {
			dst += 8u * (uint8_t)cb_index;
		} break;

		case 0x6000u: {
			const uint8_t * cb = codebook + ((cb_index & 0xFFFFu) << 4);

			for (uint32_t r = 0; r < 2; ++r) {
				uint32_t lo = ((uint32_t)*(uint16_t *)(cb + 2) << 16) | *(uint16_t *)(cb + 0);
				cb += 4;
				*(uint32_t *)(dst + 0) = lo;

				uint32_t hi = ((uint32_t)*(uint16_t *)(cb + 2) << 16) | *(uint16_t *)(cb + 0);
				cb += 4;
				*(uint32_t *)(dst + 4) = hi;

				dst += bufwidth;
			}

			dst += 8u - block_row_stride;
		} break;

		case 0xC000u: {
			height = *src;
			src += 1;

			const uint8_t * cb = codebook + (16u * (uint16_t)cb_index);

			for (uint32_t r = 0; r < 2; ++r) {
				uint8_t * p = dst;

				for (uint32_t c = 0; c < 4; ++c) {
					uint16_t v = *(uint16_t *)cb;

					if (v != 0x8000u) {
						uint8_t * q = p;
						for (uint32_t i = 0; i < height; i++) {
							*(uint16_t *)q = v;
							q += 8;
						}
					}

					p += 2;
					cb += 2;
				}

				dst += bufwidth;
			}

			dst += 8u * height - block_row_stride;
		} break;

		case 0xA000u:
			height = 0;
			goto label_check;

		label_masked_index:
			idx = code & 0xFFu;

		label_vertical_fill:
			{
				const uint8_t * cb = codebook + (16u * idx);

				for (uint32_t r = 0; r < 2; ++r) {

					uint32_t lo = ((uint32_t)*(uint16_t *)(cb + 2) << 16) | *(uint16_t *)(cb + 0);
					cb += 4;

					{
						uint8_t * p = dst;
						uint32_t i;
						for (i = 0; i < height; i++) {
							*(uint32_t *)p = lo;
							p += 8;
						}
					}

					uint32_t hi = ((uint32_t)*(uint16_t *)(cb + 2) << 16) | *(uint16_t *)(cb + 0);
					cb += 4;

					{
						uint8_t * p = dst + 4;
						uint32_t i;
						for (i = 0; i < height; i++) {
							*(uint32_t *)p = hi;
							p += 8;
						}
					}

					dst += bufwidth;
				}

				dst += 8u * height - block_row_stride;
			}
			break;

		case 0x8000u: {
			const uint8_t * cb = codebook + (16u * (uint16_t)cb_index);

			for (uint32_t r = 0; r < 2; ++r) {
				uint8_t * p = dst;

				for (uint32_t c = 0; c < 4; ++c) {
					if (*(uint16_t *)cb != 0x8000u) {
						*(uint16_t *)p = *(uint16_t *)cb;
					}
					p += 2;
					cb += 2;
				}

				dst += bufwidth;
			}

			dst += 8u - block_row_stride;
		} break;
		}

		if (dst == row_end) {
			row_base += block_row_stride;
			dst = row_base;
			row_end = row_base + ((uint32_t)blocksperrow * 8u);
		}
	}
}
