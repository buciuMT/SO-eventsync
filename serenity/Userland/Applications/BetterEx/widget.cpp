#include "widget.h"
#include "syscall.h"
#include <AK/String.h>
#include <LibConfig/Client.h>
#include <AK/Random.h>
#include <AK/String.h>
#include <LibConfig/Client.h>
#include <LibCore/StandardPaths.h>
#include <LibCore/File.h>
#include <LibGUI/Application.h>
#include <LibGUI/Button.h>
#include <LibGUI/TextBox.h>
#include <LibGUI/CheckBox.h>
#include <LibGUI/Frame.h>
#include <LibGUI/Label.h>
#include <LibGUI/Painter.h>
#include <LibGUI/Process.h>
#include <LibGfx/Palette.h>
#include <AK/PrintfImplementation.h>
#include <stdio.h>

namespace W{

struct args{
    struct str{const char*str;size_t size;} name;
    int bol;
};
struct args2{
    int res;
};

BWidget::BWidget()=default;

ErrorOr<NonnullRefPtr<BWidget>> BWidget::create()
{
    auto res=TRY(try_create());
    TRY(res->create_widgets());
    return res;
}

static int get_nr(const AK::ByteString &str)
{
    int rez=0;
    for(char i:str)
        rez=rez*10+(i-'0');
    printf("%d\n",rez);
    return rez;
}

ErrorOr<void> BWidget::create_widgets()
{
    m_name=find_descendant_of_type_named<GUI::TextBox>("name");
    m_id=find_descendant_of_type_named<GUI::Label>("id");
    m_open=find_descendant_of_type_named<GUI::Button>("open");
    m_close=find_descendant_of_type_named<GUI::Button>("close");
    m_wait=find_descendant_of_type_named<GUI::Button>("wait");
    m_signal=find_descendant_of_type_named<GUI::Button>("signal");
    m_open->on_click=[&](auto)
    {
        char nstr[100];
        size_t len=0;
        for(char i:m_name->text()){
            nstr[len++]=i;
        }
        nstr[len]=0;
        args arg={{nstr,len},1};
        printf("%s\n",arg.name.str);
        int res=syscall(SC_eventopen,&arg);
        m_id->set_text(MUST(AK::String::formatted("last id:{}",res)));
        m_name->set_text(MUST(AK::String::formatted("{}",res)));
    };
    m_close->on_click=[&](auto)
    {
        args2 arg={get_nr(m_name->text().trim_whitespace())};
        int res=syscall(SC_eventclose,&arg);
        m_id->set_text(MUST(AK::String::formatted("return value: {}",res)));
    };
    m_wait->on_click=[&](auto)
    {
        args2 arg={get_nr(m_name->text().trim_whitespace())};
        int res=syscall(SC_eventwait,&arg);
        m_id->set_text(MUST(AK::String::formatted("return value: {}",res)));
    };
    m_signal->on_click=[&](auto)
    {
        args2 arg={get_nr(m_name->text().trim_whitespace())};
        int res=syscall(SC_eventsignal,&arg);
        m_id->set_text(MUST(AK::String::formatted("return value: {}",res)));
    };
    return {};
}

}