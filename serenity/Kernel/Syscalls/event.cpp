/*
 * Copyright (c) 2021, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

// Implement the event syscalls

#include <Kernel/Tasks/Process.h>

namespace Kernel {

ErrorOr<FlatPtr> Process::sys$eventopen(Userspace<Syscall::SC_eventopen_params const*>){return NULL;};
ErrorOr<FlatPtr> Process::sys$eventclose(Userspace<Syscall::SC_eventclose_params const*>){return NULL;};
ErrorOr<FlatPtr> Process::sys$eventwait(Userspace<Syscall::SC_eventwait_params const*>){return NULL;};
ErrorOr<FlatPtr> Process::sys$eventsignal(Userspace<Syscall::SC_eventsignal_params const*>){return NULL;};

}
