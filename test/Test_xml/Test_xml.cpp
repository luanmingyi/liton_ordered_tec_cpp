# include <iostream>
# include <fstream>
# include <cstdlib>
using namespace std;
# include "tinyxml2.h"
# include "ordered_tec.h"
using namespace liton_ot;

# define DATATYPE double
int main(int argc, char** argv)
{
	DATATYPE* x, *y, *z, *w;
	size_t NI = 20, NJ = 40;
	try
	{
		x = new DATATYPE[NI * NJ];
		y = new DATATYPE[NI * NJ];
		z = new DATATYPE[NI * NJ];
		w = new DATATYPE[NI * NJ];
	}
	catch (...)
	{
		cerr << "runtime_error: out of memery" << endl;
		return 0;
	}
	for (int j = 0; j != NJ; ++j)
	{
		for (int i = 0; i != NI; ++i)
		{
			x[i + j * NI] = j;
			y[i + j * NI] = i;
			z[i + j * NI] = 1 + i / 2 + j;
			w[i + j * NI] = i + j;
		}
	}

	TEC_FILE tecfile("test_11", ".", "test_11");
	tecfile.Variables.push_back("x");
	tecfile.Variables.push_back("y");
	tecfile.Variables.push_back("z");
	tecfile.add_auxiliary_data("Auxiliary1", "Auxiliary_test_1_ds");
	tecfile.add_auxiliary_data("Auxiliary2", 3.14);

	tecfile.Zones.push_back(TEC_ZONE("A"));
	tecfile.Zones[0].Max[0] = NI;
	tecfile.Zones[0].Max[1] = NJ;
	tecfile.Zones[0].Data.push_back(TEC_DATA(x));
	tecfile.Zones[0].Data.push_back(TEC_DATA(y));
	tecfile.Zones[0].Data.push_back(TEC_DATA(z));

	tecfile.Zones.push_back(tecfile.Zones[0]);
	tecfile.Zones[1].Begin[0] = 5;
	tecfile.Zones[1].End[0] = 5;
	tecfile.Zones[1].Begin[1] = 1;
	tecfile.Zones[1].End[1] = 1;
	tecfile.Zones[1].Skip[0] = 2;
	tecfile.Zones[1].Skip[1] = 4;
	tecfile.Zones[1].ZoneName = "B";
	tecfile.Zones[1].Data[2] = TEC_DATA(w);
	tecfile.Zones[1].Auxiliary.clear();
	tecfile.Zones[1].add_auxiliary_data("Auxiliary3", "Auxiliary_test_1_2");
	tecfile.Zones[1].add_auxiliary_data("Auxiliary4", 3.1415);

	try
	{
		tecfile.set_echo_mode("full", "full");
		tecfile.write_plt();
		tecfile.last_log.write_echo();
		tecfile.last_log.write_json();
		tecfile.last_log.write_xml();
		tecfile.last_log.Zones[0].write_echo();
		tecfile.last_log.Zones[0].write_json();
		tecfile.last_log.Zones[0].write_xml();
	}
	catch (runtime_error err)
	{
		cerr << "runtime_error: " << err.what() << endl;
	}

	try
	{
		TEC_FILE_LOG log;
		tinyxml2::XMLDocument doc;
		doc.LoadFile("test_11.xml");
		log.read_xml(doc.FirstChildElement("File"));
		ofstream out("read.xml");
		out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
		log.write_xml(out);
		out.close();
	}
	catch (const std::exception &err)
	{
		cout << err.what() << endl;
	}

	delete[] x;
	delete[] y;
	delete[] z;
	delete[] w;
	return 0;
}