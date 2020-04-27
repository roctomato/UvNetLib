#include "u_json_node.h"
#include "zby_debug.h"


ujson::value to_json(UJsonNode const &e)
{
	return e.ToValue();
}
///////////////////////////////////////////////

UJsonNode::UJsonNode()
	:_nodeType(NodeType_UnKnown)
	,_delObj( false )
	,_pArray( NULL)
	,_pObj( NULL )
	,_pValue(NULL)
{
}

UJsonNode::UJsonNode(bool isArray)
	:_nodeType(NodeType_UnKnown)
	,_delObj( false )
	,_pArray( NULL)
	,_pObj( NULL )
	,_pValue(NULL)
{
	this->InitType( isArray );
}
UJsonNode::UJsonNode(ujson::array& array)
	:_nodeType(NodeType_UnKnown)
	,_delObj( false )
	,_pArray( &array)
	,_pObj( NULL )
	,_pValue(NULL)
{
	_nodeType = NodeType_Array;
}

UJsonNode::UJsonNode(ujson::object& object)
	:_delObj( false )
	,_pArray( NULL)
	,_pObj( &object )
	,_pValue(NULL)
{
	_nodeType = NodeType_Object;
}

UJsonNode::UJsonNode(const std::string& str)
	:_nodeType(NodeType_UnKnown)
	,_delObj( false )
	,_pArray( NULL)
	,_pObj( NULL )
	,_pValue(NULL)
{
	_pValue = new ujson::value(ujson::parse(str));
	InitFromValue( *_pValue);
}

UJsonNode::UJsonNode(const ujson::value& value)
	:_nodeType(NodeType_UnKnown)
	,_delObj( false )
	,_pArray( NULL)
	,_pObj( NULL )
	,_pValue(NULL)
{
	InitFromValue( value );
}


UJsonNode::~UJsonNode()
{
	if ( _delObj ) {
		if ( this->IsArray() ) {
			delete _pArray;
		} else {
			delete _pObj;
		}
	}
	if ( _pValue ) {
		delete _pValue;
	}
}

ujson::value UJsonNode::ToValue() const
{
	if ( this->IsArray() ) {
		return  ujson::value (*_pArray);
	}

	if ( this->IsObject() )
		return ujson::value(  *_pObj );
	return ujson::value ();
}
bool UJsonNode::push_back(const char* key, const ujson::value& value)
{
	bool ret = false;
	do {
		if ( this->_nodeType == NodeType_UnKnown ) {
			InitType( false );
		}
		
		if ( !this->IsObject() ) {
			SYS_ERR("not object");
			break;
		}

		if ( NULL == this->_pObj ) {
			SYS_ERR("object null");
			break;
		}
		this->_pObj->push_back(ujson::name_value_pair(key, value));
		ret =true;
	} while(false);
	return ret;
}
void UJsonNode::ToValue(ujson::value& value)
{
	if ( this->IsArray() ) {
		value =  std::move( ujson::value(*_pArray));
	} else if (  this->IsObject() ) {
		value =  std::move( ujson::value(*_pObj)) ;
	}
}
void UJsonNode::ToString(std::string& str, bool bFormat)
{
	ujson::value v;
	this->ToValue( v );
	if (bFormat)
		str = ujson::to_string( v ) ;
	else
		str = ujson::to_string( v, ujson::compact_utf8 );
}
bool UJsonNode::push_back(const char* key, UJsonNode& value)
{
	return this->push_back( key, value.ToValue());
}

bool UJsonNode::push_back(UJsonNode& value)
{
	return  this->push_back( value.ToValue() );
}

