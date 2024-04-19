MAKEFILE_DIR = $(dir $(lastword $(MAKEFILE_LIST)))

build:
	g++ \
		-c \
			$(MAKEFILE_DIR)/src/DF_CadeAnalytics.cpp \
		-o  \
			$(MAKEFILE_DIR)/etl.o \

build_framework:
	make -f ../src/Makefile build

main:
	g++ \
		main.cpp \

		-L../src/lib \
		-l:framework.a \
		
		-o \
			test.out \

