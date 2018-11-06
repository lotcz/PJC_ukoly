DEST_ARCHIVE = tiny01.zip
DEST_ARCHIVE_FULL = $(DEST_ARCHIVE)
DEST_DIR_FULL = result

default: clean move_sources create_archive

build: clean build_o

build_o:
	g++ -std=c++11 tests-main.cpp tests-tiny-01.cpp -c

test:
	g++ -std=c++11 tests-main.o tests-tiny-01.o tiny-01.cpp -o tiny01-test
	tiny01-test.exe

t:
	g++ -std=c++11 tests-main.cpp tests-tiny-01.cpp tiny-01.cpp -o tiny01-test
	tiny01-test.exe

clean:
	if [ -f "tests-main.o" ];then rm "tests-main.o" -rf;fi
	if [ -d "$(DEST_DIR_FULL)" ];then rm "$(DEST_DIR_FULL)" -rf;fi
	if [ -f "$(DEST_ARCHIVE_FULL)" ];then rm "$(DEST_ARCHIVE_FULL)";fi

move_sources:
	mkdir "$(DEST_DIR_FULL)"
	xargs -a listfile.txt cp -t "$(DEST_DIR_FULL)"

create_archive:
	7z a -tzip $(DEST_ARCHIVE_FULL) "./$(DEST_DIR_FULL)/*"
