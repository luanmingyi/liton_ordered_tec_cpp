#ifndef LITON_TIME_HPP
#define LITON_TIME_HPP

#include <string>
#include <ctime>

namespace liton
{
	namespace sp
	{
		inline std::string get_time(const std::string &format = "%Y%m%dT%H%M%S")
		{
			time_t time_c = std::time(NULL);
			struct tm tm_c;
# ifdef __linux__
			localtime_r(&time_c, &tm_c);
# else
			localtime_s(&tm_c, &time_c);
# endif
			char buf[100];
			std::strftime(buf, 100, format.c_str(), &tm_c);
			return buf;
		}
	}
}

#endif
