#include "LsUtility.h"
#include "chiredisbase.h"
#include "zby_debug.h"

CHiredisBase::CHiredisBase()
    : _context(NULL)
{
}

CHiredisBase::~CHiredisBase()
{
    Close();
}

bool CHiredisBase::AddSet(std::string& key, std::string& data)
{
    LS_PRINT("SADD %s %s ", key.c_str(), data.c_str());
    if(NULL == _context) {
        return false;
    }
    redisReply* reply = (redisReply*)redisCommand(_context, "SADD %s %b ", key.c_str(), data.c_str(), data.size());
    bool ret = Check(reply);
    freeReplyObject(reply);
    return ret;
}

bool CHiredisBase::Check(redisReply* reply)
{
    if(NULL == _context) {
        return false;
    }
    if(_context->err) {
        DB_ERR("%s", _context->errstr);
        Close();
        Connect();
        return false;
    }
    if(reply && reply->type == REDIS_REPLY_ERROR) {
        DB_ERR("%s", reply->str);
        return false;
    }
    return true;
}

bool CHiredisBase::ClearAllData(std::string& key)
{
    if(NULL == _context) {
        return false;
    }
    redisReply* reply = (redisReply*)redisCommand(_context, "DEL %s", key.c_str());
    bool ret = Check(reply);
    freeReplyObject(reply);
    return ret;
}

void CHiredisBase::Close()
{
    if(_context) {
        redisFree(_context);
        _context = NULL;
    }
}

bool CHiredisBase::Connect()
{
    bool ret = false;
    struct timeval timeout = { 1, 500000 }; // 1.5 seconds
    _context = redisConnectWithTimeout(_ip.c_str(), _port, timeout);
    if(NULL == _context) {
        return false;
    }
    if(_context->err) {
        Close();
    } else {
        if("" != _password) {
            redisReply* reply_auth = (redisReply*)redisCommand(_context, "auth %s", _password.c_str());
            ret = Check(reply_auth);
            freeReplyObject(reply_auth);
        }

        redisReply* reply_select = (redisReply*)redisCommand(_context, "select %d", _index);
        ret = Check(reply_select);
        freeReplyObject(reply_select);
    }
    return ret;
}

bool CHiredisBase::Connect(const char* ip, unsigned short port, int index, const char* password)
{
    _ip = ip;
    _port = port;
    _index = index;
    _password = password;
    return Connect();
}

bool CHiredisBase::DelHash(std::string& key, std::string& data)
{
    LS_PRINT("HDEL %s %s ", key.c_str(), data.c_str());
    if(NULL == _context) {
        return false;
    }
    redisReply* reply = (redisReply*)redisCommand(_context, "HDEL %s %s ", key.c_str(), data.c_str());
    bool ret = Check(reply);
    freeReplyObject(reply);
    return ret;
}

bool CHiredisBase::DelSet(std::string& key, std::string& data)
{
    LS_PRINT("SREM %s %s ", key.c_str(), data.c_str());
    if(NULL == _context) {
        return false;
    }
    redisReply* reply = (redisReply*)redisCommand(_context, "SREM %s %b ", key.c_str(), data.c_str(), data.size());
    bool ret = Check(reply);
    freeReplyObject(reply);
    return ret;
}

bool CHiredisBase::GetAllHash(std::string& key, VecString& vecData)
{
    LS_PRINT("hgetall %s", key.c_str());
    if(NULL == _context) {
        return false;
    }
    redisReply* reply = (redisReply*)redisCommand(_context, "hgetall %s", key.c_str());
    bool ret = Check(reply);
    if(ret && reply->elements > 0) {
        vecData.resize(reply->elements);
        for(int j = 0; j < reply->elements; j++) {
            // LS_PRINT("%u) %s", j, reply->element[j]->str);
            vecData[j] = reply->element[j]->str;
        }
    }
    freeReplyObject(reply);
    return ret;
}
bool CHiredisBase::GetAllHashValue(std::string& key, VecString& vecData)
{
    LS_PRINT("hvals %s", key.c_str());
    if(NULL == _context) {
        return false;
    }
    redisReply* reply = (redisReply*)redisCommand(_context, "hvals %s", key.c_str());
    bool ret = Check(reply);
    if(ret && reply->elements > 0) {
        vecData.resize(reply->elements);
        for(int j = 0; j < reply->elements; j++) {
            // LS_PRINT("%u) %s", j, reply->element[j]->str);
            vecData[j] = reply->element[j]->str;
        }
    }
    freeReplyObject(reply);
    return ret;
}

