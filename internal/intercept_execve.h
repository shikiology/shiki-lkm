#ifndef SHIKI_INTERCEPT_EXECVE_H
#define SHIKI_INTERCEPT_EXECVE_H

//There's no remove_ as this requires rearranging the list etc and is not needed for now
int add_blocked_execve_filename(const char * filename);
int register_execve_interceptor(void);
int unregister_execve_interceptor(void);

#endif //SHIKI_INTERCEPT_EXECVE_H
