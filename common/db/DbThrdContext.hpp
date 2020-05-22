#ifndef DBTHRDCONTEXT_HPP
#define DBTHRDCONTEXT_HPP

#include "ThreadTask.hpp" // Base class: ThreadContext
#include "MWorkThread.hpp"
#include <mysql.h>

const unsigned long MYSQL_FLAG = CLIENT_MULTI_QUERIES| CLIENT_MULTI_RESULTS|CLIENT_MULTI_STATEMENTS;

struct DBInfo {
    std::string host;
    std::string user;
    std::string passwd;
    std::string db;
    uint16_t port;
    unsigned long flag;
};

class DbThrdContext : public ThreadContext
{
public:
    DbThrdContext(DBInfo& info);
    ~DbThrdContext();

    bool Init(MWorkThread& thread, uv_loop_t* loop_) override;
    void OnStart() override;
    void OnEnd() override;
    void OnWaitTimeout(int timeoutTimes) override;
    void BeforeExecute() override;
    void OnExecuteErr() override;
    
    bool ConnectDb();
    void CloseDb();
    void CheckDb();
    
    DBInfo _dbInfo;
    MYSQL*  _conn;
};

class DbThrdMgr : public MWorkThreadMgr
{
public:
    bool StartDb(int thread_count, uv_loop_t* loop, DBInfo& info);
    bool StartDb(int thread_count, uv_loop_t* loop, const char* pHost, const char* pUser, const char* pwd, const char* pDb, uint16_t port = 3306, unsigned long flag=MYSQL_FLAG);
};
#endif // DBTHRDCONTEXT_HPP