bool CHiredisBase::GetAllSet(std::string& key, VecString& vecData)
{
    LS_PRINT("SMEMBERS %s", key.c_str());
    if(NULL == _context) {
        return false;
    }
    redisReply* reply = (redisReply*)redisCommand(_context, "SMEMBERS %s", key.c_str());
    bool ret = Check(reply);
    if(ret && reply->elements > 0) {
        vecData.resize(reply->elements);
        for(int j = 0; j < reply->elements; j++) {
            LS_PRINT("%u) %s", j, reply->element[j]->str);
            vecData[j] = reply->element[j]->str;
        }
    }
    freeReplyObject(reply);
    return ret;
}

bool CHiredisBase::SetHash(std::string& key, std::string& field, std::string& data)
{
    LS_PRINT("HSET %s %s %s", key.c_str(), field.c_str(), data.c_str());
    if(NULL == _context) {
        return false;
    }
    redisReply* reply =
        (redisReply*)redisCommand(_context, "HSET %s %s %b", key.c_str(), field.c_str(), data.c_str(), data.size());
    bool ret = Check(reply);
    freeReplyObject(reply);
    return ret;
}

bool CHiredisBase::GetNormalString(std::string& key, std::string& data)
{
    LS_PRINT("GET %s ", key.c_str());
    if(NULL == _context) {
        return false;
    }
    redisReply* reply = (redisReply*)redisCommand(_context, "GET %s", key.c_str());
    bool ret = Check(reply);
    if(ret && REDIS_REPLY_STRING == reply->type) {
        data.assign(reply->str, reply->len);
    }
    freeReplyObject(reply);
    return ret;
}

bool CHiredisBase::GetList(std::string& key, VecString& vecData)
{
    if(NULL == _context) {
        return false;
    }
    redisReply* reply = (redisReply*)redisCommand(_context, "LRANGE %s %d %d", key.c_str(), 0, -1);
    bool ret = Check(reply);
    if(ret && reply->elements > 0) {
        vecData.resize(reply->elements);
        for(int j = 0; j < reply->elements; j++) {
            LS_PRINT("%u) %s", j, reply->element[j]->str);
            vecData[j] = reply->element[j]->str;
        }
    }
    freeReplyObject(reply);
    return ret;
}

bool CHiredisBase::SetNormalString(std::string& key, std::string& data)
{
    LS_PRINT("SET %s sz %d %s", key.c_str(), data.size(), data.c_str());
    if(NULL == _context) {
        return false;
    }
    redisReply* reply = (redisReply*)redisCommand(_context, "SET %s %b", key.c_str(), data.c_str(), data.size());
    bool ret = Check(reply);

    freeReplyObject(reply);
    return ret;
}
bool CHiredisBase::AddListData(std::string& key, std::string& data)
{
    LS_PRINT("RPUSH %s %s", key.c_str(), data.c_str());
    if(NULL == _context) {
        return false;
    }
    redisReply* reply = (redisReply*)redisCommand(_context, "RPUSH %s %s", key.c_str(), data.c_str());
    bool ret = Check(reply);
    freeReplyObject(reply);
    return true;
}
bool CHiredisBase::PopList(std::string& key)
{
    LS_PRINT("RPOP %s", key.c_str());
    if(NULL == _context) {
        return false;
    }
    redisReply* reply = (redisReply*)redisCommand(_context, "RPOP %s", key.c_str());
    bool ret = Check(reply);

    freeReplyObject(reply);
    return true;
}

bool CHiredisBase::LtrimList(std::string& key, int start, int stop)
{
    LS_PRINT("LTRIM %s %d %d", key.c_str(), start, stop);
    if(NULL == _context) {
        return false;
    }
    redisReply* reply = (redisReply*)redisCommand(_context, "LTRIM %s %d %d", key.c_str(), start, stop);
    bool ret = Check(reply);

    freeReplyObject(reply);
    return true;
}

bool CHiredisBase::DelKey(std::string& key)
{
    if(NULL == _context) {
        return false;
    }
    redisReply* reply = (redisReply*)redisCommand(_context, "DEL %s", key.c_str());
    bool ret = Check(reply);
    freeReplyObject(reply);
    return ret;
}

bool CHiredisBase::Set(const char* pKey, const char* pValue, time_t timeout, LsUInt32 flag)
{
    if(NULL == _context) {
        return false;
    }
    redisReply* reply = (redisReply*)redisCommand(_context, "SETEX %s %d %s", pKey, timeout, pValue);
    bool ret = Check(reply);
    freeReplyObject(reply);
    return ret;
}

