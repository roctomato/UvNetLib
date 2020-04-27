#ifndef TIDFACTORY_H
#define TIDFACTORY_H

#include <cstdint>
#include <map>
#include <set>
#include <string>


template <typename ID_TYPE = uint32_t >
class TGenID
{
public:
    TGenID( ID_TYPE minid, ID_TYPE maxid )
        :_curID(minid),_minID(minid),_maxID( maxid)
    {}

    ID_TYPE GenID()
    {
        ID_TYPE curid = _curID ++;
        if ( _curID >  _maxID ) {
            _curID = _minID;
        }
        return  curid;
    }

    ID_TYPE GetCurID()
    {
        return _curID;
    }

    void SetStartID( ID_TYPE curID)
    {
        if ( curID < _curID  ) {
            _curID = _minID;
        } else if ( curID > _maxID ) {
            _curID = _maxID;
        } else {
            _curID = curID;
        }
    }

protected:
    ID_TYPE _curID;
    ID_TYPE _minID;
    ID_TYPE _maxID;
};

template<typename T, typename ID_TYPE = uint32_t>
class TIdFactory
{
public:
    typedef std::map<ID_TYPE,T*>   NodeIDMap;
    typedef std::set<ID_TYPE>      SetClientID;
    typedef void (*ENUM_NODE_FUNC)(T* data_, ID_TYPE id,  void* pContext_);

public:
    TIdFactory(ID_TYPE minid = 1, ID_TYPE maxid = 0xfffffff0 )
        :_genID(minid, maxid)
    {}

    template<typename...P>
    T* NewObj(ID_TYPE& id,  P... args )
    {
        T* ret = NULL;
        do {
            ret = new T( args...);;
            if ( nullptr == ret ) {
                break;
            }
            id = this->_genID.GenID();
            this->_nodeIDMap[id] = ret;
        } while(false);
        return ret;
    }

    int GetCount()
    {
        return this->_nodeIDMap.size();
    }
    bool DeletObj(ID_TYPE id )
    {
        bool ret = false;
        do {
            T* data = this->FindObj( id );
            if ( NULL == data ) {
                break;
            }
            if ( this->_inItetator ) {
                _removeSet.insert(id);
            } else {
                this->_nodeIDMap.erase(id);
                delete data;
            }
        } while(false);
        return ret;
    }

    T* FindObj(ID_TYPE id )
    {
        T* ret = NULL;
        do {
            auto it = _nodeIDMap.find( id );
            if ( it == _nodeIDMap.end()) {
                break;
            }
            ret = it->second;
        } while(false);
        return ret;
    }
    bool  EnumAllList(ENUM_NODE_FUNC fn,void* pContext_ = NULL)
    {
        bool ret = !_nodeIDMap.empty();
        if ( ret ) {
            this->_inItetator = true;
            for( auto it = _nodeIDMap.begin(); it != _nodeIDMap.end(); it ++ ) {
                T* pNode = it->second;
                fn( pNode, it->first, pContext_);
            }
            this->_inItetator= false;
            if ( ! this->_removeSet.empty() ) {
                this->DoRemove();
            }
        }
        return ret;
    }
private:
    void DoRemove()
    {
        for( auto it = _removeSet.begin(); it != _removeSet.end(); it ++ ) {
            DeletObj(*it);
        }
        _removeSet.clear();
    }

    TGenID<ID_TYPE>  _genID;

    NodeIDMap	  _nodeIDMap;

    SetClientID   _removeSet;
    bool		  _inItetator =false;
};


#endif // TIDFACTORY_H
