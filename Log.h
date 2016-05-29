#ifndef _LOG_H_
#define _LOG_H_


#include <iostream>
#include <fstream>


typedef enum LogType
{
	LOG_DEBUG,
	LOG_WARNING,
	LOG_ERROR,
	LOG_FATAL
} LogType;

std::ostream& log( const LogType &t );

#endif // _LOG_H_