bool CHiredisBase::GetHash(std::string& key, std::string& field, std::string& data)
{
    LS_PRINT("hget %s", key.c_str());
    if(NULL == _context) {
        return false;
    }
    redisReply* reply = (redisReply*)redisCommand(_context, "hget %s %s", key.c_str(), field.c_str());
    bool ret = Check(reply);
    if(ret && REDIS_REPLY_STRING == reply->type) {
        data.assign(reply->str, reply->len);
    }
    freeReplyObject(reply);
    return ret;
}

bool CHiredisBase::AddZSet(std::string& key, int score, std::string& data)
{
    LS_PRINT("ZADD %s %d %s ", key.c_str(), score, data.c_str());
    if(NULL == _context) {
        return false;
    }
    redisReply* reply = (redisReply*)redisCommand(_context, "ZADD %s %d %s ", key.c_str(), score, data.c_str());
    bool ret = Check(reply);
    freeReplyObject(reply);
    return ret;
}

bool CHiredisBase::DelZSet(std::string& key, int start, int end)
{
    LS_PRINT("ZREMRANGEBYRANK %s %d %d ", key.c_str(), start, end);
    if(NULL == _context) {
        return false;
    }
    redisReply* reply = (redisReply*)redisCommand(_context, "ZREMRANGEBYRANK %s %d %d ", key.c_str(), start, end);
    bool ret = Check(reply);
    freeReplyObject(reply);
    return ret;
}

bool CHiredisBase::ZremZSet(std::string& key, std::string& data)
{
    LS_PRINT("ZREM %s %s ", key.c_str(), data.c_str());
    if(NULL == _context) {
        return false;
    }
    redisReply* reply = (redisReply*)redisCommand(_context, "ZREM %s %s ", key.c_str(), data.c_str());
    bool ret = Check(reply);
    freeReplyObject(reply);
    return ret;
}

bool CHiredisBase::GetZSet(std::string& key, VecString& vecData, int start, int end)
{
    LS_PRINT("ZREVRANGE %s %d %d", key.c_str(), start, end);
    if(NULL == _context) {
        return false;
    }
    redisReply* reply = (redisReply*)redisCommand(_context, "ZREVRANGE %s %d %d", key.c_str(), start, end);
    bool ret = Check(reply);
    if(ret && reply->elements > 0) {
        vecData.resize(reply->elements);
        for(int j = 0; j < reply->elements; j++) {
            LS_PRINT("%u) %s", j, reply->element[j]->str);
            vecData[j] = reply->element[j]->str;
        }
    }
    freeReplyObject(reply);
    return ret;
}

bool CHiredisBase::GetZSetWithScores(std::string& key, VecString& vecData, int start, int end)
{
    LS_PRINT("ZREVRANGE %s %d %d WITHSCORES", key.c_str(), start, end);
    if(NULL == _context) {
        return false;
    }
    redisReply* reply = (redisReply*)redisCommand(_context, "ZREVRANGE %s %d %d WITHSCORES", key.c_str(), start, end);
    bool ret = Check(reply);
    if(ret && reply->elements > 0) {
        vecData.resize(reply->elements);
        for(int j = 0; j < reply->elements; j++) {
            vecData[j] = reply->element[j]->str;
        }
    }
    freeReplyObject(reply);
    return ret;
}
bool CHiredisBase::SaveScript(const char* lua_code, std::string& hash_code)
{
    LS_PRINT("save code \n%s", lua_code);
    if(NULL == _context) {
        return false;
    }
    redisReply* reply = (redisReply*)redisCommand(_context, "SCRIPT LOAD %s", lua_code);
    bool ret = Check(reply);
    if(ret && REDIS_REPLY_STRING == reply->type) {
        hash_code.assign(reply->str, reply->len);
    }
    freeReplyObject(reply);
    return ret;
}

/////////////////////////////////////////////////////////
CHiredisReply::CHiredisReply(redisReply* reply, bool freeReply)
    : _reply(reply)
    ,_freeReply(freeReply)
{
}
CHiredisReply::CHiredisReply(redisReply* reply):CHiredisReply(reply, true)
{
}

CHiredisReply::~CHiredisReply()
{
    if(_freeReply && _reply) {
        freeReplyObject(_reply);
    }
}

int CHiredisReply::ReplyType()
{
    if(_reply)
        return _reply->type;
    return -1;
}

