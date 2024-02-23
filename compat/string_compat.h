#ifndef SHIKI_STRING_COMPAT_H
#define SHIKI_STRING_COMPAT_H

#include <linux/version.h> //KERNEL_VERSION()
#include <linux/types.h> //ssize_t

#if LINUX_VERSION_CODE <= KERNEL_VERSION(4,3,0)
ssize_t __must_check strscpy(char *, const char *, size_t);
#endif

#endif //SHIKI_STRING_COMPAT_H
