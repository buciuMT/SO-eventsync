/*
 * Copyright (c) 2021, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

// Implement the event syscalls
#include <AK/Singleton.h>
#include <AK/String.h>
#include <Kernel/Debug.h>
#include <Kernel/Memory/InodeVMObject.h>
#include <Kernel/Memory/MemoryManager.h>
#include <Kernel/Tasks/Process.h>


namespace Kernel {

static size_t l_event_generator=0;

static Singleton<SpinlockProtected<HashMap<NonnullOwnPtr<Kernel::KString>, size_t>, LockRank::None>> s_global_event_id;
static Singleton<SpinlockProtected<HashMap<size_t, Vector<int>>, LockRank::None>> s_global_pids;

#define EV_STR_LENTH 128
#define EV_STR_CNT 128 

// static bool ev_free_space[EV_STR_CNT];
// static char ev_strings [EV_STR_CNT][EV_STR_LENTH]={0};


// AK::StringView ev_str_alloc(const AK::StringView&);
// AK::StringView ev_str_alloc(const AK::StringView& str){
//     for(int i=0;i<EV_STR_CNT;i++){
//         if(ev_free_space[i])
//             continue;
//         memcpy(&ev_strings[i],str.characters_without_null_termination(),str.length());
//         return AK::StringView((const char*)&ev_strings[i],str.length());
//     }
//     return AK::StringView((const char*)nullptr,0);
// };
// void ev_free_str(const AK::StringView&);
// void ev_free_str(const AK::StringView& str)
// {
//     size_t cnt=(((size_t)str.characters_without_null_termination())-((size_t)ev_strings[0]))/EV_STR_LENTH;
//     ev_free_space[cnt]=false;
// }

void use_int_simple(int);
void use_int_simple(int){};
void use_path(AK::StringView&);
void use_path(AK::StringView&){}

static size_t get_next_av_index(const HashMap<size_t,size_t> &map)
{
    size_t index=0;
    while(map.find(index)!=map.end())
        index++;
    return index;
}

ErrorOr<FlatPtr> Process::sys$eventopen(Userspace<Syscall::SC_eventopen_params const*> user_params)
{
    VERIFY_NO_PROCESS_BIG_LOCK(this);
    // TRY(require_promise(Pledge::stdio));
    auto params = TRY(copy_typed_from_user(user_params));
    dbgln("bool :{}",params.bool_create);
    auto input=TRY(try_copy_kstring_from_user(params.false_path));
    dbgln("path :{}",input);
    return s_global_event_id->with([&](auto &s)->ErrorOr<FlatPtr>{
        auto it=s.find(input);
        if(it==s.end())
        {
            if(!params.bool_create)
                return -1;
            size_t current=l_event_generator++;
            auto result=TRY(s.try_set(move(input),move(current)));
            VERIFY(result == AK::HashSetResult::InsertedNewEntry);
            return local2globalevent_translator.with([&](auto &map)->ErrorOr<FlatPtr>{
                size_t next=get_next_av_index(map);
                auto result=TRY(map.try_set(next,current));
                VERIFY(result == AK::HashSetResult::InsertedNewEntry);
                return next;
            });
        };
        return local2globalevent_translator.with([&](auto &map)->ErrorOr<FlatPtr>{
            auto its=map.find(it->value);
            if(its==map.end()){
                size_t next=get_next_av_index(map);
                auto result=TRY(map.try_set(next,it->value));
                VERIFY(result == AK::HashSetResult::InsertedNewEntry);
                return next;
            }
            return its->value;
        });
    });
    return 0;
}

ErrorOr<FlatPtr> Process::sys$eventclose(Userspace<Syscall::SC_eventclose_params const*> user_params)
{
    VERIFY_NO_PROCESS_BIG_LOCK(this);
    // TRY(require_promise(Pledge::stdio));
    auto params = TRY(copy_typed_from_user(user_params));
    use_int_simple(params.descriptor);
    return NULL;
}
ErrorOr<FlatPtr> Process::sys$eventwait(Userspace<Syscall::SC_eventwait_params const*> user_params)
{
    VERIFY_PROCESS_BIG_LOCK_ACQUIRED(this);
    // TRY(require_promise(Pledge::stdio));
    auto params = TRY(copy_typed_from_user(user_params));
    use_int_simple(params.descriptor);
    return NULL;
}
ErrorOr<FlatPtr> Process::sys$eventsignal(Userspace<Syscall::SC_eventsignal_params const*> user_params)
{
    
    VERIFY_NO_PROCESS_BIG_LOCK(this);
    // TRY(require_promise(Pledge::stdio));
    auto params = TRY(copy_typed_from_user(user_params));
    use_int_simple(params.descriptor);
    return NULL;
}

}
