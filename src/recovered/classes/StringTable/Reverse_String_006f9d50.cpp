// void __fastcall Reverse_String_006f9d50(char *start, char *end) (0x006F9D50): reverses the characters from
// start to end in place; when the first character is upper case and the last lower case, their cases swap.
void __fastcall Reverse_String_006f9d50(char *start, char *end)
{
    int first = 1;
    while (true) {
        if (start >= end) {
            return;
        }
        char left = *start;
        char right = *end;
        if (first) {
            if (left >= 'A' && left <= 'Z' && right >= 'a' && right <= 'z') {
                left += 'a' - 'A';
                right -= 'a' - 'A';
            }
            first = 0;
        }
        *end-- = left;
        *start = right;
        start++;
    }
}
