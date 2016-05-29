#include "Log.h"

#include "Misc.h"
#include "ResourcesManager.h"


std::ostream& log( const LogType &t )
{
	switch( t )
	{
		case LOG_DEBUG:
			std::cout << "[DBG] ";
			break;

		case LOG_WARNING:
			std::cout << "[WRN] ";
			break;

		case LOG_ERROR:
			std::cout << "[ERR] ";
			break;

		case LOG_FATAL:
			std::cout << "[/!\\] ";
			break;

		default:
			std::cout << "[***] ";
			break;
	}

	return std::cout;
}

