cmake .
make

rm cmake_install.cmake
rm Makefile

if [ -d "build" ]; then
    rm -r build
fi