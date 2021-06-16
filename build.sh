#!/bin/bash

# - install depends tools
# yum -y install git
# yum -y install gcc gcc-c++ autoconf libtool automake make
#



cd projects


cd spdlog
sh build.sh
cd ..

echo "build spdlog done ==========================================================================="


cd passing_flower_game
sh build.sh
cd ..

echo "build passing_flower_game done ==========================================================================="




# echo continue && read -n 1