bool UJsonNode::push_back(const ujson::value& value)
{
	bool ret = false;
	do {
		if ( this->_nodeType == NodeType_UnKnown ) {
			InitType( true );
		}
		if ( !this->IsArray() ) {
			SYS_ERR("not array");
			break;
		}

		if ( NULL == this->_pArray ) {
			SYS_ERR("array null");
			break;
		}
		this->_pArray->push_back(value);
		ret =true;
	} while(false);
	return ret;
}
bool UJsonNode::InitFromValue(const ujson::value& value)
{
	bool ret = false;
	do {
		if ( value.is_array() ) {
			_nodeType = NodeType_Array;
			ujson::array const & a = array_cast( value );
			_pArray = const_cast<ujson::array*>(&a);
			ret =true;
			break;
		}

		if ( value.is_object()) {
			_nodeType = NodeType_Object;
			ujson::object const& o = object_cast( value);
			_pObj = const_cast<ujson::object*>(&o);
			ret =true;
		}
	} while(false);
	return ret;
}
bool UJsonNode::InitType(bool isArray)
{
	bool ret = false;
	do {
		if ( this->_nodeType != NodeType_UnKnown ) {
			SYS_ERR( "not unknown type %d", this->_nodeType);
			break;
		}
		
		if ( isArray ) {
			_nodeType = NodeType_Array;
			_pArray = new ujson::array();
		} else {
			_nodeType =NodeType_Object;
			_pObj   = new ujson::object();
		}
		this->_delObj = true;
		ret =true;
	} while(false);
	return ret;
}


///////////////////////////////////////////////////////////
UJ_Iterator::UJ_Iterator(const UJsonNode& node)
{
	_nodeType = node.GetNodeType();
	if ( this->IsArray() ) {
		this->_pArray = node.GetArray();
		this->_arrayIt = this->_pArray->begin();
	} else if ( this->IsObject() ) {
		this->_pObj   = node.GetObj();
		this->_objIt  = this->_pObj->begin();
	}
}

bool UJ_Iterator::end()
{
	if ( _nodeType == UJsonNode::NodeType_UnKnown )
		return true;
	return this->IsArray() ?
	       this->_arrayIt == this->_pArray->end() :
	       this->_objIt   == this->_pObj->end();
}

const char* UJ_Iterator::GetCurKey()
{

	return this->IsObject()?
	       (this->_objIt->first).c_str():
	       "";
}

const ujson::value& UJ_Iterator::GetCurValue()
{
	return this->IsArray() ?
	       *this->_arrayIt  :
	       this->_objIt->second ;

}

void UJ_Iterator::MoveNext()
{
	if ( this->IsArray() ) {
		this->_arrayIt ++;
	} else if (  this->IsObject() ) {
		this->_objIt ++;
	}
}

UJ_Iterator& UJ_Iterator::operator ++()
{
	this->MoveNext();
	return *this;
}

UJ_Iterator& UJ_Iterator::operator ++(int)
{
	this->MoveNext();
	return *this;
}

std::string UJ_Iterator::GetString()
{
	const ujson::value&  v = this->GetCurValue();
	return string_cast( v );
}

LsInt32  UJ_Iterator::GetInt32()
{
	const ujson::value&  v = this->GetCurValue();
	return int32_cast(v);
}

LsUInt32 UJ_Iterator::GetUInt32()
{
	const ujson::value&  v = this->GetCurValue();
	return uint32_cast(v);
}
LsInt8 UJ_Iterator::GetInt8()
{
	const ujson::value&  v = this->GetCurValue();
	return int32_cast(v);
}
LsUInt8 UJ_Iterator::GetUInt8()
{
	const ujson::value&  v = this->GetCurValue();
	return int32_cast(v);
}

LsInt16 UJ_Iterator::GetInt16()
{
	const ujson::value&  v = this->GetCurValue();
	return int32_cast(v);
}

LsUInt16 UJ_Iterator::GetUInt16()
{
	const ujson::value&  v = this->GetCurValue();
	return int32_cast(v);
}

LsInt64 UJ_Iterator::GetInt64()
{
	const ujson::value&  v = this->GetCurValue();
	return int64_cast(v);
}

LsUInt64 UJ_Iterator::GetUInt64()
{
	const ujson::value&  v = this->GetCurValue();
	return int64_cast(v);
}

double UJ_Iterator::GetDouble()
{
	const ujson::value&  v = this->GetCurValue();
	return double_cast(v);
}

float UJ_Iterator::GetFloat()
{
	const ujson::value&  v = this->GetCurValue();
	return double_cast(v);
}
bool UJ_Iterator::GetBool()
{
	const ujson::value&  v = this->GetCurValue();
	return bool_cast(v);
}
