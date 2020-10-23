/*
** EPITECH PROJECT, 2020
** PSU_strace_2019
** File description:
** straceFunction
*/

#ifndef STRACEFUNC_H_
#define STRACEFUNC_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/user.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "ftrace.h"

typedef struct sysFunc
    {
    char        *fct_name;
    char        *fct_params[7];
    char        *ret_type;
}t_sysfunc;

static const t_sysfunc g_syscalls[] = {
    {"read", {"int", "char *", "size_t", NULL}, "ssize_t"},
    {"write", {"int", "char *", "size_t", NULL}, "ssize_t"},
    {"open", {"char *", "int", NULL}, "int"},
    {"close", {"int", NULL}, "int"},
    {"stat", {"char *", "struct stat *", NULL}, "int"},
    {"fstat", {"int", "struct stat *", NULL}, "int"},
    {"lstat", {"char *", "struct stat *", NULL}, "int"},
    {"poll", {"struct pollfd *", "nfds_t", "int", NULL}, "int"},
    {"lseek", {"int", "off_t", "int", NULL}, "off_t"},
    {"mmap", {"void *", "size_t", "int", "int", "int", "off_t", NULL},
    "void *"},
    {"mprotect", {"void *", "size_t", "int", NULL}, "int"},
    {"munmap", {"void *", "size_t", NULL}, "int"},
    {"brk", {"int", NULL}, "void *"},
    {"sigaction",
    {"int", "struct sigaction *", "struct sigaction *", NULL}, "int"},
    {"sigprocmask", {"int", "sigset_t *", "sigset_t *", NULL}, "int"},
    {"sigreturn", {"unsigned long", NULL}, "int"},
    {"ioctl", {"int", "int", NULL}, "int"},
    {"pread64", {"int", "void *", "size_t", "off_t", NULL}, "ssize_t"},
    {"pwrite64", {"int", "void *", "size_t", "off_t", NULL}, "ssize_t"},
    {"readv", {"int", "struct  iovec *", "int", NULL}, "ssize_t"},
    {"writev", {"int", "struct  iovec *", "int", NULL}, "ssize_t"},
    {"access", {"char *", "int", NULL}, "int"},
    {"pipe", {"int[2]", NULL}, "int"},
    {"select",
    {"int", "fd_set *", "fd_set *", "fd_set *", "stuct timeval *", NULL},
    "int"},
    {"sched_yield", {"void", NULL}, "int"},
    {"mremap", {"void *", "size_t", "size_t", "int", NULL}, "void *"},
    {"msync", {"void *", "size_t", "int", NULL}, "int"},
    {"mincore", {"void *", "size_t", "unsigned char *", NULL}, "int"},
    {"madvise", {"void *", "size_t", "int", NULL}, "int"},
    {"shmget", {"key_t", "size_t", "int", NULL}, "int"},
    {"shmat", {"int", "void *", "int", NULL}, "void *"},
    {"shmctl", {"int", "int", "struct shmid_ds *", NULL}, "int"},
    {"dup", {"int", NULL}, "int"},
    {"dup2", {"int", "int", NULL}, "int"},
    {"pause", {"void", NULL}, "int"},
    {"nanosleep", {"struct timespec *", "struct timespec *", NULL}, "int"},
    {"getitimer", {"int", "struct itimervalq *", NULL}, "int"},
    {"alarm", {"unsigned int", NULL}, "unsigned int"},
    {"setitimer",
    {"int", "struct itimerval *", "struct itimerval *", NULL}, "int"},
    {"getpid", {"void""void", NULL}, "pid_t"},
    {"sendfile", {"int", "int", "off_t *", "size_t", NULL}, "ssize_t"},
    {"socket", {"int", "int", "int", NULL}, "int"},
    {"connect", {"int", "struct sockaddr *", "socklen_t", NULL}, "int"},
    {"accept", {"int", "struct sockaddr *", "socklen_t", NULL}, "int"},
    {"sendto",
    {"int", "void *", "size_t", "int", "struct sockaddr *", "socklen_t", NULL},
    "ssize_t"},
    {"recvfrom",
    {"int", "void *", "size_t", "int", "struct sockaddr *", "socklen_t *",
    NULL}, "ssize_t"},
    {"sendmsg", {"int", "struct msghdr *", "int", NULL}, "ssize_t"},
    {"recvmsg", {"int", "struct msghdr *", "int", NULL}, "ssize_t"},
    {"shutdown", {"int", "int", NULL}, "int"},
    {"bind", {"int", "struct sockaddr *", "socklen_t", NULL}, "int"},
    {"listen", {"int", "int", NULL}, "int"},
    {"getsockname", {"int", "struct sockaddr *", "socklen_t *", NULL}, "int"},
    {"getpeername", {"int", "struct sockaddr *", "socklen_t *", NULL}, "int"},
    {"socketpair", {"int", "int", "int", "int[2]", NULL}, "int"},
    {"setsockopt", {"int", "int", "int", "void *", "socklen_t", NULL},
    "int"},
    {"getsockopt", {"int", "int", "int", "void *", "socklen_t", NULL}, "int"},
    {"clone", {"int *", "struct stat *", NULL}, "int"},
    {"fork", {"void", NULL}, "pid_t"},
    {"vfork", {"void", NULL}, "pid_t"},
    {"execve", {"char *", "char **", "char **", NULL}, "int"},
    {"exit", {"int", NULL}, "void"},
    {"wait4", {"pid_t", "int *", "int", "struct rusage *", NULL}, "pid_t"},
    {"kill", {"pid_t", "int", NULL}, "int"},
    {"uname", {"struct utsname *", NULL}, "int"},
    {"semget", {"key_t", "int", "int", NULL}, "int"},
    {"semop", {"int", "struct sembuf *", "unsigned int", NULL}, "int"},
    {"semctl", {"int", "int", "int", NULL}, "int"},
    {"shmdt", {"void *", NULL}, "int"},
    {"msgget", {"key_t", "int", NULL}, "int"},
    {"msgsnd", {"int", "void *", "size_t", "int", NULL}, "int"},
    {"msgrcv", {"int", "void *", "size_t", "long", "int", NULL}, "ssize_t"},
    {"msgctl", {"int", "int", "struct msqid_ds *", NULL}, "int"},
    {"fcntl", {"int", "int", NULL}, "int"},
    {"flock", {"int", "int", NULL}, "int"},
    {"fsync", {"int", NULL}, "int"},
    {"fdatasync", {"int", NULL}, "int"},
    {"truncate", {"char *", "off_t", NULL}, "int"},
    {"ftruncate", {"int", "off_t", NULL}, "int"},
    {"getdents",
    {"unsigned int", "struct linux_dirent *", "unsigned int", NULL}, "int"},
    {"getcwd", {"char *", "unsigned long", NULL}, "long"},
    {"chdir", {"char *", NULL}, "int"},
    {"fchdir", {"int", NULL}, "int"},
    {"rename", {"char *", "char *", NULL}, "int"},
    {"mkdir", {"char *", "mode_t", NULL}, "int"},
    {"rmdir", {"char *", NULL}, "int"},
    {"creat", {"char *", "mode_t", NULL}, "int"},
    {"link", {"char *", "char *", NULL}, "int"},
    {"unlink", {"char *", NULL}, "int"},
    {"symlink", {"char *", "char *", NULL}, "int"},
    {"readlink", {"char *", "char *", "size_t", NULL}, "ssize_t"},
    {"chmod", {"char *", "mode_t", NULL}, "int"},
    {"fchmod", {"int", "mode_t", NULL}, "int"},
    {"chown", {"char *", "uid_t", "gid_t", NULL}, "int"},
    {"fchown", {"int", "uid_t", "gid_t", NULL}, "int"},
    {"lchown", {"char *", "uid_t", "gid_t", NULL}, "int"},
    {"umask", {"mode_t", NULL}, "mode_t"},
    {"gettimeofday", {"struct timeval *", "struct timezone *", NULL}, "int"},
    {"getrlimit", {"int", "struct rlimit *", NULL}, "int"},
    {"getrusage", {"int", "struct rusage *", NULL}, "int"},
    {"sysinfo", {"struct sysinfo *", NULL}, "int"},
    {"times", {"struct tms *", NULL}, "clock_t"},
    {"ptrace", {"int", "pid_t", "void *", "void *", NULL}, "long"},
    {"getuid", {"void", NULL}, "uid_t"},
    {"syslog", {"int", "char *", "int", NULL}, "int"},
    {"getgid", {"void", NULL}, "gid_t"},
    {"setuid", {"uid_t", NULL}, "int"},
    {"setgid", {"gid_t", NULL}, "int"},
    {"geteuid", {"void", NULL}, "uid_t"},
    {"getegid", {"void", NULL}, "gid_t"},
    {"setpgid", {"pid_t", "pid_t", NULL}, "int"},
    {"getppid", {"void", NULL}, "pid_t"},
    {"getpgrp", {"void", NULL}, "pid_t"},
    {"setsid", {"void", NULL}, "pid_t"},
    {"setreuid", {"uid_t", "uid_t", NULL}, "int"},
    {"setregid", {"gid_t", "gid_t", NULL}, "int"},
    {"getgroups", {"int", "gid_t[]", NULL}, "int"},
    {"setgroups", {"size_t", "gid_t *", NULL}, "int"},
    {"setresuid", {"uid_t", "uid_t", "uid_t", NULL}, "int"},
    {"getresuid", {"uid_t *", "uid_t *", "uid_t *", NULL}, "clock_t"},
    {"setresgid", {"gid_t", "gid_t", "gid_t", NULL}, "int"},
    {"getresgid", {"gid_t *", "gid_t *", "gid_t *", NULL}, "int"},
    {"getpgid", {"pid_t", NULL}, "pid_t"},
    {"setfsuid", {"uid_t", NULL}, "int"},
    {"setfsgid", {"uid_t", NULL}, "int"},
    {"getsid", {"pid_t", NULL}, "pid_t"},
    {"capget", {"cap_user_header_t", "cap_huser_data_t", NULL}, "int"},
    {"capset", {"cap_user_header_t", "cap_huser_data_t", NULL}, "int"},
    {"sigpending", {"sigset_t *", NULL}, "int"},
    {"sigtimedwait",
    {"sigset_t *", "siginfo_t *", "struct timespec *", NULL}, "int"},
    {"sys_rt_sigqueueinfo", {"int", "int", "siginfo_t *", NULL}, "long"},
    {"sigsuspend", {"sigset_t *", NULL}, "int"},
    {"sigaltstack", {"stack_t *", "stack_t *", NULL}, "int"},
    {"utime", {"char *", "struct utimbuf *", NULL}, "int"},
    {"mknod", {"char *", "mode_t", "dev_t", NULL}, "int"},
    {"uselib", {"char *", NULL}, "int"},
    {"personality", {"unsigned long", NULL}, "int"},
    {"ustat", {"dev_t", "struct ustat *", NULL}, "int"},
    {"statfs", {"char *", "struct statfs *", NULL}, "int"},
    {"fstatfs", {"int", "struct statfs *", NULL}, "int"},
    {"sysfs", {"struct tms *", NULL}, "clock_t"},
    {"getpriority", {"int", "int", NULL}, "int"},
    {"setpriority", {"int", "int", "int", NULL}, "int"},
    {"sched_setparam", {"pid_t", "struct sched_param *", NULL}, "int"},
    {"sched_getparam", {"pid_t", "struct sched_param *", NULL}, "int"},
    {"sched_setscheduler",
    {"pid_t", "int", "struct sched_param *", NULL}, "int"},
    {"sched_getscheduler", {"pid_t", NULL}, "int"},
    {"sched_get_priority_max", {"int", NULL}, "int"},
    {"sched_get_priority_min", {"int", NULL}, "int"},
    {"sched_rr_get_interval", {"pid_t", "struct timespec *", NULL}, "int"},
    {"mlock", {"void *", "size_t", NULL}, "int"},
    {"munlock", {"void *", "size_t", NULL}, "int"},
    {"mlockall", {"int", NULL}, "int"},
    {"munlockall", {"void", NULL}, "int"},
    {"vhangup", {"void", NULL}, "int"},
    {"modify_ldt", {"int", "void *", "unsigned long", NULL}, "int"},
    {"pivot_root", {"char *", "char *", NULL}, "int"},
    {"_sysctl", {"struct __sysctl_args *", NULL}, "int"},
    {"prctl",
    {"int", "unsigned long", "unsigned long", "unsigned long", "unsigned long",
    NULL}, "int"},
    {"arch_prctl", {"int", "unsigned long *", NULL}, "int"},
    {"adjtimex", {"struct timex *", NULL}, "int"},
    {"setrlimit", {"int", "struct rlimit *", NULL}, "int"},
    {"chroot", {"char *", NULL}, "int"},
    {"sync", {"void", NULL}, "void"},
    {"acct", {"char *", NULL}, "int"},
    {"settimeofday", {"struct timeval *", "struct timezone *", NULL}, "int"},
    {"mount",
    {"char *", "char *", "char *", "unsigned long", "void *", NULL}, "int"},
    {"umount2", {"char *", "int", NULL}, "int"},
    {"swapon", {"char *", "int", NULL}, "int"},
    {"swapoff", {"char *", NULL}, "int"},
    {"reboot", {"int", "int", "int", "void *", NULL}, "int"},
    {"sethostname", {"char *", "size_t", NULL}, "int"},
    {"setdomainname", {"char *", "size_t", NULL}, "int"},
    {"iopl", {"int", NULL}, "int"},
    {"ioperm", {"unsigned long", "unsigned long", "int", NULL}, "int"},
    {"create_module", {"char *", "size_t", NULL}, "caddr_t"},
    {"init_module", {"void *", "unsigned long", "char *", NULL}, "int"},
    {"delete_module", {"char *", "int", NULL}, "int"},
    {"get_kernel_syms", {"struct kernel_sym *", NULL}, "int"},
    {"query_module",
    {"char *", "int", "void *", "size_t", "size_t", NULL}, "int"},
    {"quotactl", {"int", "char *", "int", "caddr_t", NULL}, "int"},
    {"nfsservctl",
    {"int", "struct nfsctl_arg *", "union nfsctl_res *", NULL}, "int"},
    {"getpmsg", {"struct tms *", NULL}, "clock_t"},
    {"putpmsg", {"struct tms *", NULL}, "clock_t"},
    {"afs_syscall", {"struct tms *", NULL}, "clock_t"},
    {"tuxcall", {"struct tms *", NULL}, "clock_t"},
    {"security", {"struct tms *", NULL}, "clock_t"},
    {"gettid", {"void", NULL}, "pid_t"},
    {"readahead", {"int", "off64_t", "size_t", NULL}, "ssize_t"},
    {"setxattr", {"char *", "char *", "void *", "size_t", "int", NULL}, "int"},
    {"lsetxattr", {"char *", "char *", "void *", "size_t", "int", NULL}, "int"},
    {"fsetxattr", {"int", "char *", "void *", "size_t", "int", NULL}, "int"},
    {"getxattr", {"char *", "char *", "void *", "size_t", NULL}, "ssize_t"},
    {"lgetxattr", {"char *", "char *", "void *", "size_t", NULL}, "ssize_t"},
    {"fgetxattr", {"int", "char *", "void *", "size_t", NULL}, "ssize_t"},
    {"listxattr", {"char *", "char *", "size_t", NULL}, "ssize_t"},
    {"llistxattr", {"char *", "char *", "size_t", NULL}, "ssize_t"},
    {"flistxattr", {"int", "char *", "size_t", NULL}, "ssize_t"},
    {"removexattr", {"char *", "char *", NULL}, "int"},
    {"lremovexattr", {"char *", "char *", NULL}, "int"},
    {"fremovexattr", {"int", "char *", NULL}, "int"},
    {"tkill", {"int", "int", NULL}, "int"},
    {"time", {"time_t", NULL}, "time_t"},
    {"futex",
    {"int *", "int", "int", "struct timespec *", "int *", "int", NULL}, "int"},
    {"sched_setaffinity", {"pid_t", "size_t", "cpu_set_t *", NULL}, "int"},
    {"sched_getaffinity", {"pid_t", "size_t", "cpu_set_t *", NULL}, "int"},
    {"set_thread_area", {"struct user_desc *", NULL}, "int"},
    {"io_setup", {"unsigned int", "aio_context_t *", NULL}, "int"},
    {"io_destroy", {"aio_context_t", NULL}, "int"},
    {"io_getevents",
    {"aio_context_t", "long", "long", "struct io_event *", "struct timespec *",
    NULL}, "int"},
    {"io_submit", {"aio_context_t", "long", "struct iocb **", NULL}, "int"},
    {"io_cancel",
    {"aio_context_t", "struct iocb *", "struct io_event *", NULL}, "int"},
    {"get_thread_area", {"struct user_desc *", NULL}, "int"},
    {"lookup_dcookie", {"u64", "char *", "size_t", NULL}, "int"},
    {"epoll_create", {"int", NULL}, "int"},
    {"epoll_ctl_old", {"void", NULL}, "unimplemented"},
    {"epoll_wait_old", {"void", NULL}, "unimplemented"},
    {"remap_file_pages",
    {"void *", "size_t", "int", "ssize_t", "int", NULL}, "int"},
    {"getdents64",
    {"unsigned int", "struct linux_dirent *", "unsigned int", NULL}, "int"},
    {"set_tid_address", {"int *", NULL}, "long"},
    {"restart_syscall", {"int", "int", NULL}, "int"},
    {"semtimedop",
    {"int", "struct sembuf *", "unsigned int", "struct timespec *", NULL},
    "int"},
    {"fadvise64", {"int", "off_t", "off_t", "int", NULL}, "int"},
    {"timer_create",
    {"clockid_t", "struct sigevent *", "time_t *", NULL}, "int"},
    {"timer_settime",
    {"timer_t", "int", "struct itimerspec *", "struct itimerspec *", NULL},
    "int"},
    {"timer_gettime", {"timer_t", "struct itimerspec *", NULL}, "int"},
    {"timer_getoverrun", {"timer_t", NULL}, "int"},
    {"timer_delete", {"timer_t", NULL}, "int"},
    {"clock_settime", {"clockid_t", "struct timespec *", NULL}, "int"},
    {"clock_gettime", {"clockid_t", "struct timespec *", NULL}, "int"},
    {"clock_getres", {"clockid_t", "struct timespec *", NULL}, "int"},
    {"clock_nanosleep",
    {"clockid_t", "int", "struct timespec *", "struct timespec *", NULL},
    "int"},
    {"exit_group", {"int", NULL}, "void"},
    {"epoll_wait", {"int", "struct epoll_event *", "int", "int", NULL}, "int"},
    {"epoll_ctl", {"int", "int", "int", "struct epoll_event *", NULL}, "int"},
    {"tgkill", {"int", "int", "int", NULL}, "int"},
    {"utimes", {"char *", "struct timeval *", NULL}, "int"},
    {"vserver", {"int", "int", NULL}, "int"},
    {"mbind", {"void *", "unsigned long", "int", "unsigned long *",
    "unsigned long", "unsigned int", NULL}, "int"},
    {"set_mempolicy", {"int", "unsigned long *", "unsigned long", NULL}, "int"},
    {"get_mempolicy", {"int *", "unsigned long *", "unsigned long",
    "unsigned long", "unsigned long", NULL}, "int"},
    {"mq_open", {"int", "int", NULL}, "int"},
    {"mq_unlink", {"char *", NULL}, "int"},
    {"mq_timedsend", {"mqd_t", "char *", "size_t",
    "unsigned int", "struct timespec *", NULL}, "int"},
    {"mq_timedreceive", {"mqd_t", "char *", "size_t",
    "unsigned int", "struct timespec *", NULL}, "int"},
    {"mq_notify", {"mqd_t", "struct sigevent *", NULL}, "int"},
    {"mq_getsetattr", {"mqd_t", "struct mq_attr *",
    "struct mq_attr *", NULL}, "int"},
    {"kexec_load", {"unsigned long", "unsigned long",
    "struct kexec_segment *", "unsigned long", NULL}, "int"},
    {"waitid", {"idtype_t", "id_t", "siginfo_t", "int", NULL}, "int"},
    {"add_key", {"char *", "char *", "void *", "size_t", "key_serial_t", NULL},
    "key_serial_t"},
    {"request_key", {"char *", "char *", "char *", "key_serial_t", NULL},
    "key_serial_t"},
    {"keyctl", {"int", NULL}, "int"},
    {"ioprio_set", {"int", "int", "int", NULL}, "int"},
    {"ioprio_get", {"int", "int", NULL}, "int"},
    {"inotify_init", {"void", NULL}, "int"},
    {"inotify_add_watch", {"int", "char *", "uint32_t", NULL}, "int"},
    {"inotify_rm_watch", {"int", "int", NULL}, "int"},
    {"migrate_pages",
    {"int", "unsigned long", "unsigned long *", "unsigned long *", NULL},
    "long"},
    {"openat", {"int", "char *", "int", NULL}, "int"},
    {"mkdirat", {"int", "char *", "mode_t", NULL}, "int"},
    {"mknodat", {"int", "char *", "mode_t", "dev_t", NULL}, "int"},
    {"fchownat", {"int", "char *", "uid_t", "gid_t", "int", NULL}, "int"},
    {"futimesat", {"int", "char *", "struct timeval *", NULL}, "int"},
    {"fstatat", {"int", "char *", "struct stat *", "int", NULL}, "int"},
    {"unlinkat", {"int", "char *", "int", NULL}, "int"},
    {"renameat", {"int", "char *", "int", "char *", NULL}, "int"},
    {"linkat", {"int", "char *", "int", "char *", "int", NULL}, "int"},
    {"symlinkat", {"char *", "int", "char *", NULL}, "int"},
    {"readlinkat", {"int", "char *", "char *", "size_t", NULL}, "int"},
    {"fchmodat", {"int", "char *", "mode_t", "int", NULL}, "int"},
    {"faccessat", {"int", "char *", "int", "int", NULL}, "int"},
    {"pselect6", {"int", "fd_set *", "fd_set *", "fd_set *",
    "struct timespec *", "sigset_t", NULL}, "int"},
    {"ppoll", {"struct pollfd *", "nfds_t",
    "struct timespec *", "sigset_t *", NULL}, "int"},
    {"unshare", {"int", NULL}, "int"},
    {"set_robust_list", {"struct robust_list_head *", "size_t", NULL}, "long"},
    {"get_robust_list", {"int", "char *", "int", "char *", "int", NULL}, "int"},
    {"splice",
    {"int", "loff_t *", "int", "loff_t *", "size_t", "unsigned int", NULL},
    "ssize_t"},
    {"tee", {"int", "int", "size_t", "unsigned int", NULL}, "ssize_t"},
    {"sync_file_range",
    {"int", "off64_t", "off64_t", "unsigned int", NULL}, "int"},
    {"vmsplice",
    {"int", "struct iovec *", "unsigned long", "unsigned int", NULL},
    "ssize_t"},
    {"move_pages",
    {"int", "unsigned long", "void **", "int *", "int *", "int", NULL},
    "long"},
    {"utimensat", {"int", "char *", "struct timespec[]", "int", NULL}, "int"},
    {"epoll_pwait",
    {"int", "struct epoll_event *", "int", "int", "sigset_t", NULL}, "int"},
    {"signalfd", {"int", "sigset_t *", "int", NULL}, "int"},
    {"timerfd_create", {"int", "int", NULL}, "int"},
    {"eventfd", {"unsigned int", "int", NULL}, "int"},
    {"fallocate", {"int", "int", "off_t", "off_t", NULL}, "int"},
    {"timerfd_settime",
    {"int", "int", "struct itimerspec *", "struct itimerspec *", NULL}, "int"},
    {"timerfd_gettime", {"int", "struct itimerspec *", NULL}, "int"},
    {"accept4", {"int", "struct sockaddr *", "socklen_t", "int", NULL}, "int"},
    {"signalfd4", {"int", "sigset_t *", "int", NULL}, "int"},
    {"eventfd2", {"int", "char *", "struct timespec *", "int", NULL}, "int"},
    {"epoll_create1", {"int", NULL}, "int"},
    {"dup2", {"int", "int", NULL}, "int"},
    {"pipe2", {"int[2]", "int", NULL}, "int"},
    {"inotify_init1", {"int", NULL}, "int"},
    {"preadv", {"int", "struct iovec *", "int", "off_t", NULL}, "ssize_t"},
    {"pwritev", {"int", "struct iovec *", "int", NULL}, "ssize_t"},
    {"sys_rt_tgsigqueueinfo", {"int", "int", "siginfo_t *", NULL}, "long"},
    {"perf_event_open",
    {"int", "struct sockaddr *", "socklen_t", "int", NULL}, "int"},
    {"recvmmsg", {"int", "struct mmsghdr *", "unsigned int",
    "unsigned int", "struct timespec *", NULL}, "int"},
    {"fanotify_init",
    {"int", "struct sockaddr *", "socklen_t", "int", NULL}, "int"},
    {"fanotify_init",
    {"int", "struct sockaddr *", "socklen_t", "int", NULL}, "int"},
    {"prlimit",
    {"pid_t", "int", "struct rlimit *", "struct rlimit *", NULL}, "int"},
    {"name_to_handle_at", {"int", NULL}, "int"},
    {"open_to_handle_at",
    {"int", "struct iovec *", "int", "off_t", NULL}, "ssize_t"},
    {"clock_adjtime", {"int", "struct iovec *", "int", NULL}, "ssize_t"},
    {"syncfs", {"int", NULL}, "int"},
    {"sendmmsg",
    {"int", "struct mmsghdr *", "unsigned int", "unsigned int", NULL}, "int"},
    {"setns", {"int", "int", NULL}, "int"},
    {"getcpu",
    {"unsigned *", "unsigned *", "struct getcpu_cache *", NULL}, "int"},
    {"process_vm_readv",
    {"pid_t", "struct iovec *", "unsigned long",
    "struct iovec *", "unsigned long", "unsigned long", NULL}, "ssize_t"},
    {"process_vm_writev",
    {"pid_t", "struct iovec *", "unsigned long",
    "struct iovec *", "unsigned long", "unsigned long", NULL}, "ssize_t"},
    {"kcmp",
    {"pid_t", "pid_t", "int", "unsigned long", "unsigned long", NULL}, "int"},
    {"finit_module", {"int", "char *", "int", NULL}, "int"}
};

#endif