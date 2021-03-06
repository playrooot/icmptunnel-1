/*
 *  https://github.com/jamesbarlow/icmptunnel
 *
 *  The MIT License (MIT)
 *
 *  Copyright (c) 2016 James Barlow-Bignell
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int daemon()
{
    int res;

    if ((res = fork()) < 0) {
        fprintf(stderr, "unable to fork: %s\n", strerror(errno));
        return -1;
    }

    /* if we're the parent process then exit. */
    if (res > 0)
        exit(0);

    /* set a new session id. */
    if (setsid() < 0) {
        fprintf(stderr, "unable to set sid: %s\n", strerror(errno));
        return -1;
    }

    /* redirect the standard streams to /dev/null. */
    int fd;

    if ((fd = open("/dev/null", O_RDWR)) < 0) {
        fprintf(stderr, "unable to open /dev/null: %s\n", strerror(errno));
        return -1;
    }
/*
    int i;
    for (i = 0; i < 3; ++i) {
        dup2(fd, i);
    }

    if (fd >= 2) {
        close(fd);
    }
*/
    return 0;
}
