/*
 * This file is part of usysconf.
 *
 * Copyright © 2017-2019 Solus Project
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#define _GNU_SOURCE

#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "config.h"
#include "util.h"

/**
 * Ensure that /dev/null is actually a character device and exists,
 * so that we don't try to redirect stdout to the disk.
static bool dev_null_not_cranky(void)
{
        struct stat st = { 0 };
        if (stat("/dev/null", &st) != 0) {
                return false;
        }
        if (!S_ISCHR(st.st_mode)) {
                return false;
        }
        return true;
}*/

/**
 * Redirect the file descriptor to the named file
 */
static void redirect_fileno_named(int file_no, const char *file, int mode)
{
        int fd = -1;
        fd = open(file, mode, 00644);
        dup2(fd, file_no);
        close(fd);
}

/**
 * Redirect the file descriptor to /dev/null
static void redirect_fileno_devnull(int file_no)
{
        redirect_fileno_named(file_no, "/dev/null", O_WRONLY);
}*/

int usc_exec_command(char **command)
{
        pid_t p;
        int status = 0;
        int ret = 0;
        int r = -1;

        if ((p = fork()) < 0) {
                fprintf(stderr, "Failed to fork(): %s\n", strerror(errno));
                return -1;
        } else if (p == 0) {
                /* Force all output to a temporary log file */
                redirect_fileno_named(STDOUT_FILENO,
                                      USYSCONF_REWIND_LOG_FILE,
                                      O_WRONLY | O_CREAT | O_APPEND);
                redirect_fileno_named(STDERR_FILENO,
                                      USYSCONF_REWIND_LOG_FILE,
                                      O_WRONLY | O_CREAT | O_APPEND);

                /* Execute the command */
                if ((r = execv(command[0], command)) != 0) {
                        fprintf(stderr, "Failed to execve(%s): %s\n", command[0], strerror(errno));
                        exit(EXIT_FAILURE);
                }
                _exit(EXIT_SUCCESS);
                /* We'd never actually get here. */
        } else {
                if (waitpid(p, &status, 0) < 0) {
                        fprintf(stderr, "Failed to waitpid(%d): %s\n", (int)p, strerror(errno));
                        return -1;
                }
                /* i.e. sigsev */
                if (!WIFEXITED(status)) {
                        fprintf(stderr, "Child process '%s' exited abnormally\n", command[0]);
                }
        }

        /* At this point just make sure the return code was 0 */
        ret = WEXITSTATUS(status);
        return ret;
}

char *usc_get_strn_component(const char *inp_path, ssize_t whence)
{
        char *c = NULL;
        char *snd = NULL;
        ssize_t i;

        c = (char *)inp_path;

        for (i = 0; i <= whence; i++) {
                c = strchr(c, '/');
                if (!c) {
                        return NULL;
                }
                c++;
        }

        if (i != whence + 1) {
                return NULL;
        }

        snd = strchr(c, '/');
        if (snd) {
                return strndup(c, (size_t)(snd - c));
        }
        return strdup(c);
}

/*
 * Editor modelines  -  https://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 8
 * tab-width: 8
 * indent-tabs-mode: nil
 * End:
 *
 * vi: set shiftwidth=8 tabstop=8 expandtab:
 * :indentSize=8:tabSize=8:noTabs=true:
 */
