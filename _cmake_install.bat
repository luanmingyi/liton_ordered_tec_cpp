cmake -H. -B_build_win32 -DCMAKE_INSTALL_PREFIX=%CPPLIB%\ordered_tec
cmake --build _build_win32 --config Release --target INSTALL
