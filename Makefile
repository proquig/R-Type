RM    := rm -rf
MKDIR := mkdir -p

all: ./build/Makefile
	$(MAKE) -C build

./build/Makefile:
	($(MKDIR) build > /dev/null)
	(cd build > /dev/null 2>&1 && cmake ..)

distclean: ./build/Makefile
	$(MAKE) --silent -C build clean || true
	@for subdir in $(shell find ./build/ -name 'CMakeFiles' -printf '%h\n'); do \
		echo "Cleaning $$subdir"	;\
		$(RM) $$subdir/Makefile		;\
		$(RM) $$subdir/CMake*		;\
		$(RM) $$subdir/cmake.*		;\
		$(RM) $$subdir/*.cmake		;\
		$(RM) $$subdir/*.txt		;\
	done
