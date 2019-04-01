/**
 * @file ordered_tec.h
 * @author lmy
 *
 */
# ifndef ORDERED_TEC_H
# define ORDERED_TEC_H

#include<cstddef>
#include<string>
#include<vector>
#include<map>
#include<bitset>
#include<fstream>
#include<sstream>
#include<typeinfo>
#include<stdexcept>

#ifdef OT_TINYXML
	#include"tinyxml2.h"
#endif

/**
 * @brief namespace ordered_tec
 */
namespace liton_ot
{
	typedef int INT32;
	typedef float FLOAT32;
	typedef double FLOAT64;

	typedef signed int longint;///<longint in tecplot, same as int
	typedef signed short int shortint;///<longint in tecplot, same as short int
	typedef signed char byte;///<byte in tecplot, same as char

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
		std::string FilePath;///<file path, default is current folder "."
		std::string FileName;///<file name, default is "untitled_file"
		std::string Title;///<file title, default is "untitled"
		std::vector<std::string> Variables;///<vector of variables' names
		/**
		 * @brief filetype
		 * @note
		 * - 0 full file
		 * - 1 grid file
		 * - 2 solution file
		 */
		INT32 FileType;
		std::map<std::string, std::string> Auxiliary;//<auxiliary in file
	  public:
		/**
		 * @brief Get the auxiliary data by name
		 *
		 * @tparam NUMT data type
		 * @param name data name
		 * @param data var to save data
		 */
		template<typename NUMT>
		void get_auxiliary_data(const std::string &name, NUMT &data) const
		{
			std::istringstream tran;
			std::map<std::string, std::string>::const_iterator aux_id = Auxiliary.find(name);
			if (aux_id == Auxiliary.end())
			{
				throw(std::runtime_error("can not find data [" + name + "] in auxiliary data of file [" + FileName + "]"));
			}
			tran.str(aux_id->second);
			tran >> data;
		}
	};

	class TEC_ZONE_BASE
	{
	  public:
		std::string ZoneName;///<zone name, default is "untitled_zone"
		INT32 StrandId;///<time strand id, -1 for static zone
		FLOAT64 SolutionTime;///<flowtime, used in animation
		INT32 Max[3];///<size of the original data @note in column-major order
		INT32 Dim;///<dimension of the original data
		INT32 Skip[3];///<stride to output in dimensions @note in column-major order
		INT32 Begin[3];///<offset at the head in dimensions @note in column-major order
		INT32 End[3];///<offset at the tail in dimensions @note in column-major order
		INT32 Real_Max[3];///<size of the original data @note in column-major order
		INT32 Real_Dim;///<dimension of the real data
		bool noskip;///<if skip data in output
		bool noexc;///<if exclude some data in output
		std::map<std::string, std::string> Auxiliary;///<auxiliary in zone
	  public:
		/**
		 * @brief Get the auxiliary data by name
		 *
		 * @tparam NUMT data type
		 * @param name data name
		 * @param data var to save data
		 */
		template<typename NUMT>
		void get_auxiliary_data(const std::string &name, NUMT &data) const
		{
			std::istringstream tran;
			std::map<std::string, std::string>::const_iterator aux_id = Auxiliary.find(name);
			if (aux_id == Auxiliary.end())
			{
				throw(std::runtime_error("can not find data [" + name + "] in auxiliary data of zone [" + ZoneName + "]"));
			}
			tran.str(aux_id->second);
			tran >> data;
		}
		/**
		 * @brief get the reference of Max in row-major order
		 *
		 * @param DIM dimensions of the original data
		 * @param d the dimension to get in row-major order
		 */
		inline INT32 &Max_C(const unsigned DIM, const unsigned d) { return Max[DIM - 1 - d]; }
		/**
		 * @brief get the reference of Begin in row-major order
		 *
		 * @param DIM dimensions of the original data
		 * @param d the dimension to get in row-major order
		 */
		inline INT32 &Begin_C(const unsigned DIM, const unsigned d) { return Begin[DIM - 1 - d]; }
		/**
		 * @brief get the reference of End in row-major order
		 *
		 * @param DIM dimensions of the original data
		 * @param d the dimension to get in row-major order
		 */
		inline INT32 &End_C(const unsigned DIM, const unsigned d) { return End[DIM - 1 - d]; }
		/**
		 * @brief get the reference of Skip in row-major order
		 *
		 * @param DIM dimensions of the original data
		 * @param d the dimension to get in row-major order
		 */
		inline INT32 &Skip_C(const unsigned DIM, const unsigned d) { return Skip[DIM - 1 - d]; }
		/**
		 * @brief get the value of Real_Max in row-major order
		 *
		 * @param DIM dimensions of the original data
		 * @param d the dimension to get in row-major order
		 */
		inline INT32 Real_Max_C(const unsigned DIM, const unsigned d) const { return Real_Max[DIM - 1 - d]; }
	};

	class TEC_DATA_BASE
	{
	  public:
		/**
		 * @brief enum used to identity data type
		 */
		enum TEC_TYPE
		{
			TEC_NULL,
			TEC_FLOAT = 1,///< float
			TEC_DOUBLE,///< double
			TEC_LONGINT,///< longint
			TEC_SHORTINT,///< shortint
			TEC_BYTE///< byte
		};
	  public:
		TEC_TYPE type;///<data type
		size_t size;///<sizeof(data type)
	};

	/**
	 * @brief class related to the log of tec files
	 */
	class TEC_FILE_LOG : public TEC_FILE_BASE
	{
		friend class TEC_FILE;
	  public:
		std::vector<TEC_ZONE_LOG> Zones;///<zone logs in file

		std::string Time_Begin;///<begin time to output
		std::string Time_End;///<end time to output
		double UsingTime;///<time used to output
		double Size;///<file size, in unit of MB
		std::string Error;///<error message
		std::vector<std::string> Echo_Text;///<echo text for file in each line, "#ZONE#" stand for zone
		std::vector<std::string> Json_Text;///<json text for file in each line, "#ZONE#" stand for zone
		std::vector<std::string> Xml_Text;///<xml text for file in each line, "#ZONE#" stand for zone
	  public:
		TEC_FILE_LOG();
		explicit TEC_FILE_LOG(const TEC_FILE &file);

		/**
		 * @brief write echo to (FilePath)/(FileName).txt
		 */
		void write_echo();
		/**
		 * @brief write echo to out file stream
		 *
		 * @param of out file stream
		 */
		void write_echo(std::ofstream &of);
		/**
		 * @brief write json to (FilePath)/(FileName).json
		 *
		 * @param depth depth of the file, one for one tab
		 */
		void write_json(int depth = 0);
		/**
		 * @brief write json to out file stream
		 *
		 * @param of of out file stream
		 * @param depth depth of the file, one for one tab
		 */
		void write_json(std::ofstream &of, int depth = 0);
		/**
		 * @brief write xml to (FilePath)/(FileName).xml
		 *
		 * @param depth depth of the file, one for one tab
		 */
		void write_xml(int depth = 0);
		/**
		 * @brief write xml to out file stream
		 *
		 * @param of of out file stream
		 * @param depth depth of the file, one for one tab
		 */
		void write_xml(std::ofstream &of, int depth = 0);

#ifdef OT_TINYXML
		/**
		 * @brief read file logs form xml file
		 *
		 * @param file_root node "File"
		 */
		void read_xml(const tinyxml2::XMLElement* file_root);
#endif
	  protected:
		void gen_json();
		void gen_xml();
	};

	/**
	 * @brief class related to the log of tec zones
	 */
	class TEC_ZONE_LOG : public TEC_ZONE_BASE
	{
		friend class TEC_FILE_LOG;
	  public:
		std::vector<TEC_DATA_LOG> Data;///<data logs in zone

		double Size;///<zone size, in unit of MB
		std::vector<std::string> Echo_Text;///<echo text for zone including data in each line
		std::vector<std::string> Json_Text;///<json text for zone including data in each line
		std::vector<std::string> Xml_Text;///<xml text for zone including data in each line
	  public:
		TEC_ZONE_LOG();
		explicit TEC_ZONE_LOG(const TEC_ZONE &zone);

		/**
		 * @brief write echo to (FilePath)/Zone_(ZoneName).txt
		 */
		void write_echo();
		/**
		 * @brief write echo to out file stream
		 *
		 * @param of out file stream
		 */
		void write_echo(std::ofstream &of);
		/**
		 * @brief write json to (FilePath)/Zone_(ZoneName).json
		 *
		 * @param depth depth of the file, one for one tab
		 */
		void write_json(int depth = 0);
		/**
		 * @brief write json to out file stream
		 *
		 * @param of of of out file stream
		 * @param depth depth of the file, one for one tab
		 */
		void write_json(std::ofstream &of, int depth = 0);
		/**
		 * @brief write xml to (FilePath)/Zone_(ZoneName).xml
		 *
		 * @param depth depth of the file, one for one tab
		 */
		void write_xml(int depth = 0);
		/**
		 * @brief write xml to out file stream
		 *
		 * @param of of out file stream
		 * @param depth depth of the file, one for one tab
		 */
		void write_xml(std::ofstream &of, int depth = 0);

#ifdef OT_TINYXML
		/**
		 * @brief read zone logs form xml file
		 *
		 * @param zone_root node "Zone"
		 */
		void read_xml(const tinyxml2::XMLElement* zone_root);
#endif
	  protected:
		void gen_json();
		void gen_xml();
	};

	/**
	 * @brief class related to the log of tec data
	 */
	class TEC_DATA_LOG : public TEC_DATA_BASE
	{
	  public:
		long int file_pt;///<file point for reading file
		double min;///<min of the output data
		double max;///<max of the output data
	  public:
		TEC_DATA_LOG();
		explicit TEC_DATA_LOG(const TEC_DATA &data);
	};

	/**
	 * @brief class related to the tec files
	 */
	class TEC_FILE : public TEC_FILE_BASE
	{
	  public:
		std::vector<TEC_ZONE> Zones;///< zones in file

		/**
		 * @brief flags to control echo
		 *
		 * - usingtime
		 * - time
		 * - size
		 * - section
		 * - variable
		 * - file_end
		 * - file_head
		 */
		std::bitset<7> Echo_Mode;

		TEC_FILE_LOG last_log;///<file log of the last time output
	  public:
		/**
		 * @brief construction function
		 *
		 * @param name file name, default is "untitled_file"
		 * @param path file path, default is "."
		 * @param title file title, default is "untitled"
		 */
		TEC_FILE(const std::string &name = "untitled_file", const std::string &path = ".", const std::string &title = "untitled");

		/**
		 * @brief add string type of auxiliary data
		 *
		 * @param name name
		 * @param value auxiliary data
		 * @return return if the operation succeeds
		 */
		bool add_auxiliary_data(const std::string &name, const std::string &value);
		/**
		 * @brief add double type of auxiliary data
		 *
		 * @param name name
		 * @param value auxiliary data
		 * @return return if the operation succeeds
		 */
		bool add_auxiliary_data(const std::string &name, const double &value);

		/**
		 * @brief set echo mode
		 *
		 * @param file file mode
		 * - brief(default) time, variable, file_end, file_head
		 * - full all
		 * - simple time, file_head
		 * - none none
		 *
		 * @param zone zone mode
		 * - brief(default) max_real, zone_head
		 * - full all
		 * - simple zone_head
		 * - none none
		 */
		void set_echo_mode(const std::string &file, const std::string &zone);

		/**
		 * @brief write plt data
		 *
		 * @param echo if echo on screen
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
	 */
	class TEC_ZONE : public TEC_ZONE_BASE
	{
		friend class TEC_FILE;
	  public:
		std::vector<TEC_DATA> Data;///data in zone

		/**
		 * @brief flags to control echo
		 *
		 * - size
		 * - stdid & soltime
		 * - begin & end
		 * - skip
		 * - max_org
		 * - max_real
		 * - variable
		 * - zone_end
		 * - zone_head
		 */
		std::bitset<9> Echo_Mode;
	  protected:
		INT32 Real_Max[3];
		INT32 Real_Dim;
		bool noskip, noexc;
		bool needreal;
	  public:
		/**
		 * @brief construction function
		 *
		 * @param name zone name, default is untitled_zone
		 */
		explicit TEC_ZONE(const std::string &name = "untitled_zone");
		/**
		 * @brief get real max
		 *
		 * @param d dimension to get
		 */
		INT32 get_real_max(unsigned d);
		/**
		 * @brief get real max in row-major order
		 *
		 * @param DIM dimensions of the original data
		 * @param d the dimension to get in row-major order
		 */
		INT32 get_real_max_C(const unsigned DIM, const unsigned &d);
		/**
		 * @brief get real dim
		 */
		INT32 get_real_dim();
		/**
		 * @brief add string type of auxiliary data
		 *
		 * @param name name
		 * @param value auxiliary data
		 * @return true if the operation succeeds
		 */
		bool add_auxiliary_data(const std::string &name, const std::string &value);
		/**
		 * @brief add double type of auxiliary data
		 *
		 * @param name name
		 * @param value auxiliary data
		 * @return true if the operation succeeds
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
	 */
	class TEC_DATA : public TEC_DATA_BASE
	{
		friend class TEC_ZONE;
	  public:
		const void* DataP;///<pointer points to data
	  protected:
		byte* buf;
	  public:
		TEC_DATA();
		/**
		 * @brief construction function
		 *
		 * @tparam T data type
		 * @param iDataP pointer points to data
		 */
		template<typename T> explicit TEC_DATA(T* iDataP);

	  protected:
		std::pair<FLOAT64, FLOAT64> minmax(size_t N) const;
	};
}

template<typename T> liton_ot::TEC_DATA::TEC_DATA(T* iDataP)
{
	if (typeid(iDataP) == typeid(float*) || typeid(iDataP) == typeid(const float*))
	{
		type = TEC_DATA::TEC_FLOAT;
	}
	else if (typeid(iDataP) == typeid(double*) || typeid(iDataP) == typeid(const double*))
	{
		type = TEC_DATA::TEC_DOUBLE;
	}
	else if ((typeid(iDataP) == typeid(longint*) || typeid(iDataP) == typeid(shortint*)
	          || typeid(iDataP) == typeid(const longint*) || typeid(iDataP) == typeid(const shortint*))
	         && sizeof(T) == TEC_LONGINT_S)
	{
		type = TEC_DATA::TEC_LONGINT;
	}
	else if ((typeid(iDataP) == typeid(shortint*) || typeid(iDataP) == typeid(longint*)
	          || typeid(iDataP) == typeid(const shortint*) || typeid(iDataP) == typeid(const longint*))
	         && sizeof(T) == TEC_SHORTINT_S)
	{
		type = TEC_DATA::TEC_SHORTINT;
	}
	else if (typeid(iDataP) == typeid(byte*) || typeid(iDataP) == typeid(const byte*))
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
