#include "AsyncGetAddrInfo.hpp"
#include "zby_debug.h"


bool AsyncGetAddrInfoEx::Lookup(uv_loop_t* loop, const char* host, IHandleAddrResutl* pHandler, bool cacheFirst)
{
    bool ret = false;
    do {
        if( NULL == pHandler ) {
            SYS_ERR("handler null");
            break;
        }

         if(NULL == host) {
            SYS_ERR("host  null");
            break;
        } 

        if ( cacheFirst ){
            auto it = m_addrMap.find(host);
            if(it != m_addrMap.end()) {
                AddrIpInfo& info = it->second;
                pHandler->OnResolved(info.status, host, info.ip.c_str());
                ret = true;
                break;
            }
        }

        AddrReq* pReq = new AddrReq();
        pReq->hostName = host;
        memset(&(pReq->addrReq), 0, sizeof(pReq->addrReq));
        pReq->addrReq.data = this;
        pReq->Handler = pHandler;
        struct addrinfo ai;
        ai.ai_family = PF_INET;
        ai.ai_socktype = SOCK_STREAM;
        ai.ai_protocol = IPPROTO_TCP;
        ai.ai_flags = 0;

        int result = uv_getaddrinfo(loop, &(pReq->addrReq),
            [](uv_getaddrinfo_t* req, int status, struct addrinfo* res) {
                AddrReq* pReq = (AddrReq*)req;
                do {
                    AsyncGetAddrInfoEx* pCl = (AsyncGetAddrInfoEx*)(req->data);
                    if(NULL == pCl) {
                        SYS_ERR("AsyncGetAddrInfo null");
                        break;
                    }
                    
                    AddrIpInfo info;
                    info.status = status;
                    char addr[17] = { 0 };
                    if(status == 0 && res) {
                        uv_ip4_name((struct sockaddr_in*)res->ai_addr, addr, 16);
                        info.ip = addr;
                    } else {
                        info.ip = "";
                    }
                    pCl->m_addrMap[pReq->hostName] = info;
                    IHandleAddrResutl* hd = pReq->Handler;
                    if(hd) {
                        hd->OnResolved(status, pReq->hostName.c_str(), addr);
                    }
                } while(false);

                if(res) {
                    uv_freeaddrinfo(res);
                }
                delete pReq;
            },
            pReq->hostName.c_str(), NULL, &ai);
    
        if ( result ){
            delete pReq;
            break;
        }
        ret = true;
    } while(false);

    return ret;
}

void AsyncGetAddrInfoEx::ClearCache()
{
    m_addrMap.clear();
}
