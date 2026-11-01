// void SubTitleParser::Parse_Token(unsigned short *token, unsigned short *param, SubTitle *subtitle)
// (0x0069BC60): calls the keyword's handler.
void SubTitleParser::Parse_Token(unsigned short *token, unsigned short *param, SubTitle *subtitle)
{
    if (token != 0) {
        for (int index = 0; unknown_subtitle_hooks_7f62f0[index].Token != 0; index++) {
            SubTitleHook *hook = &unknown_subtitle_hooks_7f62f0[index];
            if (_wcsicmp(hook->Token, token) == 0) {
                hook->Handler(param, subtitle);
                return;
            }
        }
    }
}
