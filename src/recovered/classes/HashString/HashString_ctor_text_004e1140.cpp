HashString::HashString(char const *text)
{
    strcpy(Text, text);
    _strupr(Text);
}
