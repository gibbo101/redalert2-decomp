// bool BitFontClass::Intersect_Rect(tagRECT *result, tagRECT const *a, tagRECT const *b) (0x00432000)
// The overlap of two rectangles (edges inclusive); 0,0,-1,-1 and false
// when they do not meet.
#include "shared/text_print.hpp"

bool BitFontClass::Intersect_Rect(tagRECT *result, tagRECT const *a, tagRECT const *b)
{
    if (a->top <= b->bottom && b->top <= a->bottom && a->left <= b->right && b->left <= a->right) {
        *result = *a;
        if (result->top < b->top) {
            result->top = b->top;
        }
        if (result->left < b->left) {
            result->left = b->left;
        }
        if (result->bottom > b->bottom) {
            result->bottom = b->bottom;
        }
        if (result->right > b->right) {
            result->right = b->right;
        }
        return true;
    }
    result->left = 0;
    result->top = 0;
    result->right = -1;
    result->bottom = -1;
    return false;
}
