#ifndef CHTTPPARSER_H
#define CHTTPPARSER_H

#include <map>
#include <string>
#include <sstream>

#include "http_parser.h"

struct CodeMsg {
	int status_code;
	std::string msg;
};

const static CodeMsg STATUS_OK = {200, "OK"};
const static CodeMsg STATUS_NOT_FOUND = {404, "Not Found"};
const static CodeMsg STATUS_METHOD_NOT_ALLOWED = {405, "Method Not Allowed"};
const static CodeMsg STATUS_LENGTH_REQUIRED = {411, "Length Required"};

const static int PARSE_REQ_LINE = 0;
const static int PARSE_REQ_HEAD = 1;
const static int PARSE_REQ_BODY = 2;
const static int PARSE_REQ_OVER = 3;
const static int PARSE_REQ_HEAD_OVER = 4;

const static int NEED_MORE_STATUS = 1;
const static int PARSE_LEN_REQUIRED = 2;

typedef std::map<std::string,std::string> HeaderMap;
typedef std::map<std::string,std::string> ParamMap;
class CHttpParser
{
public:
	CHttpParser( enum http_parser_type  type = HTTP_REQUEST);
	~CHttpParser();

	bool Parse_ExecuteEx( const char *buf, size_t length );
	int Parse_Execute( const char *buf, size_t length );

	virtual int on_url( const char *at, size_t length);
	virtual int on_status( const char *at, size_t length);
	virtual int on_header_field( const char *at, size_t length);
	virtual int on_header_value( const char *at, size_t length);
	virtual int on_body( const char *at, size_t length);


	virtual int on_message_begin ( );
	virtual int on_headers_complete ( );
	virtual int on_message_complete ( );
	virtual int on_chunk_header ( );
	virtual int on_chunk_complete ( );

	std::string GetHeader(const char* fd );
	const char* GetParam(const char* fd );

	std::string GetReqParam();
	void ParseReqParam();

	unsigned int GetMethod() {
		return this->_parser.method;
	}



	const std::string& GetBody() const {
		return _body;
	}

	const std::string& GetUrl() const {
		return _url;
	}

	const std::string& GetUrlQuery() const {
		return _urlQuery;
	}
	void SetBody(const std::string& _body) {
		this->_body = _body;
	}
	void SetUrl(const std::string& _url) {
		this->_url = _url;
	}
	
protected:
	HeaderMap		_headerMap;
	std::string 	_url;
	
	std::string 	_body;
	std::string		_urlQuery;
	ParamMap		_paramMap;

private:
	std::string 		  _curHeaderField;
	http_parser			  _parser;
	http_parser_settings  _settings;
	bool                  _b_message_complete;
};

class Response
{
public:
	Response(CodeMsg status_code = STATUS_OK);
	//Response(CodeMsg status_code, Json::Value &body);

	void set_head(const std::string& name, const std::string &value);

	void set_body( std::string &value );
	void  SetBody(const char* data );

	// void set_body(Json::Value &body);

	int gen_response(std::string &http_version, bool is_keepalive);

	/**
	 * return 0: read part, 1: read over, -1:read error
	 */
	int readsome(char *buffer, int buffer_size, int &read_size);

	/**
	 * rollback num bytes in response bytes
	 */
	int rollback(int num);

	std::string str() {
		return _res_bytes.str();
	}

	bool _is_writed;
	CodeMsg _code_msg;
	std::string _body;
private:
	std::map<std::string, std::string> _headers;
	std::stringstream _res_bytes;
};
#endif // CHTTPPARSER_H
