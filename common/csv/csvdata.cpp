#include "csvdata.h"
#include "ls_debug.h"


Zby::CsvData::CsvData()
{
}

bool Zby::CsvData::HandleLine(int idx, RowString& row)
{
	//SYS_DEBUG( "IDX %d %s %s", idx, row[0].c_str(), row[1].c_str() );
	if ( 0 == idx ){
		this->ParseHeader( row );
	}else if ( idx >= 2){
		_rowMap.insert( RAW_MAP::value_type( row[0], row ));
	}
	return true;
}

bool Zby::CsvData::LoadCsv(const char* pFile)
{
	bool ret = false;
	do {
		CvsFileParser cfp;
		if ( !cfp.OpenCsvFile( pFile ))
			break;
		cfp.EnumBody( this );
		ret = true;
	} while(false);
	return ret;
}

Zby::CsvData::~CsvData()
{
}
void Zby::CsvData::ParseHeader(RowString& row)
{
	this->_header = row;
	for( int i = 0; i < row.size(); i ++ ){
		this->_fdIndex[ row[i]] = i;
		//SYS_DEBUG( "%s:%d", row[i].c_str(), i );
	}
}

const RowString* Zby::CsvData::GetRowData(const char* id)
{
	const RowString* ret = NULL;
	do{
		RAW_MAP::iterator it = this->_rowMap.find( id );
		if ( it == this->_rowMap.end() ){
			SYS_ERR( "no id %s", id );
			break;
		}
		ret = &(it->second);
	}while( false);
	return ret;
}

const RowString* Zby::CsvData::GetRowData(int id)
{
	char temp[32];
	sprintf( temp, "%d", id );
	return this->GetRowData(temp ); 
}

const std::string* Zby::CsvData::GetValue(const char* id, const char* field)
{
	const std::string* ret = NULL;
	do{
		const RowString* row = this->GetRowData( id );
		if ( NULL == row ){
			break;
		}
		
		FD_INDEX::iterator it =  _fdIndex.find( field );
		if ( it == _fdIndex.end() ){
			SYS_ERR( "id %s NO field %s ", id, field );
			break;
		}
		
		int index = it->second;
		if ( index >= row->size() ){
			SYS_ERR( "id %s NO field %s len err %d", id, field , index);
			break; 
		}
		
		ret = &(row->at( index ));
	}while(false);
	
	
	return ret;
}

const std::string* Zby::CsvData::GetValue(int id, const char* field)
{
	char temp[32];
	sprintf( temp, "%d", id );
	return this->GetValue( temp, field );
}
