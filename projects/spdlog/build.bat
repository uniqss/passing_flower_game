cd libevent-2.1.12-stable

set BAT_BUILD_TYPE=Release


rmdir /S /Q build
mkdir build
cd build


rem cmake -DEVENT__DISABLE_OPENSSL=ON -DEVENT__LIBRARY_TYPE=STATIC -DEVENT__MSVC_STATIC_RUNTIME=ON  -A x64 ..
cmake -DEVENT__DISABLE_OPENSSL=ON -DEVENT__LIBRARY_TYPE=STATIC -DEVENT__MSVC_STATIC_RUNTIME=ON -DBUILD_TESTING=OFF -DEVENT__DISABLE_SAMPLES=ON -DEVENT__DISABLE_TESTS=ON -DEVENT__DISABLE_BENCHMARK=ON  -A x64 ..
rem cmake --build . --config Release
cmake --build . --config %BAT_BUILD_TYPE%


cd ..

xcopy /Y /S /Q .\include\* ..\..\include\
xcopy /Y /S /Q .\build\lib\%BAT_BUILD_TYPE%\* ..\..\lib\

xcopy /Y /S /Q .\build\include\* ..\..\include\

cd ..

rem pause