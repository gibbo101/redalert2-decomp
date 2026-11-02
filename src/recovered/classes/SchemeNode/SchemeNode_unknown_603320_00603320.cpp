// SchemeNode::unknown_603320 (0x603320)
void SchemeNode::unknown_603320()
{
    if (Schemes != 0) {
        int count = Schemes->Count();
        for (int index = 0; index < count; index++) {
            ColorScheme *scheme = (*Schemes)[index];
            if (scheme != 0) {
                delete scheme;
            }
        }
        delete Schemes;
        Schemes = 0;
    }
}
