# ifndef ORDERED_TEC_H
# define ORDERED_TEC_H

#include<cstddef>
#include<string>
#include<vector>
#include<map>
#include<bitset>
#include<fstream>
#include<typeinfo>
#include<stdexcept>
#include"tinyxml2.h"

/**
 * @brief 
 * 
 */
namespace liton_ot
{
	typedef int INT32;
	typedef float FLOAT32;
	typedef double FLOAT64;

	typedef signed int longint;
	typedef signed short int shortint;
	typedef signed char byte;

	const size_t TEC_FLOAT_S = 4;
	const size_t TEC_DOUBLE_S = 8;
	const size_t TEC_LONGINT_S = 4;
	const size_t TEC_SHORTINT_S = 2;
	const size_t TEC_BYTE_S = 1;

	class TEC_FILE_BASE;
	class TEC_ZONE_BASE;
	class TEC_DATA_BASE;
	class TEC_FILE_LOG;
	class TEC_ZONE_LOG;
	class TEC_DATA_LOG;
	class TEC_FILE;
	class TEC_ZONE;
	class TEC_DATA;

	class TEC_FILE_BASE
	{
	  public:
		std::string FilePath;///file path, default is "."
		std::string FileName;///.
		std::string Title;///.
		std::vector<std::string> Variables;///.
		INT32 FileType;///.
		std::map<std::string, std::string> Auxiliary;///.
	};

	class TEC_ZONE_BASE
	{
	  public:
		std::string ZoneName;///.
		INT32 StrandId;///.
		FLOAT64 SolutionTime;///.
		INT32 Max[3];///.
		INT32 Dim;///.
		INT32 Skip[3];///.
		INT32 Begin[3];///.
		INT32 End[3];///.
		INT32 Real_Max[3];///.
		INT32 Real_Dim;///.
		bool noskip, noexc;///.
		std::map<std::string, std::string> Auxiliary;///.
	};

	class TEC_DATA_BASE
	{
	  public:
		/**
		 * @brief 
		 * 
		 */
		enum TEC_TYPE
		{
			TEC_NULL,
			TEC_FLOAT = 1,
			TEC_DOUBLE,
			TEC_LONGINT,
			TEC_SHORTINT,
			TEC_BYTE
		};
	  public:
		TEC_TYPE type;///.
		size_t size;///.
	};

	/**
	 * @brief class related to the log of tec files
	 *
	 */
	class TEC_FILE_LOG : public TEC_FILE_BASE
	{
		friend class TEC_FILE;
	  public:
		std::vector<TEC_ZONE_LOG> Zones;///.

		std::string Time_Begin;///.
		std::string Time_End;///.
		double UsingTime;///.
		double Size;///.
		std::string Error;///.
		std::vector<std::string> Echo_Text;///.
		std::vector<std::string> Json_Text;///.
		std::vector<std::string> Xml_Text;///.
	  public:
		/**
		 * @brief
		 *
		 */
		TEC_FILE_LOG();
		/**
		 * @brief
		 *
		 * @param file
		 */
		explicit TEC_FILE_LOG(const TEC_FILE &file);

		/**
		 * @brief
		 *
		 */
		void write_echo();
		/**
		 * @brief
		 *
		 * @param of
		 */
		void write_echo(std::ofstream &of);
		/**
		 * @brief
		 *
		 * @param depth
		 */
		void write_json(int depth = 0);
		/**
		 * @brief
		 *
		 * @param of
		 * @param depth
		 */
		void write_json(std::ofstream &of, int depth = 0);
		/**
		 * @brief
		 *
		 * @param depth
		 */
		void write_xml(int depth = 0);
		/**
		 * @brief
		 *
		 * @param of
		 * @param depth
		 */
		void write_xml(std::ofstream &of, int depth = 0);

		/**
		 * @brief
		 *
		 * @param file_root
		 */
		void read_xml(const tinyxml2::XMLElement* file_root);
	  protected:
		void gen_json();
		void gen_xml();
	};

	/**
	 * @brief class related to the log of tec zones
	 *
	 */
	class TEC_ZONE_LOG : public TEC_ZONE_BASE
	{
		friend class TEC_FILE_LOG;
	  public:
		std::vector<TEC_DATA_LOG> Data;///.

		double Size;///.
		std::vector<std::string> Echo_Text;///.
		std::vector<std::string> Json_Text;///.
		std::vector<std::string> Xml_Text;///.
	  public:
		/**
		 * @brief
		 *
		 */
		TEC_ZONE_LOG();
		/**
		 * @brief
		 *
		 * @param zone
		 */
		explicit TEC_ZONE_LOG(const TEC_ZONE &zone);

		/**
		 * @brief
		 *
		 */
		void write_echo();
		/**
		 * @brief
		 *
		 * @param of
		 */
		void write_echo(std::ofstream &of);
		/**
		 * @brief
		 *
		 * @param depth
		 */
		void write_json(int depth = 0);
		/**
		 * @brief
		 *
		 * @param of
		 * @param depth
		 */
		void write_json(std::ofstream &of, int depth = 0);
		/**
		 * @brief
		 *
		 * @param depth
		 */
		void write_xml(int depth = 0);
		/**
		 * @brief
		 *
		 * @param of
		 * @param depth
		 */
		void write_xml(std::ofstream &of, int depth = 0);

		/**
		 * @brief
		 *
		 * @param zone_root
		 */
		void read_xml(const tinyxml2::XMLElement* zone_root);
	  protected:
		void gen_json();
		void gen_xml();
	};