bool CHiredisReply::CheckIdx(int idx)
{
    bool ret = false;
    do {
        if(NULL == _reply)
            break;

        if(REDIS_REPLY_ARRAY != _reply->type)
            break;

        if(idx < 0 || idx >= _reply->elements)
            break;

        ret = true;
    } while(false);
    return ret;
}
bool CHiredisReply::GetFloat(double& value, redisReply* r)
{
    if(NULL == r)
        return false;

    bool ret = false;
    switch(r->type) {
    case REDIS_REPLY_INTEGER:
        ret = true;
        value = r->integer;
        break;
    case REDIS_REPLY_STRING:
        ret = true;
        value = atof(r->str);
        break;
        /*
    case REDIS_REPLY_ARRAY:
    case REDIS_REPLY_ERROR:
    case REDIS_REPLY_STATUS:
 */
    }
    return ret;
}

bool CHiredisReply::GetIntValue(int& value, redisReply* r)
{
    if(NULL == r)
        return false;

    bool ret = false;
    switch(r->type) {
    case REDIS_REPLY_INTEGER:
        ret = true;
        value = r->integer;
        break;
    case REDIS_REPLY_STRING:
        ret = true;
        value = atoi(r->str);
        break;
        /*
    case REDIS_REPLY_ARRAY:
    case REDIS_REPLY_ERROR:
    case REDIS_REPLY_STATUS:
 */
    }
    return ret;
}
bool CHiredisReply::GetInt64Value(LsInt64& value, redisReply* r)
{
    if(NULL == r)
        return false;

    bool ret = false;
    switch(r->type) {
    case REDIS_REPLY_INTEGER:
        ret = true;
        value = r->integer;
        break;
    case REDIS_REPLY_STRING:
        ret = true;
        value = atol(r->str);
        break;
        /*
    case REDIS_REPLY_ARRAY:
    case REDIS_REPLY_ERROR:
    case REDIS_REPLY_STATUS:
 */
    }
    return ret;
}

bool CHiredisReply::GetString(std::string& value, redisReply* r)
{
    if(NULL == r)
        return false;

    bool ret = true;
    switch(r->type) {
    case REDIS_REPLY_INTEGER:
        char buf[32];
        sprintf(buf, "%d", r->integer);
        value = buf;
        break;
    case REDIS_REPLY_ERROR:
    case REDIS_REPLY_STRING:
        value = r->str;
        break;
    case REDIS_REPLY_ARRAY:
    case REDIS_REPLY_STATUS:
        ret = false;
        // value =   r->str ;
        break;
    }
    return ret;
}
bool CHiredisReply::GetByteString(std::string& value, redisReply* r)
{
    if(NULL == r)
        return false;

    bool ret = true;
    switch(r->type) {
    case REDIS_REPLY_INTEGER:
        char buf[32];
        sprintf(buf, "%d", r->integer);
        value = buf;
        break;
    case REDIS_REPLY_ERROR:
    case REDIS_REPLY_STRING:
        value = value.assign(r->str, r->len);
        break;
    case REDIS_REPLY_ARRAY:
    case REDIS_REPLY_STATUS:
        ret = false;
        // value =   r->str ;
        break;
    }
    return ret;
}
bool CHiredisReply::GetValue(LsInt16& value)
{
    int temp;
    bool ret = GetIntValue(temp, _reply);
    if(ret)
        value = temp;
    return ret;
}

bool CHiredisReply::GetValue(LsInt32& value)
{
    return CHiredisReply::GetIntValue(value, _reply);
}
bool CHiredisReply::GetValue(LsInt64& value)
{
    return CHiredisReply::GetInt64Value(value, _reply);
}

bool CHiredisReply::GetValue(LsInt8& value)
{
    int temp;
    bool ret = GetIntValue(temp, _reply);
    if(ret)
        value = temp;
    return ret;
}

bool CHiredisReply::GetValue(double& value)
{
    return CHiredisReply::GetFloat(value, _reply);
}

bool CHiredisReply::GetValue(float& value)
{
    double temp;
    bool ret = GetFloat(temp, _reply);
    if(ret)
        value = temp;
    return ret;
}

bool CHiredisReply::GetValue(std::string& value)
{
    return CHiredisReply::GetString(value, _reply);
}

