#include "crossplatform.h"

#ifndef _WIN32
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <poll.h>

void os_contextInit() {

}

void os_contextCleanup() {

}

void os_closeFd(fd_t fd) {
    close(fd);
}

int os_connect(fd_t s, const struct sockaddr *addr, socklen_t addrlen) {
    return os_connect(s, addr, addrlen);
}

int os_setsockopt(fd_t s, int level, int optname, const void *optval, socklen_t optlen) {
    return setsockopt(s, level, optname, optval, optlen);
}

int os_getsockopt(fd_t s, int level, int optname, void *optval, socklen_t *optlen) {
    return getsockopt(s, level, optname, optval, optlen);
}

ssize_t os_write(fd_t fd, const void *buf, size_t count) {
    return write(fd, buf, count);
}

ssize_t os_read(fd_t fd, void *buf, size_t count) {
    return read(fd, buf, count);
}

int os_poll(struct pollfd *fds, nfds_t nfds, int timeout) {
    return poll(fds, nfds, timeout);
}

#else

#include <io.h>
#include <assert.h>

void os_contextInit() {
    WORD wVersionRequested;
    WSADATA wsaData;

    wVersionRequested = MAKEWORD(2, 2);
    WSAStartup(wVersionRequested, &wsaData);
}

void os_contextCleanup() {
    WSACleanup();
}

void os_close(fd_t fd) {
    closesocket(fd);
}

int os_connect(fd_t s, const struct sockaddr *addr, socklen_t addrlen) {
    int ret = connect(s, addr, addrlen);
    if (ret == SOCKET_ERROR) {
        errno = convertWsaErrorToUnixError(WSAGetLastError());
        if (errno == EAGAIN) {
            errno = EINPROGRESS;
        }
    }
    return ret;
}

int os_setsockopt(fd_t s, int level, int optname, const void *optval, socklen_t optlen) {
    int ret = setsockopt(s, level, optname, (const char*)optval, optlen);
    if (ret == SOCKET_ERROR) {
        errno = convertWsaErrorToUnixError(WSAGetLastError());
    }
    return ret;
}

int os_getsockopt(fd_t s, int level, int optname, void *optval, socklen_t *optlen) {
    int ret = getsockopt(s, level, optname, (char *)optval, optlen);
    if (ret == SOCKET_ERROR)
        errno = convertWsaErrorToUnixError(WSAGetLastError());

    if (level == SOL_SOCKET && optname == SO_ERROR) {
        *(int*)optval = convertWsaErrorToUnixError(*(int*)optval);
    }
    return ret;
}

ssize_t os_write(fd_t fd, const void *buf, size_t count) {
    ssize_t nwriten = 0;
    nwriten = send(fd, (const char*)buf, (int)count, 0);
    if (nwriten == SOCKET_ERROR) {
        errno = convertWsaErrorToUnixError(WSAGetLastError());
    }
    return nwriten;
}

ssize_t os_read(fd_t fd, void *buf, size_t count) {
    ssize_t nread = 0;
    nread = recv(fd, (char* )buf, (int)count, 0);
    if (nread == SOCKET_ERROR) {
        errno = convertWsaErrorToUnixError(WSAGetLastError());
    }
    return nread;
}

int _os_fcntl(fd_t fd, int cmd, ... /* arg */ ) {
    va_list args;
    int flag = 0;
    u_long nonblock = 0;
    int ret = SOCKET_ERROR;

    assert(cmd == F_GETFL || cmd == F_SETFL);

    va_start(args, cmd);

    if (cmd == F_GETFL) {
        ret = ioctlsocket(fd, FIONBIO, &nonblock);
        if (nonblock)
        {
            flag |= O_NONBLOCK;
        }
    } else if (cmd == F_SETFL) {
        flag = va_arg(args, int);

        if (flag & O_NONBLOCK) {
            nonblock = 1;
        }
        ret = ioctlsocket(fd, FIONBIO, &nonblock);
    }

    va_end(args);

    if (ret == SOCKET_ERROR) {
        errno = convertWsaErrorToUnixError(WSAGetLastError());
        return -1;
    }

    return flag;
}

