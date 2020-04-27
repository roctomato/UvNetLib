#include "log4cpploggerex.h"


Log4cppLoggerEx& Log4cppLoggerEx::Instance()
{
	static Log4cppLoggerEx logger;
	return logger;
}
