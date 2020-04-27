#ifndef UJsonNode_H
#define UJsonNode_H

#include "ujson.hpp"
#include "z_typedef.h"

class UJsonNode
{
public:
	enum NodeType{
		NodeType_UnKnown,
		NodeType_Array,
		NodeType_Object,
	};
	UJsonNode();
    UJsonNode(UJsonNode&& uj);
    UJsonNode(const UJsonNode& uj);
	UJsonNode(bool isArray);
	UJsonNode( const std::string& str );
	UJsonNode(ujson::array&  array );
	UJsonNode(ujson::object&  object );
	UJsonNode(const ujson::value& value );

	~UJsonNode();
	
	// as object
	bool push_back(const char* key, UJsonNode& value );
	template<typename T>bool push_back(const char* key, const T& value )
	{
		ujson::value v(value);
		return push_back(key, v );
	}
	
	bool push_back(const char* key, const LsUInt64& value )
	{
		LsInt64 v1 = value;
		ujson::value v(v1);
		return push_back(key, v );
	}
	// as array
	bool push_back( UJsonNode& value );
	template<typename T>bool push_back( const T& value )
	{
		ujson::value v(value);
		return push_back(v );
	}
	
	ujson::value ToValue( ) const;
	void ToValue(ujson::value& value);
	void ToString(std::string& str , bool format=false);
	
	const ujson::object* GetObj() const { return this->_pObj; }
	const ujson::array*  GetArray() const { return this->_pArray; }
	
	bool IsArray() const  { return _nodeType == NodeType_Array; };
	bool IsObject() const { return _nodeType == NodeType_Object; };
	NodeType GetNodeType() const { return  _nodeType; }
	
private:	
	bool InitType( bool isArray);
	bool InitFromValue(const ujson::value& value );
	bool push_back( const char* key, const ujson::value& value );
	bool push_back( const ujson::value& value );
	
	NodeType  _nodeType;
	bool  _delObj;
	
	ujson::array * _pArray;
	ujson::object* _pObj;
	ujson::value*  _pValue;
	
};

ujson::value to_json(UJsonNode const &e); 

//////////////////////////////////////////////////
class UJ_Iterator
{
public:
	UJ_Iterator( const UJsonNode& node);
	
	const ujson::value& GetCurValue();
	
	LsInt32      GetInt32();
	LsUInt32     GetUInt32();
	LsInt8       GetInt8();
	LsUInt8      GetUInt8();
	LsInt16      GetInt16();
	LsUInt16     GetUInt16();
	LsInt64      GetInt64();
	LsUInt64     GetUInt64();
    double       GetDouble();
	float        GetFloat();
	bool         GetBool();
	std::string  GetString();
	
	const char * GetCurKey();
	
	bool end();
	
	UJ_Iterator& operator ++ ();
	UJ_Iterator& operator ++ (int);
	
private:
	bool IsArray() const  { return _nodeType == UJsonNode::NodeType_Array; };
	bool IsObject() const { return _nodeType == UJsonNode::NodeType_Object; };
	void MoveNext();
	
	
	const ujson::array * 			 _pArray;
	ujson::array::const_iterator     _arrayIt;
	
	ujson::object::const_iterator    _objIt;
	const ujson::object* 			 _pObj;
	
	UJsonNode::NodeType  _nodeType;
};

template<typename T>
void WriteToJsonStr( const T& s,  std::string& str, bool bFormat)
{
	UJsonNode n;
	WriteToJson( s, n );	
	n.ToString(str, bFormat);
}

template<typename T>
void ReadFromJsonStr( T& s,  std::string& str)
{
	UJsonNode n( str );
	ReadFromJson( s, n );
}
#endif // UJsonNode_H
