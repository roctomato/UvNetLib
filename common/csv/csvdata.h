#ifndef CSVDATA_H
#define CSVDATA_H

#include <stdio.h>
#include "CvsFileParser.h"
#include <map>
#include <string>
#include "ls_xtype.h"

namespace Zby
{

	typedef std::map<std::string, int> FD_INDEX;
	typedef std::map<std::string, RowString> RAW_MAP;
	
	class CsvData: public IHandleCsvLin{
	public:
		CsvData();
		~CsvData();
		virtual bool HandleLine( int idx, RowString& row);
		bool LoadCsv( const char* pFile);
		
		const RowString*  GetRowData( int id );
		const RowString*  GetRowData( const char* id );
		
		const std::string* GetValue( int id, const char* field );
		const std::string* GetValue( const char* id, const char* field );
		
		int GetRowCount(){ return _rowMap.size(); }
		const RowString& GetFiedList(){ return _header; }
		const RAW_MAP& GetCsvData(){ return _rowMap; }
	private:
		void ParseHeader(RowString& row);
		FD_INDEX _fdIndex;
		RAW_MAP  _rowMap;
		RowString	_header;
	};

}
#endif // CSVDATA_H
