test:
	g++ \
		test.cpp \
		../src/datetime.cpp \
		../src/repodata.cpp \
		-l sqlite3\
		-o \
			test.out

test_run: test
	./test.out