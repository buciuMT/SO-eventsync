/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2021, Julius Heijmen <julius.heijmen@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <iostream>
#include <syscall.h>
// #include <LibCore/System.h>
// #include <LibGUI/AboutDialog.h>
// #include <LibGUI/Application.h>
// #include <LibGUI/Icon.h>
// #include <LibMain/Main.h>

struct args{
    struct str{const char*str;size_t size;} name;
    int bol;
};

int main(){
    
    std::cout<<"hello world\n";
    args arg={{"test",4},1};  
    int res=syscall(SC_eventopen,&arg);
    std::cout<<res<<'\n';
    std::cout<<"waiting\n";
    struct args2{
        int res;
    } arg2={res};
    int res2=syscall(SC_eventwait,&arg2);
    std::cout<<res2<<'\n';
    return 0;
}
