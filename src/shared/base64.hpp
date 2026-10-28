// Westwood's Base64 text coding (wwlib), 0x0042D520 and 0x0042D640: the data is coded in groups of three bytes
// into four characters of the 64-character alphabet; the text is padded with the pad character.
#ifndef RA2_SHARED_BASE64_HPP
#define RA2_SHARED_BASE64_HPP

// Encodes slen bytes into at most dlen characters (a multiple of four is used); a terminating zero is written when
// room remains. Returns the number of characters produced.
int __fastcall Base64_Encode(void const *source, int slen, void *dest, int dlen);   // 0x0042D520
// Decodes the text; characters outside the alphabet are skipped and the pad character ends the input.
// Returns the number of bytes produced.
int __fastcall Base64_Decode(void const *source, int slen, void *dest, int dlen);   // 0x0042D640

extern char const *unknown_base64_pad_79c61c;       // 0x0079C61C points to "="
extern char const *unknown_base64_chars_79c620;     // 0x0079C620 points to the alphabet
extern unsigned char unknown_base64_table_79c624[256];   // 0x0079C624 the value of each character (0xFE skipped, 0xFF the pad)

#endif
