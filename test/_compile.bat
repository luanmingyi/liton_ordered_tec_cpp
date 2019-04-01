cmake -H. -B_build_win32 -DCMAKE_PREFIX_PATH=%CPPLIB% -DCMAKE_MODULE_PATH=%CPPLIB%
cmake --build _build_win32
