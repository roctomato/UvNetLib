#include "asyncredis.h"
#include "chiredisbase.h"
#include "zby_debug.h"

AsyncRedis::AsyncRedis()
{
    _context = NULL;
    _bConnect = false;
    _cnntState = REDIS_STATE_DISCONNECT;
    _password = NULL;
    //_redisState = -1;
}

AsyncRedis::~AsyncRedis()
{
    if(_context)
        redisAsyncFree(_context);
}

bool AsyncRedis::Connect(const char* ip, int port, uv_loop_t* loop, int index, const char* password)
{
    _context = redisAsyncConnect(ip, port);
    if(_context->err) {
        /* Let *c leak for now... */
        SYS_ERR("Error: %s\n", _context->errstr);
        return false;
    }
    _redisIdx = index;
    if ( password )_password = password;
    _context->data = this;

    redisLibuvAttach(_context, loop);
    redisAsyncSetConnectCallback(_context, ConnectCallback);
    redisAsyncSetDisconnectCallback(_context, DisonnectCallback);
    _cnntState = REDIS_STATE_CONNECTING;
    return true;
}

void AsyncRedis::ConnectCallback(const redisAsyncContext* c, int status)
{
    if(c->data) {
        AsyncRedis* pIns = (AsyncRedis*)c->data;
        pIns->HandleAuthPassword(status);
    }
}

void AsyncRedis::DisonnectCallback(const redisAsyncContext* c, int status)
{
    if(c->data) {
        AsyncRedis* pIns = (AsyncRedis*)c->data;
        pIns->HandleDisconnet(status);
    }
}
void AsyncRedis::HandleDisconnet(int status)
{
    _bConnect = false;
    _cnntState = REDIS_STATE_DISCONNECT;
    OnDisconnect(status);
}

void AsyncRedis::CmdCallback(redisAsyncContext* c, void* r, void* privdata)
{
    HackFunc* data = (HackFunc*)privdata;
    redisReply* reply = (redisReply*)r;

    if(data) {
        do {
            AsyncRedis* pIns = (AsyncRedis*)data->redis;
            if(NULL == pIns) {
                break;
            }

            if(NULL == reply && c->err && strlen(c->errstr)>0 ) {
                NET_ERR("redis err %d %s", c->err, c->errstr);
            }
            CHiredisReply hreply(reply, false);

            if(data->fn) {
                data->fn(c, pIns, hreply, data->param);
                break;
            }

            hreply.Print();

        } while(false);

        if(data->auto_delete)
            delete data;
    }
}

void AsyncRedis::HandleConnect(int status)
{
    auto f = [](redisAsyncContext* c, AsyncRedis* redis, CHiredisReply& reply, void* param) -> bool {
        redis->_bConnect = true;
        redis->_cnntState = REDIS_STATE_CONNECTED;
        redis->OnConnect(c->err);
        return true;
    };

    char cmd[128];
    sprintf(cmd, "select %d", this->_redisIdx);
    Exec(f, NULL, cmd);
}

void AsyncRedis::OnConnect(int status)
{
    if(status != REDIS_OK) {
        SYS_ERR("Error: %s\n", _context->errstr);
        return;
    }

    printf("Connected...\n");
}

void AsyncRedis::OnDisconnect(int status)
{
    if(status != REDIS_OK) {
        SYS_ERR("Error: %s\n", _context->errstr);
        return;
    }
    printf("Disconnected...\n");
}

int AsyncRedis::ExecRepeatCallback(HandleRedis fn, void* param, const char* format, ...)
{
    HackFunc* privateData = new HackFunc();
    privateData->redis = this;
    privateData->fn = fn;
    privateData->param = param;
    privateData->auto_delete = false;
    va_list ap;
    int status;
    va_start(ap, format);
    status = redisvAsyncCommand(_context, AsyncRedis::CmdCallback, privateData, format, ap);
    va_end(ap);
    return status;
}

int AsyncRedis::Exec(HandleRedis fn, void* param, const char* format, ...)
{
    HackFunc* privateData = new HackFunc();
    privateData->redis = this;
    privateData->fn = fn;
    privateData->param = param;
    privateData->auto_delete = true;
    va_list ap;
    int status;
    va_start(ap, format);
    status = redisvAsyncCommand(_context, AsyncRedis::CmdCallback, privateData, format, ap);
    va_end(ap);
    return status;
}

void AsyncRedis::HandleAuthPassword(int status)
{
    // this->_redisState = status;

    if(NULL == this->_password) {
        this->HandleConnect(status);
    } else {
        if(status == REDIS_OK) {
            if(_redisIdx != -1) {
                char cmd[128];
                sprintf(cmd, "auth %s", this->_password);
                auto f = [](redisAsyncContext* c, AsyncRedis* redis, CHiredisReply& reply, void* param) -> bool {
                    redis->HandleConnect(c->err);
                    return true;
                };
                Exec(f, NULL, cmd);
            }
        }
    }
}
