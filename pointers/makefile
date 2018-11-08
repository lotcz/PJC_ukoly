PROJECT_NAME = pointers
DEST_DIR = result
COMPILER = x86_64-w64-mingw32-g++.exe#mingw32-g++.exe #g++

default: clean build

build:
	$(COMPILER) -std=c++14 main.cpp -o $(PROJECT_NAME)

clean:
	if [ -f "$(PROJECT_NAME).exe" ];then rm "$(PROJECT_NAME).exe";fi
