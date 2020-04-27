#ifndef CVSFILEPARSER_H
#define CVSFILEPARSER_H

#include "csvparser.h"
#include <string>
#include <vector>
#include <sstream>

template <class T> bool StrToType(std::string& in, T& value)
{
    bool ret = false;
    try {
        std::stringstream ss(in);
        ss >> value;
        ret = true;
    } catch(...) {
    }
    return ret;
}

typedef std::vector<std::string> RowString;
class IHandleCsvLin
{
public:
    virtual bool HandleLine(int idx, RowString& row) = 0;
};



class CvsFileParser
{
public:
    CvsFileParser();
    ~CvsFileParser();
    bool GetHeader(RowString& row);
    bool OpenCsvFile(const char* filePath, const char* delimiter = ",");
    bool EnumBody(IHandleCsvLin* pHandler);

protected:
    CsvParser* _csvparser;
    //CsvRowCpp _header;
};

#endif // CVSFILEPARSER_H
