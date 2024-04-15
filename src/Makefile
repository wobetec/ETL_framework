MAKEFILE_DIR = $(dir $(lastword $(MAKEFILE_LIST)))

build:
	g++ \
		-c \
			$(MAKEFILE_DIR)/utils/datetime.cpp \
		-o \
			$(MAKEFILE_DIR)/framework.o \