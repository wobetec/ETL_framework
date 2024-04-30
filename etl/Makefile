
clear:
	rm -f *.out && \
	rm -f *.db && \
	rm -f *.txt && \
	rm -f *.db-journal

main: clear
	g++ \
		main.cpp \
		../src/datetime.cpp \
		../src/repodata.cpp \
		-l sqlite3\
		-o \
			main.out

main_run: main
	./main.out