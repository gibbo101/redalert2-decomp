// A heap string slot assigned from a C string (0x0076DBC0) and the comma list parser that
// fills it (0x0073D070).
#ifndef RA2_SHARED_WOL_LIST_TEXT_HPP
#define RA2_SHARED_WOL_LIST_TEXT_HPP

class UnknownStringSlot {
public:
    void Assign(char const *text);      // 0x0076DBC0 (frees the old copy, duplicates text)
    char *unknown_0;                    // +0x00 the copy
};

void __fastcall Unknown_Split_Five_Numbers_And_Text_0073D070(char *text, int *first, int *second,
                                                             int *third, int *fourth, int *fifth,
                                                             UnknownStringSlot *rest);

#endif
