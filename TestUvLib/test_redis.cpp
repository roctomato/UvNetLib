#include "asyncredis.h"
#include "chiredisbase.h"
#include "event_loop.h"
#include "zby_debug.h"

extern event_loop loop;

bool HandleSetFoo(redisAsyncContext* c, AsyncRedis* redis, CHiredisReply& reply, void* param)
{
    reply.Print();
    
    return true;
}

class TestAsync : public AsyncRedis
{
public:
    void OnConnect(int status)
    {
        this->Exec(HandleSetFoo, NULL, "set foo bar");
        this->Exec(HandleSetFoo, NULL, "get foo");
    }

    void OnDisconnect(int status)
    {
    }
};

class WatchAsync : public AsyncRedis
{
public:
    void OnConnect(int status)
    {
        this->ExecRepeatCallback(HandleSetFoo, NULL, "subscribe h");
    }

    void OnDisconnect(int status)
    {
    }
};

TestAsync recvr;
WatchAsync async;

void block_test(){
        CHiredisBase redis;
    bool ok = redis.Connect("192.168.11.50", 6379, 0, "123456");

    SYS_DEBUG("CONNECT redis %s", ok ? "ok" : "failed");

    if(ok) {
        BlockRedisCmmd cmd(redis);
        SharePrtReply reply = cmd.redisCommand("set foo bar");
        if(reply) {
            reply->Print();
        }
        // reply.reset();

        reply = cmd.redisCommand("get foo");
        reply->Print();
        // reply.reset();

        PipelineRedisCmmd pmd(redis);
        pmd.redisAppendCommand("set foo bar");
        pmd.redisAppendCommand("get foo");

        reply = pmd.RedisGetReply();
        reply->Print();

        reply = pmd.RedisGetReply();
        reply->Print();

        reply = pmd.RedisGetReply();
        reply->Print();
    }
}

void test_block_redis()
{
    block_test();
    recvr.Connect("192.168.11.50", 6379, loop.loop(), 0, "123456");
    async.Connect("192.168.11.50", 6379, loop.loop(), 0, "123456");
}