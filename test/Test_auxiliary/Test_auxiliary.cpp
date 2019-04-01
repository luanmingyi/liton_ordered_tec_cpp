# include <iostream>
# include <string>
#include <typeinfo>
using namespace std;
# include "ordered_tec.h"
using namespace liton_ot;

template<typename TEC, typename NUMT>
void test_get_aux(TEC &tec, const std::string &name)
{
	try
	{
		NUMT data;
		tec.get_auxiliary_data(name, data);
		cout << typeid(data).name() << ": " << data << endl;
	}
	catch (runtime_error err)
	{
		cerr << "runtime_error: " << err.what() << endl;
	}
}

int main(int argc, char** argv)
{
	TEC_FILE tecfile("test", ".", "test");
	tecfile.add_auxiliary_data("Auxiliary1", "Auxiliary_test_1_ds");
	tecfile.add_auxiliary_data("Auxiliary2", 3.14);
	tecfile.add_auxiliary_data("Auxiliary3", 2);
	tecfile.Zones.push_back(TEC_ZONE("A"));
	tecfile.Zones[0].add_auxiliary_data("Auxiliary4", "2e-2");
	tecfile.Zones[0].add_auxiliary_data("Auxiliary5", 3.1415e4);
	tecfile.Zones[0].add_auxiliary_data("Auxiliary6", 10);

	test_get_aux<TEC_FILE, string>(tecfile, "no_var");
	test_get_aux<TEC_FILE, string>(tecfile, "Auxiliary1");
	test_get_aux<TEC_FILE, double>(tecfile, "Auxiliary2");
	test_get_aux<TEC_FILE, int>(tecfile, "Auxiliary3");

	test_get_aux<TEC_ZONE, string>(tecfile.Zones[0], "no_var");
	test_get_aux<TEC_ZONE, string>(tecfile.Zones[0], "Auxiliary4");
	test_get_aux<TEC_ZONE, double>(tecfile.Zones[0], "Auxiliary4");
	test_get_aux<TEC_ZONE, double>(tecfile.Zones[0], "Auxiliary5");
	test_get_aux<TEC_ZONE, int>(tecfile.Zones[0], "Auxiliary6");

	return 0;
}