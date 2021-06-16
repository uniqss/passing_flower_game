#!/bin/bash

# - install depends tools
# yum -y install git
# yum -y install gcc gcc-c++ autoconf libtool automake make
#

cd libevent-2.1.12-stable

BAT_BUILD_TYPE=Release

rm -rf build
mkdir -p build
cd build


#cmake -DEVENT__DISABLE_OPENSSL=ON -DEVENT__LIBRARY_TYPE=STATIC ..
cmake -DEVENT__DISABLE_OPENSSL=ON -DEVENT__LIBRARY_TYPE=STATIC -DBUILD_TESTING=OFF -DEVENT__DISABLE_SAMPLES=ON -DEVENT__DISABLE_TESTS=ON -DEVENT__DISABLE_BENCHMARK=ON ..
#cmake --build . --config Release
cmake --build . --config $BAT_BUILD_TYPE


cd ..

mkdir -p ../../include/
cp -R ./include/* ../../include/

mkdir -p ../../lib/
cp -R ./build/lib/* ../../lib/

mkdir -p ../../include/
cp -R ./build/include/* ../../include/



cd ..

# echo continue && read -n 1
