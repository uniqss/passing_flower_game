#!/bin/bash

# - install depends tools
# yum -y install git
# yum -y install gcc gcc-c++ autoconf libtool automake make
#



rm -rf bin

cd projects

rm -rf include
rm -rf lib






pushd spdlog
rm -rf bin
rm -rf build
rm -rf lib
sh clean_all.sh
popd

echo "clean spdlog done ==========================================================================="


pushd passing_flower_game
rm -rf bin
rm -rf build
rm -rf lib
sh clean_all.sh
popd

echo "clean passing_flower_game done ==========================================================================="

