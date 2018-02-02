#ifndef LITON_SNIPPET_HPP
#define LITON_SNIPPET_HPP

#include <cstdlib>
#include <cstdio>

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include <ctime>

namespace liton_sp
{
	class file
	{
	  public:
		static inline FILE* open_file_c(const std::string &fullname, const char* mode)
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
	};

	class time
	{
	  public:
		static inline std::string get_time(const std::string &format = "%Y%m%dT%H%M%S")
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
	};

	class env
	{
	  public:
		static const char* os;
		static const char* compiler;
		static const char* cpp_std;
		static const char* debug_mode;
		static void disp_env(std::ostream &out)
		{
			out << os << std::endl;
			out << compiler << std::endl;
			out << cpp_std << std::endl;
			out << debug_mode << std::endl;
		}
	};

#ifdef _WIN32
	const char* env::os = "Windows 32 or Windows 64";
#elif _WIN64
	const char* env::os = "Windows 64";
#elif __MINGW32__
	const char* env::os = "Windows32 by mingw compiler";
#elif __CYGWIN__
	const char* env::os = "Cygwin";
#elif __linux__
	const char* env::os = "linux";
#endif

#ifdef __INTEL_COMPILER
	const char* env::compiler = "Interl C++";
#elif _MSC_VER
	const char* env::compiler = "Visual C++";
#elif __GNUC__
	const char* env::compiler = "GCC";
#endif

#if (__cplusplus < 201103L && !defined(_MSC_VER)) || (defined(_MSC_VER) && (_MSC_VER < 1700))
	const char* env::cpp_std = "C++03";
#else
	const char* env::cpp_std = "C++11";
#endif

#if defined(_DEBUG) || defined(DEBUG)
	#ifndef _DEBUG
		#define _DEBUG
	#endif
	const char* env::debug_mode = "DEBUG";
#elif defined(_NDEBUG) || !defined(_DEBUG)
	const char* env::debug_mode = "RELEASE";
#endif

	class debug
	{
	  public:
		template<typename Expression>
		static void exec_except(const Expression &exp, std::ostream &out, std::ostream &except_out)
		{
			std::ostringstream tran;
			tran << std::setw(10) << std::setfill('0') << std::rand();
			std::string timestr = "[" + time::get_time() + "|" + tran.str() + "]: ";
			try
			{
				exp();
				out << timestr << "no exception" << std::endl;
			}
			catch (const std::exception &err)
			{
				out << timestr << "with exception" << std::endl;
				except_out << timestr << err.what() << std::endl;
			}
		}

		template<typename Expression>
		static double exec_time(const unsigned &N, const Expression &exp)
		{
			double t = 0;
			for (unsigned i = 0; i != N; ++i)
			{
				clock_t clock_begin = clock();
				exp();
				t += static_cast<double>(clock() - clock_begin) / CLOCKS_PER_SEC;
			}
			t /= static_cast<double>(N);
			return t;
		}
	};
}

#endif
