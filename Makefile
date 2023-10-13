build/SDES: src/SDES.c src/main.c include/SDES.h
	g++ src/main.c src/SDES.c -Iinclude -o build/SDES
build/SDES.o: src/SDES.c include/SDES.h
	gcc -g -O -c src/SDES.c -Iinclude  -o build/SDES.o
test/test: build/SDES.o test/test.c include/SDES.h
	g++ test/test.c build/SDES.o -Iinclude -o test/test  -lgtest -lpthread
test: test/test
	./test/test
run: build/SDES
	./build/SDES 1819 77