bool CHiredisReply::GetValueInArray(LsInt16& value, int idx)
{
    int temp;
    if(!this->CheckIdx(idx))
        return false;
    bool ret = CHiredisReply::GetIntValue(temp, _reply->element[idx]);
    if(ret)
        value = temp;
    return ret;
}
bool CHiredisReply::GetValueInArray(LsInt32& value, int idx)
{
    if(!this->CheckIdx(idx))
        return false;
    return CHiredisReply::GetIntValue(value, _reply->element[idx]);
}
bool CHiredisReply::GetValueInArray(LsInt64& value, int idx)
{
    if(!this->CheckIdx(idx))
        return false;
    return CHiredisReply::GetInt64Value(value, _reply->element[idx]);
}

bool CHiredisReply::GetValueInArray(LsInt8& value, int idx)
{
    int temp;
    if(!this->CheckIdx(idx))
        return false;
    bool ret = CHiredisReply::GetIntValue(temp, _reply->element[idx]);
    if(ret)
        value = temp;
    return ret;
}

bool CHiredisReply::GetValueInArray(double& value, int idx)
{
    if(!this->CheckIdx(idx))
        return false;
    return CHiredisReply::GetFloat(value, _reply->element[idx]);
}

bool CHiredisReply::GetValueInArray(float& value, int idx)
{
    double temp;
    if(!this->CheckIdx(idx))
        return false;
    bool ret = CHiredisReply::GetFloat(temp, _reply->element[idx]);
    if(ret)
        value = temp;
    return ret;
}

bool CHiredisReply::GetValueInArray(std::string& value, int idx)
{
    if(!this->CheckIdx(idx))
        return false;

    return CHiredisReply::GetString(value, _reply->element[idx]);
}

bool CHiredisReply::IsArray(int& sz)
{
    sz = 0;
    bool ret = false;
    do {
        if(NULL == _reply)
            break;

        if(REDIS_REPLY_ARRAY != _reply->type)
            break;

        sz = _reply->elements;

        ret = true;
    } while(false);
    return ret;
}

bool CHiredisReply::GetByteValue(std::string& value)
{
    return CHiredisReply::GetByteString(value, _reply);
}
void CHiredisReply::Print()
{
    if(this->_reply) {
        PrintReply(this->_reply);
    } else {
        SYS_ERR("NO REPLY");
    }
}

void PrintReply(redisReply* cur)
{
    switch(cur->type) {
    case REDIS_REPLY_STRING:
        SYS_ERR("type %d %s", cur->type, cur->str);
        break;
    case REDIS_REPLY_INTEGER:
        SYS_ERR("type %d %d", cur->type, cur->integer);
        break;
    case REDIS_REPLY_ARRAY:
        SYS_ERR("array type elements: %d", cur->elements);
        for(int i = 0; i < cur->elements; i++) {
            redisReply* c = cur->element[i];
            SYS_ERR("array[%d]: ", i);
            PrintReply(c);
        }
        SYS_ERR("array end");
        break;
    case REDIS_REPLY_NIL:
        SYS_ERR("return nill");
        break;
    case REDIS_REPLY_STATUS:
        SYS_ERR("status %s", cur->str);
        break;
    default:
        SYS_ERR("return type %d", cur->type);
        break;
    }
}
///////////////////////////////////////////////////////////////////
SharePrtReply BlockRedisCmmd::redisCommand(const char* format, ...)
{
    va_list ap;
    va_start(ap, format);
    redisReply* reply = (redisReply*)redisvCommand(_context, format, ap);
    va_end(ap);
    return std::make_shared<CHiredisReply>(reply);
}

//////////////////////////////////////////////////////////////
int PipelineRedisCmmd::redisAppendCommand(const char* format, ...)
{
    if(NULL == _context)
        return REPLY_ERR_CONTEXT_NULL;
    va_list ap;
    int ret;

    va_start(ap, format);
    ret = redisvAppendCommand(_context, format, ap);
    va_end(ap);
    if(0 == REDIS_OK) {
        _appandTimes++;
    }
    return ret;
}

SharePrtReply PipelineRedisCmmd::RedisGetReply()
{
    redisReply* reply = NULL;
    if(_appandTimes - _getTimes > 0) {
        int ret = redisGetReply(_context, (void**)(&reply));
        if(0 == ret) {
            _getTimes++;
        }
    }
    return std::make_shared<CHiredisReply>(reply);
}

PipelineRedisCmmd::~PipelineRedisCmmd()
{
    this->Reset();
}

void PipelineRedisCmmd::Reset()
{
    int left = _appandTimes - _getTimes;
    redisReply* reply = NULL;
    for(int i = 0; i < left; i++) {
        redisGetReply(_context, (void**)(&reply));
        _getTimes++;
        if(_reply) {
            freeReplyObject(reply);
        }
    }
}
