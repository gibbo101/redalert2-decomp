// void __fastcall Unknown_006F92A0(void *file, char *source, char *text, char *label, int limit) (0x006F92A0)
// Reads one entry of a text resource: first a quoted string (up to limit
// characters; a backslash escapes the next one, a newline or white space
// becomes a blank, the closing quote ends it) into text, then the label
// that follows (letters, digits and underscores after any leading white
// space or '='; a label ending in a digit gets an "e" appended) into
// label. Characters come from source first, then from file (0x00784A3C).
// @ref ?Unknown_getc_00784a3c@@YAHPAX@Z=00784a3c
// @ref ?Unknown_isspace_00784aa8@@YAHF@Z=00784aa8

int __cdecl Unknown_getc_00784a3c(void *file);
int __cdecl Unknown_isspace_00784aa8(short character);

// The next character: from the string while it lasts, then from the file.
static inline void Next_Character(void *file, char *&source, char &character)
{
    if (source) {
        character = *source++;
        if (character == 0) {
            source = 0;
            character = (char)Unknown_getc_00784a3c(file);
        }
    } else {
        character = (char)Unknown_getc_00784a3c(file);
    }
}

void __fastcall Unknown_006F92A0(void *file, char *source, char *text, char *label, int limit)
{
    int escaped = 0;
    int state = 0;
    int length = 0;
    char character;
    for (; limit != 0; limit--) {
        Next_Character(file, source, character);
        if (character == -1) {
            return;
        }
        if (character == '\n') {
            escaped = 0;
            character = ' ';
        } else if (character == '\\') {
            escaped = escaped == 0;
        } else {
            if (character == '"' && !escaped) {
                break;
            }
            escaped = 0;
        }
        if (Unknown_isspace_00784aa8(character)) {
            character = ' ';
        }
        *text++ = character;
    }
    *text = 0;
    for (;;) {
        Next_Character(file, source, character);
        if (character == '\n' || character == -1) {
            *label = 0;
            if (length != 0 && label[-1] >= '0' && label[-1] <= '9') {
                *label = 'e';
                label[1] = 0;
            }
            return;
        }
        switch (state) {
        case 0:
            if (Unknown_isspace_00784aa8(character) || character == '=') {
                continue;
            }
            state = 1;
        case 1:
            if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z') || (character >= '0' && character <= '9') || character == '_') {
                *label++ = character;
                length++;
            } else {
                state = 2;
            }
            break;
        }
    }
}
