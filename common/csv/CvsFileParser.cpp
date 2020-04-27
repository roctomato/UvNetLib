#include "CvsFileParser.h"

CvsFileParser::CvsFileParser():_csvparser(NULL)
{
}

CvsFileParser::~CvsFileParser()
{
    if (_csvparser)
        CsvParser_destroy(_csvparser);
}

bool CvsFileParser::OpenCsvFile(const char* filePath, const char* delimiter)
{
    _csvparser = CsvParser_new( filePath, delimiter, 1 );
    return NULL != _csvparser ;
}

bool CvsFileParser::GetHeader(RowString& row)
{
    CsvRow* header = CsvParser_getHeader(_csvparser);
    if (header == NULL) {
        return false;
    }
    char **headerFields = CsvParser_getFields(header);
    for (int i = 0 ; i < CsvParser_getNumFields(header) ; i++) {
        row.push_back( headerFields[i] );    
    }
    return true;
}
bool CvsFileParser::EnumBody(IHandleCsvLin* pHandler)
{
    bool ret = false;
    do{
        if ( NULL == pHandler)
            break;
        CsvRow *row=NULL;
        RowString vec;
        int line = 0;
        while ((row = CsvParser_getRow(_csvparser)) ) {
            //printf("NEW LINE:\n");
            char **rowFields = CsvParser_getFields(row);
            vec.clear();
            for (int i = 0 ; i < CsvParser_getNumFields(row) ; i++) {
                vec.push_back(rowFields[i]);
            }
            CsvParser_destroy_row(row);
            if (  !pHandler->HandleLine( line++, vec) ){
                break;
            }
        }
        ret = true;
    }while(false);
    return ret;
}

