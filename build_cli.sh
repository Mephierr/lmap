mkdir -p build/cli_debug
cd build/cli_debug
cmake ../.. -DBUILD_WITH_QT=OFF
cmake --build . --target all
./lmap
