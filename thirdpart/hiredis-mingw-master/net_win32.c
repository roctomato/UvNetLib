#include "net.h"

#ifdef _WIN32

void __redisSetError(redisContext *c, int type, const char *str);

int redisContextConnectUnix(redisContext *c, const char *path, const struct timeval *timeout) {
    __redisSetError(c,REDIS_ERR_IO, "Unix sockets are not supported on Windows platform.\n");
    return REDIS_ERR;
}

#endif