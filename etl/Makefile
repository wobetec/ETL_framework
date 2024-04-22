MAKEFILE_DIR = $(dir $(lastword $(MAKEFILE_LIST)))

build:
	g++ \
		-c \
			$(MAKEFILE_DIR)/src/DF_CadeAnalytics.cpp \
		-o  \
			$(MAKEFILE_DIR)/etl.o \

build_framework:
	make -f ../src/Makefile build

main: build_framework
	g++ \
		main.cpp \

		-L../src/lib \
		-l:framework.a \
		
		-o \
			test.out \

test: 
	g++ \
		main.cpp \
		../src/datetime.cpp \
		../src/repodata.cpp \
		-l sqlite3\
		-o \
			main.out
