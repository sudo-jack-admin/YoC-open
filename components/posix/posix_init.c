/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#include "posix_init.h"

extern int pthread_lock_init(void);
extern int timer_lock_init(void);
extern int tmpnam_lock_init(void);
extern int enviro_lock_init(void);

int ramfs_mount(void);

int posix_init(void)
{
    int ret = -1;

#if (POSIX_CONFIG_PTHREAD_ENABLE > 0)
    ret = pthread_lock_init();
    if (ret != 0) {
        return -1;
    }
#endif

#if (POSIX_CONFIG_TIMER_ENABLE > 0)
    ret = timer_lock_init();
    if (ret != 0) {
        return -1;
    }
#endif

#if (POSIX_CONFIG_DIRENT_ENABLE > 0)
#if (POSIX_CONFIG_DIRENT_TMPFILE_ENABLE > 0)
    ret = tmpnam_lock_init();
    if (ret != 0) {
        return -1;
    }

    ret = ramfs_mount();
    if (ret != 0) {
        return -1;
    }

#endif
#endif

#if (POSIX_CONFIG_ENVIRO_ENABLE > 0)
    ret = enviro_lock_init();
    if (ret != 0) {
        return -1;
    }
#endif

    return ret;
}

#if (POSIX_CONFIG_DIRENT_TMPFILE_ENABLE > 0)
int ramfs_mount(void)
{
    return ramfs_register("/ramfs");
}
#endif
