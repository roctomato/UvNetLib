#ifndef CHIREDISBASE_H
#define CHIREDISBASE_H

#include <memory>
#include <stdlib.h>
#include <string>
#include <vector>

#include "hiredis.h"
#include "z_typedef.h"

typedef std::vector<std::string> VecString;

void PrintReply(redisReply* C);

class CHiredisReply
{
public:
    explicit CHiredisReply(redisReply* reply);
    explicit CHiredisReply(redisReply* reply, bool freeReply);

    CHiredisReply(const CHiredisReply&) = delete;
    CHiredisReply& operator=(CHiredisReply&) = delete;
    CHiredisReply(CHiredisReply&&) = delete;
    CHiredisReply& operator=(CHiredisReply&&) = delete;

    ~CHiredisReply();

    int ReplyType();
    void Print();

    bool IsArray(int& sz);

    bool GetValue(std::string& value);
    bool GetValue(LsInt64& value);
    bool GetValue(LsInt32& value);
    bool GetValue(LsInt16& value);
    bool GetValue(LsInt8& value);
    bool GetValue(double& value);
    bool GetValue(float& value);
    bool GetByteValue(std::string& value);

    bool GetValueInArray(std::string& value, int idx);
    bool GetValueInArray(LsInt64& value, int idx);
    bool GetValueInArray(LsInt32& value, int idx);
    bool GetValueInArray(LsInt16& value, int idx);
    bool GetValueInArray(LsInt8& value, int idx);
    bool GetValueInArray(double& value, int idx);
    bool GetValueInArray(float& value, int idx);

    static bool GetString(std::string& value, redisReply* r);
    static bool GetIntValue(int& value, redisReply* r);
    static bool GetFloat(double& value, redisReply* r);
    static bool GetInt64Value(LsInt64& value, redisReply* r);
    static bool GetByteString(std::string& value, redisReply* r);

protected:
    bool CheckIdx(int idx);
    redisReply* _reply;
    bool        _freeReply;
};

typedef std::shared_ptr<CHiredisReply> SharePrtReply;

class CHiredisBase
{
    friend class CHiredisCommandBase;
    friend class PipelineRedisCmmd;
public:
    CHiredisBase();
    ~CHiredisBase();

    bool Connect(const char* ip, unsigned short port, int index, const char* password);
    void Close();
    bool SetHash(std::string& key, std::string& field, std::string& data);
    bool DelHash(std::string& key, std::string& field);
    bool GetAllHash(std::string& key, VecString& vecData);
    bool GetAllHashValue(std::string& key, VecString& vecData);
    bool GetHash(std::string& key, std::string& field, std::string& data);

    bool AddSet(std::string& key, std::string& data);
    bool DelSet(std::string& key, std::string& data);
    bool GetAllSet(std::string& key, VecString& vecData);

    bool GetNormalString(std::string& key, std::string& data);
    bool SetNormalString(std::string& key, std::string& data);
    bool DelKey(std::string& key);
    bool Set(const char* pKey, const char* pValue, time_t timeout, LsUInt32 flag = 0);

    bool AddZSet(std::string& key, int score, std::string& data);
    bool DelZSet(std::string& key, int start, int end);
    bool ZremZSet(std::string& key, std::string& data);
    bool GetZSet(std::string& key, VecString& vecData, int start, int end);
    bool GetZSetWithScores(std::string& key, VecString& vecData, int start, int end);

    bool GetList(std::string& key, VecString& vecData);
    bool AddListData(std::string& key, std::string& data);
    bool PopList(std::string& key);
    bool LtrimList(std::string& key, int start, int stop);
    bool SaveScript(const char* lua_code, std::string& hash_code);

    bool ClearAllData(std::string& key);

protected:
    bool Check(redisReply* reply);
    redisContext* _context;
    bool Connect();

    std::string _ip;
    LsUInt16 _port;
    std::string _data;
    int _index;
    std::string _password;
};

class CHiredisCommandBase
{
public:
    CHiredisCommandBase(redisContext* context)
        : _context(context)
    {
    }
    CHiredisCommandBase(CHiredisBase& cct)
        : CHiredisCommandBase(cct._context)
    {
    }

protected:
    redisContext* _context;
};

class BlockRedisCmmd : public CHiredisCommandBase
{
public:
    using CHiredisCommandBase::CHiredisCommandBase;

    SharePrtReply redisCommand(const char* format, ...);
};

class PipelineRedisCmmd : public CHiredisCommandBase
{
public:
    enum {
        REPLY_ERR_NONE =0,
        REPLY_ERR_CONTEXT_NULL=1000,
    };
    
    PipelineRedisCmmd(redisContext* context)
        : CHiredisCommandBase(context)
        , _reply(NULL)
        ,_appandTimes(0)
        ,_getTimes(0)
    {
        
    }
    
    PipelineRedisCmmd(CHiredisBase& cct)
        : PipelineRedisCmmd(cct._context)
    {
    }
    
    ~PipelineRedisCmmd();
    void Reset();
    
    int redisAppendCommand(const char* format, ...);
    SharePrtReply RedisGetReply();
private:
    redisReply* _reply;
    int _appandTimes;
    int _getTimes;
};



#endif // CHIREDISBASE_H
