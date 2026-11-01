// 0x0060E9F0
static int __cdecl Phone_Compare(void const *p1, void const *p2)
{
    PhoneEntryClass *pe1, *pe2;
    int result;

    pe1 = *((PhoneEntryClass **)p1);
    pe2 = *((PhoneEntryClass **)p2);
    result = wcscmp(pe1->Name, pe2->Name);
    if (!result) {
        result = strcmp(pe1->Number, pe2->Number);
    }
    return result;
}
// @ref _wcscmp=007837d3
