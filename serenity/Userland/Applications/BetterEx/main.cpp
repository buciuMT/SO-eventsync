/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2021, Julius Heijmen <julius.heijmen@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */


#include <LibCore/System.h>
#include <LibGUI/AboutDialog.h>
#include <LibGUI/Application.h>
#include <LibGUI/Icon.h>
#include <LibMain/Main.h>
#include <LibGUI/Window.h>
#include "widget.h"

ErrorOr<int> serenity_main(Main::Arguments arguments)
{
    auto app = TRY(GUI::Application::create(arguments));
    auto window=GUI::Window::construct();
    window->set_title("BetterExample!");
    window->set_rect(100, 100, 300, 200);
    auto widget=TRY(W::BWidget::create());
    window->set_main_widget(widget);
    window->show();
    return app->exec();
}