	/**
	 * @brief class related to the log of tec data
	 *
	 */
	class TEC_DATA_LOG : public TEC_DATA_BASE
	{
	  public:
		long int file_pt;///.
		double min;///.
		double max;///.
	  public:
		/**
		 * @brief
		 *
		 */
		TEC_DATA_LOG();
		/**
		 * @brief
		 *
		 * @param data
		 */
		explicit TEC_DATA_LOG(const TEC_DATA &data);
	};

	/**
	 * @brief class related to the tec files
	 *
	 */
	class TEC_FILE : public TEC_FILE_BASE
	{
	  public:
		std::vector<TEC_ZONE> Zones;///.

		//usingtime, time, size, section, variable, file_end, file_head
		std::bitset<7> Echo_Mode;///.

		TEC_FILE_LOG last_log;///.
	  public:
		/**
		 * @brief 
		 * 
		 */
		TEC_FILE(const std::string &name = "untitled_file", const std::string &path = ".", const std::string &title = "untitled");

		/**
		 * @brief 
		 * 
		 * @param name 
		 * @param value 
		 * @return true 
		 * @return false 
		 */
		bool add_auxiliary_data(const std::string &name, const std::string &value);
		/**
		 * @brief 
		 * 
		 * @param name 
		 * @param value 
		 * @return true 
		 * @return false 
		 */
		bool add_auxiliary_data(const std::string &name, const double &value);

		/**
		 * @brief 
		 * 
		 * @param file 
		 * @param zone 
		 */
		void set_echo_mode(const std::string &file, const std::string &zone);

		/**
		 * @brief 
		 * 
		 * @param echo 
		 */
		void write_plt(bool echo = true);
	  protected:
		void echo_mode(const std::string &echo = "brief");

		void wrtie_plt_pre();
		void write_plt_head(FILE* of, bool echo = true);
		void write_plt_data(FILE* of, bool echo = true);
	};

	/**
	 * @brief class related to the tec zones
	 *
	 */
	class TEC_ZONE : public TEC_ZONE_BASE
	{
		friend class TEC_FILE;
	  public:
		std::vector<TEC_DATA> Data;///.

		//size, stdid & soltime, begin & end, skip, max_org, max_real, variable, zone_end, zone_head
		std::bitset<9> Echo_Mode;///.
	  protected:
		INT32 Real_Max[3];
		INT32 Real_Dim;
		bool noskip, noexc;
		bool needreal;
	  public:
		/**
		 * @brief 
		 * 
		 */
		explicit TEC_ZONE(const std::string &name = "untitled_zone");
		/**
		 * @brief 
		 * 
		 */
		const INT32* get_real_size(const std::string &name = "realmax");
		/**
		 * @brief 
		 * 
		 * @param name 
		 * @param value 
		 * @return true 
		 * @return false 
		 */
		bool add_auxiliary_data(const std::string &name, const std::string &value);
		/**
		 * @brief 
		 * 
		 * @param name 
		 * @param value 
		 * @return true 
		 * @return false 
		 */
		bool add_auxiliary_data(const std::string &name, const double &value);
	  protected:
		void echo_mode(const std::string &echo = "brief");

		void gather_real_size();
		void make_buf();
		void realise_buf();

		void wrtie_plt_pre(const TEC_FILE &thisfile, TEC_ZONE_LOG &zone_log);
		void write_plt_head(FILE* of) const;
		void write_plt_data(FILE* of, const TEC_FILE &thisfile, TEC_ZONE_LOG &zone_log, bool echo = true);
	};

	/**
	 * @brief class related to the tec data
	 *
	 */
	class TEC_DATA : public TEC_DATA_BASE
	{
		friend class TEC_ZONE;
	  public:
		const void* DataP;///.
	  protected:
		byte* buf;
	  public:
		/**
		 * @brief 
		 * 
		 */
		TEC_DATA();
		/**
		 * @brief 
		 * 
		 * @tparam T 
		 * @param iDataP 
		 */
		template<typename T> explicit TEC_DATA(T* iDataP);

	  protected:
		std::pair<FLOAT64, FLOAT64> minmax(size_t N) const;
	};
}

template<typename T> liton_ot::TEC_DATA::TEC_DATA(T* iDataP)
{
	if (typeid(iDataP) == typeid(float*))
	{
		type = TEC_DATA::TEC_FLOAT;
	}
	else if (typeid(iDataP) == typeid(double*))
	{
		type = TEC_DATA::TEC_DOUBLE;
	}
	else if ((typeid(iDataP) == typeid(longint*) || typeid(iDataP) == typeid(int*)) && sizeof(T) == TEC_LONGINT_S)
	{
		type = TEC_DATA::TEC_LONGINT;
	}
	else if ((typeid(iDataP) == typeid(shortint*) || typeid(iDataP) == typeid(int*)) && sizeof(T) == TEC_SHORTINT_S)
	{
		type = TEC_DATA::TEC_SHORTINT;
	}
	else if (typeid(iDataP) == typeid(byte*))
	{
		type = TEC_DATA::TEC_BYTE;
	}
	else
	{
		char buf[300];
#ifdef _MSC_VER
		sprintf_s(buf, "type [%s]*%i is unsupported in Tecplot", typeid(T).name(), static_cast<int>(sizeof(T)));
#else
		std::sprintf(buf, "type [%s]*%i is unsupported in Tecplot", typeid(T).name(), static_cast<int>(sizeof(T)));
#endif
		throw(std::runtime_error(buf));
	}
	DataP = iDataP;
	buf = NULL;
	size = sizeof(T);
}

# endif
