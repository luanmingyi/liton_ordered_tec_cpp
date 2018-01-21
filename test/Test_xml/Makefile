CXX = g++
proname = Test_xml

%.o_debug:%.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $(@) $(<)

out: CXXFLAGS = -O2
out: CPPFLAGS = -DNDEBUG
out: $(proname).o lib_ot.o lib_txml.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $(@) $(^)

lib_ot.o: CXXFLAGS = -O2
lib_ot.o: CPPFLAGS = -DNDEBUG
lib_ot.o: ../../scr/ordered_tec.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $(@) $(<)

lib_txml.o: CXXFLAGS = -O2
lib_txml.o: CPPFLAGS = -DNDEBUG
lib_txml.o: ../../scr/tinyxml2.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $(@) $(<)

.PHONY: run
run: out
	-./out
	-cat *.txt

out_debug: CXXFLAGS = 
out_debug: CPPFLAGS = -D_DEBUG
out_debug: $(proname).o_debug lib_ot_debug.o lib_txml_debug.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $(@) $(^)

lib_ot_debug.o: CXXFLAGS =
lib_ot_debug.o: CPPFLAGS = -D_DEBUG
lib_ot_debug.o: ../../scr/ordered_tec.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $(@) $(<)

lib_txml_debug.o: CXXFLAGS =
lib_txml_debug.o: CPPFLAGS = -D_DEBUG
lib_txml_debug.o: ../../scr/tinyxml2.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $(@) $(<)

.PHONY: run_debug
run_debug: out_debug
	-./out_debug
	-cat *.txt

.PHONY: clean
clean:
	-rm *.o
	-rm *.o_debug
	-rm out
	-rm out_debug

.PHONY: clean_run
clean_run:
	-rm *.txt
	-rm *.plt
	-rm *.xml
	-rm *.json

.PHONY: clean_all
clean_all: clean clean_run
