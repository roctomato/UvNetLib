#ifndef RAWCSVMGR_H
#define RAWCSVMGR_H
#include "csvdata.h"

namespace Zby
{
	typedef std::map< std::string, CsvData> CSV_MAP;
	class RawCsvMgr
	{
	public:
		RawCsvMgr();
		~RawCsvMgr();
		int LoadFromPath( const char* path );
		CsvData* GetCsvData( const char* name );
		
		void TestLoadCsv( const char* path );
		
		const std::string* GetValue( const char* table, int id, const char* field );
		const std::string* GetValue( const char* table, const char* id, const char* field );
	private:
		CSV_MAP _csvDataMap;

	};
}
#endif // RAWCSVMGR_H
