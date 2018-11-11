PROJECT_NAME = tiny-04
ARCHIVE_NAME = $(PROJECT_NAME).zip
DEST_DIR = result
COMPILER = x86_64-w64-mingw32-g++.exe#mingw32-g++.exe #g++

default: clean create_archive

build: clean build_o

build_o:
	$(COMPILER) -std=c++14 tests-main.cpp tests-$(PROJECT_NAME).cpp -c

test:
	$(COMPILER) -g -std=c++14 tests-main.o tests-$(PROJECT_NAME).o $(PROJECT_NAME).cpp -o $(PROJECT_NAME)-test
	$(PROJECT_NAME)-test.exe

mem:
	drmemory $(PROJECT_NAME)-test.exe

memtest: test mem

simple:
	$(COMPILER) -g -std=c++14 $(PROJECT_NAME).cpp main.cpp -o $(PROJECT_NAME)
	$(PROJECT_NAME).exe

clean:
	if [ -f "tests-main.o" ];then rm "tests-main.o";fi
	if [ -f "tests-$(PROJECT_NAME).o" ];then rm "tests-$(PROJECT_NAME).o";fi
	if [ -f "$(ARCHIVE_NAME)" ];then rm "$(ARCHIVE_NAME)";fi

create_archive:
	if [ -d "$(DEST_DIR)" ];then rm "$(DEST_DIR)" -rf;fi
	mkdir "$(DEST_DIR)"
	xargs -a listfile.txt cp -t "$(DEST_DIR)"
	7z a -tzip $(ARCHIVE_NAME) "./$(DEST_DIR)/*"
	rm "$(DEST_DIR)" -rf
