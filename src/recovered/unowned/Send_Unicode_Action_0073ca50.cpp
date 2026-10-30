#include "shared/wol_sink.hpp"
#include "shared/crt_memory.hpp"
HWND Unknown_00735B10();
extern int unknown_selected_actions_b294f4[128];
// @ref ?Unknown_00735B10@@YAPAXXZ=00735b10
// @ref ?unknown_selected_actions_b294f4@@3PAHA=00b294f4
int __fastcall Unknown_0073ca50(WideString const &message)
{
    HWND users=GetDlgItem(Unknown_00735B10(),0x53e);
    int count=SendMessageA(users,0x191,32,(LPARAM)unknown_selected_actions_b294f4);
    if(count==0) {
        unknown_chat_a72cfc->unknown_slot58(message.unknown_text_770430());
        return 0;
    } else {
        WOL::User *last=0,*head=0,*item=0;
        WOL::User source;
        memset(&source,0,sizeof(source));
        for(int i=0;i<count;++i) {
            unknown_users_b2a728.Get_Copy(source,unknown_selected_actions_b294f4[i]);
            item=new WOL::User;
            *item=source;
            item->next=0;
            if(i==0) head=item;
            if(last) last->next=item;
            last=item;
        }
        if(head) unknown_chat_a72cfc->unknown_slot59(head,message.unknown_text_770430());
        while(head) { item=head; head=head->next; delete item; }
        return 1;
    }
}
