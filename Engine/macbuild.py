import os

COMPILER = "g++"

SOURCE = "./src/*.cpp"

ARGUMENTS = "-D MAC -std=c++17 -shared -undefined dynamic_lookup `pkg-config --cflags --libs sdl2`"

LIBRARIES = "-F /Library/Frameworks `python3.11-config --ldflags` "

INCLUDE_DIR = "-I ./include/ -I./pybind11/include/ `python3.11 -m pybind11 --includes`"

EXECUTABLE = "mygameengine.so"

compileString = f"{COMPILER} {ARGUMENTS} -o {EXECUTABLE} {INCLUDE_DIR} {SOURCE} {LIBRARIES}"

print(compileString)

os.system(compileString)