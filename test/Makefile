subfolder = Test_single_zone Test_two_zone Test_grid_solution Test_multi_file Test_data_type Test_zone_size Test_using_time Test_echo_in_file Test_echo_mode Test_log Test_xml

out_flag = $(foreach n,$(subfolder),$(n).out_flag)
%.out_flag:
	echo $(@) > $(@)
	cd $(basename $(@)) && $(MAKE) out
out:$(out_flag)
	rm *.out_flag

run_flag = $(foreach n,$(subfolder),$(n).run_flag)
%.run_flag:
	echo $(@) > $(@)
	cd $(basename $(@)) && $(MAKE) run
run:$(run_flag)
	rm *.run_flag

out_debug_flag = $(foreach n,$(subfolder),$(n).out_debug_flag)
%.out_debug_flag:
	echo $(@) > $(@)
	cd $(basename $(@)) && $(MAKE) out_debug
out_debug:$(out_debug_flag)
	rm *.out_debug_flag

run_debug_flag = $(foreach n,$(subfolder),$(n).run_debug_flag)
%.run_debug_flag:
	echo $(@) > $(@)
	cd $(basename $(@)) && $(MAKE) run_debug
run_debug:$(run_debug_flag)
	rm *.run_debug_flag

clean_flag = $(foreach n,$(subfolder),$(n).clean_flag)
%.clean_flag:
	echo $(@) > $(@)
	cd $(basename $(@)) && $(MAKE) clean
clean:$(clean_flag)
	rm *.clean_flag

clean_run_flag = $(foreach n,$(subfolder),$(n).clean_run_flag)
%.clean_run_flag:
	echo $(@) > $(@)
	cd $(basename $(@)) && $(MAKE) clean_run
clean_run:$(clean_run_flag)
	rm *.clean_run_flag

clean_all_flag = $(foreach n,$(subfolder),$(n).clean_all_flag)
%.clean_all_flag:
	echo $(@) > $(@)
	cd $(basename $(@)) && $(MAKE) clean_all
clean_all:$(clean_all_flag)
	rm *.clean_all_flag
