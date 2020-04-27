#include "chttpparser.h"
#include "zby_debug.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int My_on_message_begin(http_parser* parser)
{
	CHttpParser* p = (CHttpParser*)( parser->data );
	if ( p ) {
		p->on_message_begin( );
	}
	return 0;
}
int My_on_headers_complete(http_parser* parser)
{
	CHttpParser* p = (CHttpParser*)( parser->data );
	if ( p ) {
		p->on_headers_complete( );
	}
	return 0;
}
int My_on_message_complete(http_parser* parser)
{
	CHttpParser* p = (CHttpParser*)( parser->data );
	if ( p ) {
		p->on_message_complete( );
	}
	return 0;
}
int My_on_chunk_header(http_parser* parser)
{
	CHttpParser* p = (CHttpParser*)( parser->data );
	if ( p ) {
		p->on_chunk_header( );
	}
	return 0;
}
int My_on_chunk_complete(http_parser* parser)
{
	CHttpParser* p = (CHttpParser*)( parser->data );
	if ( p ) {
		p->on_chunk_complete( );
	}
	return 0;
}

int My_on_url(http_parser* parser , const char *at, size_t len)
{
	CHttpParser* p = (CHttpParser*)( parser->data );
	if ( p ) {
		p->on_url( at, len);
	}
	return 0;
}
int My_on_status(http_parser* parser , const char *at, size_t len)
{
	CHttpParser* p = (CHttpParser*)( parser->data );
	if ( p ) {
		p->on_status( at, len);
	}
	return 0;
}
int My_on_header_field(http_parser* parser , const char *at, size_t len)
{
	CHttpParser* p = (CHttpParser*)( parser->data );
	if ( p ) {
		p->on_header_field( at, len);
	}
	return 0;
}
int My_on_header_value(http_parser* parser , const char *at, size_t len)
{
	CHttpParser* p = (CHttpParser*)( parser->data );
	if ( p ) {
		p->on_header_value( at, len);
	}
	return 0;
}
int My_on_body(http_parser* parser , const char *at, size_t len)
{
	CHttpParser* p = (CHttpParser*)( parser->data );
	if ( p ) {
		p->on_body( at, len);
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CHttpParser::CHttpParser(enum http_parser_type type  )
{
	http_parser_init( &this->_parser, type );
	this->_parser.data = this;

	this->_settings.on_body = My_on_body;
	this->_settings.on_chunk_complete = My_on_chunk_complete;
	this->_settings.on_chunk_header = My_on_chunk_header;
	this->_settings.on_header_field= My_on_header_field;
	this->_settings.on_header_value = My_on_header_value;
	this->_settings.on_headers_complete= My_on_headers_complete;
	this->_settings.on_message_begin = My_on_message_begin;
	this->_settings.on_message_complete= My_on_message_complete;
	this->_settings.on_status = My_on_status;
	this->_settings.on_url    = My_on_url;
}

CHttpParser::~CHttpParser()
{
}

int CHttpParser::on_body(const char* at, size_t length)
{
	//ZPRINT("%s", at );
	this->_body.assign( at, length );
	return 0;
}

int CHttpParser::on_chunk_complete()
{
	//ZPRINT("on_chunk_complete");
	return 0;
}

int CHttpParser::on_chunk_header()
{
	//ZPRINT("on_chunk_header");
	return 0;
}

int CHttpParser::on_header_field(const char* at, size_t length)
{
	//ZPRINT("on_header_field");
	this->_curHeaderField.assign( at, length);
	return 0;
}

int CHttpParser::on_header_value(const char* at, size_t length)
{
	//ZPRINT("on_header_value");
	this->_headerMap[ this->_curHeaderField].assign( at, length);
	return 0;
}

int CHttpParser::on_headers_complete()
{
/*
	HeaderMap::iterator it;
	for( it = this->_headerMap.begin(); it != this->_headerMap.end(); it ++ ) {
		ZPRINT("fd:%s value:%s", (it->first).c_str(),(it->second).c_str()) ;
	}
*/	
	return 0;
}

int CHttpParser::on_message_begin()
{
	//ZPRINT("on_message_begin");
	_b_message_complete = false;
	return 0;
}

int CHttpParser::on_message_complete()
{
	/*
	ZPRINT("url %s", this->_url.c_str() );
	ZPRINT("body %s", this->_body.c_str() );
	ZPRINT("query %s", this->_urlQuery.c_str() );*/
	_b_message_complete = true;
	this->ParseReqParam();
	return 0;
}

int CHttpParser::on_status(const char* at, size_t length)
{
	//ZPRINT("on_status");
	return 0;
}

int CHttpParser::on_url(const char* at, size_t length)
{
	struct http_parser_url u;
	http_parser_url_init(&u);
	http_parser_parse_url( at, length, 0, &u );
	this->_url.assign( at + u.field_data[UF_PATH].off, u.field_data[UF_PATH].len );
	this->_urlQuery.assign(  at + u.field_data[UF_QUERY].off, u.field_data[UF_QUERY].len );
	//ZPRINT("on_url");
	return 0;
}
int CHttpParser::Parse_Execute(const char* buf, size_t recved)
{
	/* Start up / continue the parser.
	 * Note we pass recved==0 to signal that EOF has been received.
	 */
	size_t nparsed = http_parser_execute(&this->_parser, &this->_settings, buf, recved);
	//ZPRINT("recv %d parsed %d", recved, nparsed );
	if ( _parser.upgrade) {
		/* handle new protocol */
	} else if (nparsed != recved) {
		/* Handle error. Usually just close the connection. */
	}
	return nparsed;
}

std::string CHttpParser::GetHeader(const char* fd)
{
	HeaderMap::iterator it = this->_headerMap.find( fd );
	if ( it != this->_headerMap.end() ){
		return it->second;
	}
	return "";
}
std::string CHttpParser::GetReqParam()
{
	if ( this->GetMethod() == 3 )//post
	{
		return this->_body;
	}
	return this->_urlQuery;
}
bool CHttpParser::Parse_ExecuteEx(const char* buf, size_t length)
{
	this->Parse_Execute( buf, length);
	return _b_message_complete;
}
void CHttpParser::ParseReqParam()
{
	std::stringstream query_ss(_urlQuery);
    //ZPRINT("start parse_query_url:%s", _urlQuery.c_str());

    while(query_ss.good()) {
        std::string key_value;
        std::getline(query_ss, key_value, '&');
        //ZPRINT("get key_value:%s", key_value.c_str());

        std::stringstream key_value_ss(key_value);
        while(key_value_ss.good()) {
            std::string key, value;
            std::getline(key_value_ss, key, '=');
            std::getline(key_value_ss, value, '=');
            //_params.insert(std::pair<std::string, std::string>(key, value));
			//ZPRINT("get key %s, value:%s", key.c_str(), value.c_str() );
			this->_paramMap[key]= value;
        }
    }
}
const char* CHttpParser::GetParam(const char* fd)
{
	ParamMap::iterator it = this->_paramMap.find( fd );
	if ( it != this->_paramMap.end() ){
		return it->second.c_str();
	}
	return NULL;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Response::Response(CodeMsg status_code) {
    this->_code_msg = status_code;
    this->_is_writed = 0;
}

void Response::set_head(const std::string& name, const std::string &value) {
    this->_headers[name] = value;
}
/*
void Response::set_body(Json::Value &body) {
    Json::FastWriter writer;
    std::string str_value = writer.write(body);
    this->_body = str_value;
}
*/
int Response::gen_response(std::string &http_version, bool is_keepalive) {
    //ZPRINT("START gen_response code:%d, msg:%s", _code_msg.status_code, _code_msg.msg.c_str());
    _res_bytes << http_version << " " << _code_msg.status_code << " " << _code_msg.msg << "\r\n";
    _res_bytes << "Server: zhttp/1.0.0"  << "\r\n";
    if (_headers.find("Content-Type") == _headers.end()) {
        _res_bytes << "Content-Type: application/json; charset=UTF-8" << "\r\n";
    }
    _res_bytes << "Content-Length: " << _body.size() << "\r\n";

    std::string con_status = "Connection: close";
    if(is_keepalive) {
        con_status = "Connection: Keep-Alive";
    }
    _res_bytes << con_status << "\r\n";

    for (std::map<std::string, std::string>::iterator it = _headers.begin(); it != _headers.end(); ++it) {
        _res_bytes << it->first << ": " << it->second << "\r\n";
    }
    // header end
    _res_bytes << "\r\n";
    _res_bytes << _body;

    //ZPRINT("gen response context:%s", _res_bytes.str().c_str());
    return 0;
}

int Response::readsome(char *buffer, int buffer_size, int &read_size) {
    _res_bytes.read(buffer, buffer_size);
    read_size = _res_bytes.gcount();

    if (!_res_bytes.eof()) {
        return 1;
    }
    return 0;
}

int Response::rollback(int num) {
    if (_res_bytes.eof()) {
        _res_bytes.clear();
    }
    int rb_pos = (int) _res_bytes.tellg() - num;
    _res_bytes.seekg(rb_pos);
    return _res_bytes.good() ? 0 : -1;
}
void Response::set_body(std::string& value)
{
	this->_body = value;
}
void Response::SetBody(const char* value)
{
	this->_body = value;
}
