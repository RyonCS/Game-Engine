g++ -std=c++20 ./src/*.cpp -I./include -o myengine.so `pkg-config --libs --cflags sdl3` -Wl,-rpath,/usr/local/lib