int os_poll(struct pollfd *fds, nfds_t nfds, int timeout) {
    int ret = WSAPoll(fds, nfds, timeout);
    if (ret == SOCKET_ERROR) {
        errno = convertWsaErrorToUnixError(WSAGetLastError());
    }
    return ret;
}

int convertWsaErrorToUnixError(int error) {
    switch (error) {
        case WSAEINTR: return EINTR;
        case WSAEBADF: return EBADF;
        case WSAEACCES: return EACCES;
        case WSAEFAULT: return EFAULT;
        case WSAEINVAL: return EINVAL;
        case WSAEMFILE: return EMFILE;
        case WSAEWOULDBLOCK: return EAGAIN;
        case WSAEINPROGRESS: EINPROGRESS;
        case WSAEALREADY: return EALREADY;
        case WSAENOTSOCK: return ENOTSOCK;
        case WSAEDESTADDRREQ: return EDESTADDRREQ;
        case WSAEMSGSIZE: return EMSGSIZE;
        case WSAEPROTOTYPE: return EPROTOTYPE;
        case WSAENOPROTOOPT: return ENOPROTOOPT;
        case WSAEPROTONOSUPPORT: return EPROTONOSUPPORT;
        case WSAESOCKTNOSUPPORT: return EPROTONOSUPPORT;
        case WSAEOPNOTSUPP: return EOPNOTSUPP;
        case WSAEPFNOSUPPORT: return EPROTONOSUPPORT;
        case WSAEAFNOSUPPORT: return EAFNOSUPPORT;
        case WSAEADDRINUSE: return EADDRINUSE;
        case WSAEADDRNOTAVAIL: return EADDRNOTAVAIL;
        case WSAENETDOWN: return ENETDOWN;
        case WSAENETUNREACH: return ENETUNREACH;
        case WSAENETRESET: return ENETRESET;
        case WSAECONNABORTED: return ECONNABORTED;
        case WSAECONNRESET: return ECONNRESET;
        case WSAENOBUFS: return ENOBUFS;
        case WSAEISCONN: return EISCONN;
        case WSAENOTCONN: return ENOTCONN;
        case WSAESHUTDOWN: return ENOTCONN;
        //case WSAETOOMANYREFS: return EMFILE;
        case WSAETIMEDOUT: return ETIMEDOUT;
        case WSAECONNREFUSED: return ECONNREFUSED;
        case WSAELOOP: return ELOOP;
        case WSAENAMETOOLONG: return ENAMETOOLONG;
        case WSAEHOSTDOWN: return EHOSTUNREACH;
        case WSAEHOSTUNREACH: return EHOSTUNREACH;
        case WSAENOTEMPTY: return ENOTEMPTY;
        //case WSAEPROCLIM: return EPROCLIM;
        //case WSAEUSERS: return EUSERS;
        //case WSAEDQUOT: return EDQUOT;
        //case WSAESTALE: return ESTALE;
        //case WSAEREMOTE: return EREMOTE;
        //case WSASYSNOTREADY: return SYSNOTREADY;
        //case WSAVERNOTSUPPORTED: return VERNOTSUPPORTED;
        //case WSANOTINITIALISED: return NOTINITIALISED;
        //case WSAEDISCON: return EDISCON;
        //case WSAENOMORE: return ENOMORE;
        //case WSAECANCELLED: return ECANCELLED;
        //case WSAEINVALIDPROCTABLE: return EINVALIDPROCTABLE;
        //case WSAEINVALIDPROVIDER: return EINVALIDPROVIDER;
        //case WSAEPROVIDERFAILEDINIT: return EPROVIDERFAILEDINIT;
        //case WSASYSCALLFAILURE: return SYSCALLFAILURE;
        //case WSASERVICE_NOT_FOUND: return SERVICE_NOT_FOUND;
        //case WSATYPE_NOT_FOUND: return TYPE_NOT_FOUND;
        //case WSA_E_NO_MORE: return _E_NO_MORE;
        //case WSA_E_CANCELLED: return _E_CANCELLED;
        //case WSAEREFUSED: return EREFUSED;
        default:
            return error;
    }
}

#endif
