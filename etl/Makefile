MAKEFILE_DIR = $(dir $(lastword $(MAKEFILE_LIST)))

build:
	g++ \
		-c \
			$(MAKEFILE_DIR)/src/DF_CadeAnalytics.cpp \
		-o  \
			$(MAKEFILE_DIR)/etl.o \

build_framework:
	make -f ../src/Makefile build

all: build build_framework 
	g++ $(MAKEFILE_DIR)/main.cpp $(MAKEFILE_DIR)/etl.o ../src/framework.o -o $(MAKEFILE_DIR)/main.out
