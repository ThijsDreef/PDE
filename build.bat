cmake --build build --config Release
touch bin/lock.txt
cmake --install build --prefix .
rm bin/lock.txt