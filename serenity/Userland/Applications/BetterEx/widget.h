#pragma once

#include <AK/StringView.h>
#include <LibGUI/Widget.h>
#include <AK/Random.h>
#include <AK/String.h>
#include <LibConfig/Client.h>
#include <LibCore/StandardPaths.h>
#include <LibGUI/Application.h>
#include <LibGUI/Button.h>
#include <LibGUI/CheckBox.h>
#include <LibGUI/Frame.h>
#include <LibGUI/Label.h>
#include <LibGUI/Painter.h>
#include <LibGUI/Process.h>
#include <LibGfx/Palette.h>

namespace W{

class BWidget final:public GUI::Widget{
    C_OBJECT(BWidget);
public:
    static ErrorOr<NonnullRefPtr<BWidget>> create();
    virtual ~BWidget() override = default;

private:
    BWidget();
    ErrorOr<void> create_widgets();
    static ErrorOr<NonnullRefPtr<BWidget>> try_create();
    RefPtr<GUI::TextBox> m_name;
    RefPtr<GUI::Label> m_id;
    RefPtr<GUI::Button> m_open;
    RefPtr<GUI::Button> m_close;
    RefPtr<GUI::Button> m_wait;
    RefPtr<GUI::Button> m_signal;
};

}