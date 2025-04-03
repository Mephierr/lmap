mkdir build/gui_debug
cd build/gui_debug/
cmake  ../.. -DBUILD_WITH_QT=ON
cmake --build . --target all
./lmap
