#ifndef LOG4CPPLOGGEREX_H
#define LOG4CPPLOGGEREX_H

#include "loggerinterfaceex.h" // Base class: LoggerInterfaceEx
#include "log4cpp/Category.hh"
#include "log4cpp/PropertyConfigurator.hh"

class Log4cppLoggerEx : public LoggerInterfaceEx
{
public:
	/// Instantiation Log4cppLogger object.
	//static Log4cppLoggerEx& Instance();


	Log4cppLoggerEx(){}
	virtual ~Log4cppLoggerEx() {printf("log exit\n");}

// Method.
public:
	/// Load configure.
	void Configure( const std::string& configFile_ )  {
		try {
			log4cpp::PropertyConfigurator::configure( configFile_ );
		} catch( log4cpp::ConfigureFailure& reason ) {
			throw ConfigureExceptionEx( reason.what()  );
		}
	}


	/// Log a message with the specified category and priority.
	virtual void Print( const std::string& categoryName_, int priority_, const char* format_,  va_list args ) {
		log4cpp::Category::getInstance( categoryName_ ).logva( priority_, format_, args );
	};

	/// Log a message with the specified category and priority.
	virtual void Print( const std::string& categoryName_, int priority_, const std::string& message_ )  {
		log4cpp::Category::getInstance( categoryName_ ).log( priority_, message_ );
	};

};

#endif // LOG4CPPLOGGEREX_H
