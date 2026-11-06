// SPDX-License-Identifier: GPL-3.0-or-later
// Copyright 2026 ra2-decomp contributors
// Copyright 2025 Electronic Arts Inc.; 2026 OpenTS contributors
// Derived from Electronic Arts source code; EA's GPL Section 7 terms apply (COPYING.md).

// Modified for this RA2 target; pinned upstream COPYING:
// https://github.com/gibbo101/ra2-decomp/blob/4453ab030c86d8586992bfa7425ef7f39e3fb8d4/COPYING.md
/* BEGIN EA supplemental terms
ADDITIONAL TERMS per GNU GPL Section 7

No trademark or publicity rights are granted. This license does NOT give you
any right, title or interest in "Command & Conquer" or any other Electronic Arts
trademark. You may not distribute any modification of this program using any
Electronic Arts trademark or claim any affiliation or association with
Electronic Arts Inc. or its affiliates or their employees.

Any propagation or conveyance of this program must include this copyright
notice and these terms.

If you convey this program (or any modifications of it) and assume
contractual liability for the program to recipients of it, you agree to
indemnify Electronic Arts for any liability that those contractual
assumptions impose on Electronic Arts.

You may not misrepresent the origins of this program; modified versions of
the program must be marked as such and not identified as the original program.

This disclaimer supplements the one included in the General Public License.
TO THE FULLEST EXTENT PERMISSIBLE UNDER APPLICABLE LAW, THIS PROGRAM IS
PROVIDED TO YOU "AS IS," WITH ALL FAULTS, WITHOUT WARRANTY OF ANY KIND, AND
YOUR USE IS AT YOUR SOLE RISK. THE ENTIRE RISK OF SATISFACTORY QUALITY AND
PERFORMANCE RESIDES WITH YOU. ELECTRONIC ARTS DISCLAIMS ANY AND ALL EXPRESS,
IMPLIED OR STATUTORY WARRANTIES, INCLUDING IMPLIED WARRANTIES OF
MERCHANTABILITY, SATISFACTORY QUALITY, FITNESS FOR A PARTICULAR PURPOSE,
NONINFRINGEMENT OF THIRD PARTY RIGHTS, AND WARRANTIES (IF ANY) ARISING FROM A
COURSE OF DEALING, USAGE, OR TRADE PRACTICE. ELECTRONIC ARTS DOES NOT WARRANT
AGAINST INTERFERENCE WITH YOUR ENJOYMENT OF THE PROGRAM; THAT THE PROGRAM WILL
MEET YOUR REQUIREMENTS; THAT OPERATION OF THE PROGRAM WILL BE UNINTERRUPTED OR
ERROR-FREE, OR THAT THE PROGRAM WILL BE COMPATIBLE WITH THIRD PARTY SOFTWARE
OR THAT ANY ERRORS IN THE PROGRAM WILL BE CORRECTED. NO ORAL OR WRITTEN ADVICE
PROVIDED BY ELECTRONIC ARTS OR ANY AUTHORIZED REPRESENTATIVE SHALL CREATE A
WARRANTY. SOME JURISDICTIONS DO NOT ALLOW THE EXCLUSION OF OR LIMITATIONS ON
IMPLIED WARRANTIES OR THE LIMITATIONS ON THE APPLICABLE STATUTORY RIGHTS OF A
CONSUMER, SO SOME OR ALL OF THE ABOVE EXCLUSIONS AND LIMITATIONS MAY NOT APPLY
TO YOU.

END EA supplemental terms */

// Adopted from ra2-decomp YR005C80A0, pinned4453ab030c86d8586992bfa7425ef7f39e3fb8d4.
// Adaptation: existing RA2 fastcall API, 32-bit digit spelling and Upton globals.
#include "shared/mpmath.hpp"
#define SEMI_UPPER_MOST_BIT 0x8000

int __fastcall XMP_Mod_Mult(digit * prod, const digit * multiplicand, const digit * multiplier, int precision)
{
	XMP_Double_Mul(upton_mpdbuf, multiplicand, multiplier, precision);

	int double_precision = precision * 2 + 1;

	upton_mpdbuf[double_precision - 1] = 0;

	int dmi = XMP_Significance(upton_mpdbuf, double_precision) * 2;

	if (dmi >= upton_munits) {
		XMP_Inc(upton_mpdbuf, double_precision);
		XMP_Neg(upton_mpdbuf, double_precision);

		int nqd = dmi + 1 - upton_munits;

		unsigned short * dmph = ((unsigned short *)upton_mpdbuf) + dmi + 1;
		unsigned short * dmpl = dmph - upton_munits;

		for (; nqd; nqd--) {
			--dmph;
			--dmpl;

			unsigned short q = mp_quo_digit(dmph);
			if (q > 0) {
				XMP_Single_Mul(dmpl, (unsigned short *)upton_modulus, q, precision*2);

				if (!(*dmph & SEMI_UPPER_MOST_BIT)) {
					unsigned short * dmp = dmpl;
					if (XMP_Sub((digit *)dmp, (digit *)dmp, upton_modulus, false, precision)) {
						(*dmph)--;
					}
				}
			}
		}

		XMP_Neg(upton_mpdbuf, precision);
		XMP_Dec(upton_mpdbuf, precision);
	}

	XMP_Move(prod, upton_mpdbuf, precision);
	return(0);
}
