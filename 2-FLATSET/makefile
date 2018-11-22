PROJECT_NAME = flatset
ARCHIVE_NAME = $(PROJECT_NAME).zip
DEST_DIR = result
COMPILER = x86_64-w64-mingw32-g++.exe#mingw32-g++.exe #g++

default: create_archive

build:
	if [ -f "tests-main.o" ];then rm "tests-main.o";fi
	if [ -f "tests-helpers.o" ];then rm "tests-helpers.o";fi
	$(COMPILER) -g -std=c++14 tests-main.cpp tests-helpers.cpp -c

test:
	$(COMPILER) -g -std=c++14 tests-main.o tests-helpers.o test_$(PROJECT_NAME).cpp $(PROJECT_NAME).hpp -o $(PROJECT_NAME)-test
	$(PROJECT_NAME)-test.exe

debug:
	gdb $(PROJECT_NAME)-test.exe

mem:
	drmemory $(PROJECT_NAME)-test.exe

memtest: test mem

simple:
	$(COMPILER) -g -std=c++14 tests-main.o tests-helpers.o $(PROJECT_NAME).hpp simple.cpp -o simple
	simple.exe

main:
	$(COMPILER) -g -std=c++14 $(PROJECT_NAME).hpp main.cpp -o $(PROJECT_NAME)
	$(PROJECT_NAME).exe

create_archive:
	if [ -f "$(ARCHIVE_NAME)" ];then rm "$(ARCHIVE_NAME)";fi
	if [ -d "$(DEST_DIR)" ];then rm "$(DEST_DIR)" -rf;fi
	mkdir "$(DEST_DIR)"
	xargs -a listfile.txt cp -t "$(DEST_DIR)"
	7z a -tzip $(ARCHIVE_NAME) "./$(DEST_DIR)/*"
	rm "$(DEST_DIR)" -rf
