mkdir -p build/Desktop_Qt_6_8_3-Debug
cd build/Desktop_Qt_6_8_3-Debug
export Qt6_DIR=~/Qt/6.8.3/gcc_64/lib/cmake/Qt6
export Qt5_DIR=~/Qt/6.8.3/gcc_64/lib/cmake/Qt6
cmake ../..
cmake --build . --target all
