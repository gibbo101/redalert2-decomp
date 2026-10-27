// void __fastcall unknown_text_buffer_append(char character) -- 0x005CFD70
// Purpose: appends one character to a global zero-terminated text buffer
// (pointer 0x00A40A34, capacity 0x00A40A38, length 0x00A40A3C) while room
// remains for the terminator. No direct callers. Owner not identified.
// @ref ?unknown_text_buffer_a40a34@@3PADA=00a40a34
// @ref ?unknown_text_capacity_a40a38@@3HA=00a40a38
// @ref ?unknown_text_length_a40a3c@@3HA=00a40a3c

extern char *unknown_text_buffer_a40a34;
extern int unknown_text_capacity_a40a38;
extern int unknown_text_length_a40a3c;

void __fastcall unknown_text_buffer_append_005cfd70(char character)
{
    if (unknown_text_length_a40a3c < unknown_text_capacity_a40a38 - 1) {
        unknown_text_buffer_a40a34[unknown_text_length_a40a3c] = character;
        unknown_text_buffer_a40a34[unknown_text_length_a40a3c + 1] = '\0';
        unknown_text_length_a40a3c++;
    }
}
