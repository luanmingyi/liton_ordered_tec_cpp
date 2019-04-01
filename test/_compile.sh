cmake -H. -B_build_unix -DCMAKE_PREFIX_PATH=$CPPLIB -DCMAKE_MODULE_PATH=$CPPLIB
cmake --build ./_build_unix
