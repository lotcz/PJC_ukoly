DEST_ARCHIVE = initB.zip
DEST_ARCHIVE_FULL = $(DEST_ARCHIVE)
DEST_DIR_FULL = result

build: clean move_sources create_archive

test:
	g++ -o initb tests-factorial.cpp
	initb.exe

clean:
	if [ -d "$(DEST_DIR_FULL)" ];then rm "$(DEST_DIR_FULL)" -rf;fi
	if [ -f "$(DEST_ARCHIVE_FULL)" ];then rm "$(DEST_ARCHIVE_FULL)";fi

move_sources:
	mkdir "$(DEST_DIR_FULL)"
	xargs -a listfile.txt cp -t "$(DEST_DIR_FULL)"

create_archive:
	7z a -tzip $(DEST_ARCHIVE_FULL) "./$(DEST_DIR_FULL)/*"
