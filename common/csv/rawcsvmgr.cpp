#include "rawcsvmgr.h"
#include "ls_debug.h"
#include <dirent.h>



Zby::CsvData* Zby::RawCsvMgr::GetCsvData(const char* name)
{
	Zby::CsvData* ret = NULL;
	do{
		CSV_MAP::iterator it =  _csvDataMap.find( name );
		if ( it == _csvDataMap.end() ){
			SYS_ERR( "NO TABLE %s", name );
			break;
		}
		ret = &(it->second);
	}while(false);
	return ret;
}

const std::string* Zby::RawCsvMgr::GetValue(const char* table, const char* id, const char* field)
{
	const std::string * ret = NULL;
	do{
		Zby::CsvData* tb = this->GetCsvData( table );
		if ( NULL == tb ){
			break;
		}
		ret = tb->GetValue( id, field );
	}while(false);
	return ret;
}

const std::string* Zby::RawCsvMgr::GetValue(const char* table, int id, const char* field)
{
	char temp[32];
	sprintf( temp, "%d", id );
	return this->GetValue( table, temp, field );
}

int Zby::RawCsvMgr::LoadFromPath(const char* path)
{
	DIR    *dir;
	struct dirent *ptr;
	dir = opendir( path );
	while((ptr = readdir(dir)) != NULL) {
		
		std::string file_name = ptr->d_name;
		int pos = file_name.find( ".csv" );
		if( pos != -1 ){
			std::string name = file_name.substr( 0, pos );
			std::string file_path = path + file_name;
			Zby::CsvData& cd = this->_csvDataMap[name];
			cd.LoadCsv( file_path.c_str() );
		} 
	}
	closedir(dir);
	return this->_csvDataMap.size();
}

Zby::RawCsvMgr::RawCsvMgr()
{
}

Zby::RawCsvMgr::~RawCsvMgr()
{
}

void Zby::RawCsvMgr::TestLoadCsv(const char* path)
{
	this->LoadFromPath( path );
	
	CSV_MAP::iterator iter = this->_csvDataMap.begin();
	for( ; iter != this->_csvDataMap.end(); ++iter ){
		Zby::CsvData cd = iter->second;
		const RowString& row = cd.GetFiedList();
		for( int i = 0; i < row.size(); i ++ ){
			//this->_fdIndex[ row[i]] = i;
			SYS_DEBUG( "%s:%d", row[i].c_str(), i );
		}
		SYS_DEBUG("count %d", cd.GetRowCount() );
	}
	SYS_DEBUG("file_count %d", this->_csvDataMap.size() );
}
