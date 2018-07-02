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

#ifdef SP_TINYXML
	#include "../tinyxml2/tinyxml2.h"
#endif

namespace liton_sp
{
	class file
	{
	  public:
		static inline FILE* open_file_c(const std::string &fullname, const char* mode)
		{
# ifdef _MSC_VER
			FILE* of;
			errno_t err = fopen_s(&of, fullname.c_str(), mode);
			if (err != 0)
			{
				throw std::runtime_error(std::string("can not open file ") + fullname);
			}
# else
			FILE* of;
			of = std::fopen(fullname.c_str(), mode);
			if (of == NULL)
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
# ifdef _MSC_VER
			localtime_s(&tm_c, &time_c);
# else
			localtime_r(&time_c, &tm_c);
# endif
			char buf[100];
			std::strftime(buf, 100, format.c_str(), &tm_c);
			return buf;
		}
	};

	class env
	{
	  public:
		static const char* os()
		{
#ifdef _WIN32
			return "Windows 32 or Windows 64";
#elif _WIN64
			return "Windows 64";
#elif __MINGW32__
			return "Windows32 by mingw compiler";
#elif __CYGWIN__
			return "Cygwin";
#elif __linux__
			return "linux";
#endif
		}
		static const char* compiler()
		{
#ifdef __INTEL_COMPILER
			return "Interl C++";
#elif _MSC_VER
			return "Visual C++";
#elif __GNUC__
			return "GCC";
#endif
		}
		static const char* cpp_std()
		{
#if (__cplusplus < 201103L && !defined(_MSC_VER)) || (defined(_MSC_VER) && (_MSC_VER < 1700))
			return "C++03";
#else
			return "C++11";
#endif
		}
		static const char* debug_mode()
		{
#if defined(_DEBUG) || defined(DEBUG)
#ifndef _DEBUG
#define _DEBUG
#endif
			return "DEBUG";
#elif defined(_NDEBUG) || !defined(_DEBUG)
			return "RELEASE";
#endif
		}
		static void disp_env(std::ostream &out)
		{
			out << os() << std::endl;
			out << compiler() << std::endl;
			out << cpp_std() << std::endl;
			out << debug_mode() << std::endl;
		}
	};

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

	class xml
	{
	  public:
#ifdef SP_TINYXML
		static const tinyxml2::XMLElement* load_xml(tinyxml2::XMLDocument &xml_file, std::string xml_file_name, std::string root_node_name)
		{
			tinyxml2::XMLError err_code = xml_file.LoadFile(xml_file_name.c_str());
			if (err_code != 0)
			{
				std::ostringstream tran;
				if (err_code == tinyxml2::XML_ERROR_FILE_NOT_FOUND)
				{
					tran << "case file " << xml_file_name << " not found";
				}
				else
				{
					tran << "error when loading file " << xml_file_name << ": error ID " << err_code;
				}
				throw(std::runtime_error(tran.str()));
			}
			const tinyxml2::XMLElement* xml_root = xml_file.FirstChildElement(root_node_name.c_str());
			if (xml_root == 0)
			{
				std::ostringstream tran;
				tran << "node \"" << root_node_name << "\" not found in " << xml_file_name;
				throw(std::runtime_error(tran.str()));
			}
			return xml_root;
		}

		static void check_xmlnode(const tinyxml2::XMLElement* xml, const std::string &node_name)
		{
			if (xml->FirstChildElement(node_name.c_str()) == 0)
			{
				throw(std::runtime_error("node \"" + node_name + "\" not found in node \"" + xml->Name() + "\""));
			}
		}

		static const tinyxml2::XMLElement* get_xmlnode(const tinyxml2::XMLElement* xml, const std::string &node_name)
		{
			check_xmlnode(xml,node_name);
			return xml->FirstChildElement(node_name.c_str());
		}
#endif
	};
}

#endif
