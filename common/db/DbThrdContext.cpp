#include "appnetstack.h"
#include "DbThrdContext.hpp"
#include "zby_debug.h"

DbThrdContext::DbThrdContext(DBInfo& info)
{
    this->_dbInfo = info;
    _conn = NULL;
}

DbThrdContext::~DbThrdContext()
{
}

bool DbThrdContext::Init(MWorkThread& thread, uv_loop_t* loop_)
{
    return this->ConnectDb();
}

void DbThrdContext::OnStart()
{
    DB_INFO("db start");
}

void DbThrdContext::OnEnd()
{
   
    DB_INFO("db end");
}

void DbThrdContext::OnWaitTimeout(int timeoutTimes)
{
    CloseDb();
}

bool DbThrdContext::ConnectDb()
{
    bool ret = false;
    do {
        _conn = mysql_init(NULL);
        if(NULL == _conn) {
            DB_ERR("system init error: Cannot connect to  mysql db");
            break;
        }
        
        if(!mysql_real_connect(_conn, _dbInfo.host.c_str(), _dbInfo.user.c_str(), _dbInfo.passwd.c_str(), _dbInfo.db.c_str(), _dbInfo.port,
               NULL, _dbInfo.flag)) {
            int err = mysql_errno(_conn);
            DB_ERR("mysql_real_connect failed for %d %s", err, mysql_error(_conn));
            break;
        }
        ret = true;
    } while(false);
    return ret;
}

void DbThrdContext::CloseDb()
{
     if ( _conn ){
        mysql_close(_conn);
        _conn = NULL;
    }
}
void DbThrdContext::CheckDb()
{
    if ( NULL == _conn ){
        this->ConnectDb();
    }
}

void DbThrdContext::BeforeExecute()
{
    this->CheckDb();
}

void DbThrdContext::OnExecuteErr()
{
    DB_ERR("DB EXECUTE ERR");
    this->CloseDb();
}
//////////////////////////////////////////////////////////////////////////////
bool DbThrdMgr::StartDb(int thread_count, uv_loop_t* loop, DBInfo& info)
{
    if(!this->Init<DbThrdContext>(thread_count, loop, info)) {
        DB_ERR("INIT DB err ");
        return false;
    }

    if(!this->Start()) {
        DB_ERR("start db err");
        return false;
    }
    return true;
}

bool DbThrdMgr::StartDb(int thread_count,
    uv_loop_t* loop,
    const char* pHost,
    const char* pUser,
    const char* pwd,
    const char* pDb,
    uint16_t port,
    unsigned long flag)
{
    DBInfo info;
    info.db = pDb;
    info.flag = flag;
    info.host = pHost;
    info.passwd = pwd;
    info.port  = port;
    info.user  = pUser;
    return StartDb(thread_count, loop, info);
}
