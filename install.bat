cmake -G "Visual Studio 17" -S . -B build -A x64 -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
