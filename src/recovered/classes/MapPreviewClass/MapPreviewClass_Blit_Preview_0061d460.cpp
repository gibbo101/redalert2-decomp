// The smaller of two values (the comparison reads the second value first).
template <class T> T min(T a, T b)
{
    return (b < a) ? b : a;
}

void UnknownPreview_0061D430::Draw_0061D460(HWND window)
{
    ValidateRect(window, 0);

    if (unknown_00 != 0) {
        RECT winrect;
        Window_Rect_In_Main_Client(GetDlgItem(window, 0x468), &winrect);
        Rect framerect(winrect.left, winrect.top, winrect.right - winrect.left, winrect.bottom - winrect.top);
        Rect destrect;
        Rect srcrect = unknown_00->Get_Rect();
        int scale = min(1000 * framerect.Width / srcrect.Width, 1000 * framerect.Height / srcrect.Height);

        destrect.X = framerect.X + framerect.Width / 2 - (scale * srcrect.Width) / 2000;
        destrect.Y = framerect.Y + framerect.Height / 2 - (scale * srcrect.Height) / 2000;
        destrect.Width = (scale * srcrect.Width) / 1000;
        destrect.Height = (scale * srcrect.Height) / 1000;
        unknown_surface_839958->Fill_Rect(framerect, 0);
        unknown_surface_839958->Copy_From(destrect, *unknown_00, unknown_00->Get_Rect(), false, false);
    }
}
// @ref ?Window_Rect_In_Main_Client@@YIHPAUHWND__@@PAURECT@@@Z=00735690
// @ref ?unknown_surface_839958@@3PAVSurface@@A=00839958
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__ValidateRect@8=0079a3f8
