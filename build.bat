@echo off

cd projects


pushd spdlog
call build.bat
popd

echo "build spdlog done ==========================================================================="


cd passing_flower_game
call build.bat
cd ..

echo "build passing_flower_game done ==========================================================================="



rem pause