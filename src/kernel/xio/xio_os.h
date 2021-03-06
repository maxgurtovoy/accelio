/*
 * Copyright (c) 2013 Mellanox Technologies®. All rights reserved.
 *
 * This software is available to you under a choice of one of two licenses.
 * You may choose to be licensed under the terms of the GNU General Public
 * License (GPL) Version 2, available from the file COPYING in the main
 * directory of this source tree, or the Mellanox Technologies® BSD license
 * below:
 *
 *      - Redistribution and use in source and binary forms, with or without
 *        modification, are permitted provided that the following conditions
 *        are met:
 *
 *      - Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 *      - Neither the name of the Mellanox Technologies® nor the names of its
 *        contributors may be used to endorse or promote products derived from
 *        this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef XIO_OS_H
#define XIO_OS_H

#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/kref.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/llist.h>

#include <linux/net.h>
#include <linux/in.h>
#include <linux/in6.h>
#include <linux/version.h>
#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 37)
#include <asm/atomic.h>
#else
#include <linux/atomic.h>
#endif

/* /usr/include/bits/types.h: *__STD_TYPE __U32_TYPE __socklen_t; */
typedef u32 __socklen_t;
/*
/usr/include/arpa/inet.h:typedef __socklen_t socklen_t;
/usr/include/unistd.h:typedef __socklen_t socklen_t;
*/
typedef __socklen_t socklen_t;

#define assert(expr) BUG_ON(!(expr))

#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 1, 0)
static inline int __atomic_add_unless(atomic_t *v, int a, int u)
{
	int c, old;
	c = atomic_read(v);
	while (c != u && (old = atomic_cmpxchg(v, c, c + a)) != c)
		c = old;
	return c;
}
#endif

static inline char *strerror(int errnum)
{
	static char buf[64];
	sprintf(buf, "errno(%d)", errnum);
	return buf;
};

#define PRIu64 "llu"

#endif /* XIO_OS_H */
