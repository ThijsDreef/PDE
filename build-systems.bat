cmake --build build --target pde-systems --config Release
touch bin/lock.txt
cmake --install build --prefix .
rm bin/lock.txt