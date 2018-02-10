# Usage {#usage}

## Download and Configuration
You only need to download all folders in `scr`  for using this package.

Before using it in your project, you need to copy these folders into your project directory or somewhere else to make sure that the complier could find it. 

## Coding
The Tecplot file consists of zones and data are storage in zone. Zones describe different set of data in space or in time. All the numbers of data in different zones in one file are same. Auxiliary data is extra data attached to file or zone which can be seen and used in Tecplot.

There are six classes usually used included in the `liton_ot` namespace. They are `TEC_FILE`, `TEC_ZONE`, `TEC_DATA` and correspondingly `TEC_FILE_LOG`, `TEC_ZONE_LOG`, `TEC_DATA_LOG` used to contain log.

To use the package, first you need some including and namespace declaration.
```
# include "ordered_tec.h"
using namespace liton_ot;
```

Then you need to declare a `TEC_FILE` object and set its properties. The property `Variables` is a string vector containing the variables' name which is required.
```
TEC_FILE tec_file;
tec_file.Variables.push_back("x");
tec_file.Variables.push_back("y");
tec_file.Variables.push_back("z");
```
You can also set some other properties **optionally**.
```
tec_file.FileName = "Test";
tec_file.Title = "Test";
tec_file.add_auxiliary_data("a_data_1","test01");
tec_file.add_auxiliary_data("a_data_2",0.5);
```

Then attach a `TEC_ZONE` object to the file and set its properties.
```
tec_file.Zones.push_back(TEC_ZONE());
//x, y, z are the point to the data, the size of all data is 10 by 30
tec_file.Zones[0].Max[0] = 10;
tec_file.Zones[0].Max[1] = 30;
tec_file.Zones[0].Data.push_back(TEC_DATA(x)); //auto recognition point type
tec_file.Zones[0].Data.push_back(TEC_DATA(y));
tec_file.Zones[0].Data.push_back(TEC_DATA(z));
```

You can also set some other properties **optionally**.
```
tec_file.Zones[0].ZoneName = "zone_1";
tec_file.Zones[0].StrandId = 0;
tec_file.Zones[0].SolutionTime = 0.1;
tec_file.Zones[0].Begin[1] = 1; //begin of data offset 1 in second dimension
tec_file.Zones[0].End[0] = 2; //end of data offset 2 in first dimension
tec_file.Zones[0].Skip[0] = 2; //skip to write data by 2 in first dimension
tec_file.Zones[0].add_auxiliary_data("a_data_1","test01");
tec_file.Zones[0].add_auxiliary_data("a_data_2",0.5);
```

Before write data, you can set echo mode **optionally**.
```
tec_file.set_echo_mode("full","full");
```

And write data.
```
tec_file.write_plt();
```

Now you can get log in `tec_file`'s property `last_log`. Also you can write the log in a xml file.
```
tec_file.last_log.write_xml();
```

## Compile
The file functions are based on 32 bit, so it is not supported to write big file over 2G. Try to split data into small files.

## Example list
* Test_single_zone
* Test_two_zone
* Test_grid_solution
* Test_multi_file

\example ../test/Test_single_zone/Test_single_zone.cpp
one simple example with single zone.
\example ../test/Test_two_zone/Test_two_zone.cpp
an example with two zones in one file.
\example ../test/Test_grid_solution/Test_grid_solution.cpp
an example with grid and solution file.
\example ../test/Test_multi_file/Test_multi_file.cpp
an example with multiply files.
\example ../test/Test_data_type/Test_data_type.cpp
an example with different data types.
