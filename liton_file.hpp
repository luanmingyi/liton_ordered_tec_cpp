#ifndef LITON_FILE_HPP
#define LITON_FILE_HPP

#include <cstdio>
#include <string>
#include <stdexcept>

namespace liton
{
	namespace sp
	{
		inline FILE* open_file_c(const std::string &fullname, const char* mode)
		{
# ifdef __linux__
			FILE* of;
			of = std::fopen(fullname.c_str(), mode);
			if (of == NULL)
			{
				throw std::runtime_error(std::string("can not open file ") + fullname);
			}
# else
			FILE* of;
			errno_t err = fopen_s(&of, fullname.c_str(), mode);
			if (err != 0)
			{
				throw std::runtime_error(std::string("can not open file ") + fullname);
			}
# endif
			return of;
		}
	}
}

#endif
