build/SDES: build/SDES.o src/main.c 
	gcc src/main.c build/SDES.o -Iinclude -o build/SDES
build/SDES.o: src/SDES.c include/SDES.h build
	gcc -g -O -c src/SDES.c -Iinclude  -o build/SDES.o
test/test: build/SDES.o test/test.c build
	g++ test/test.c build/SDES.o -Iinclude -o test/test  -lgtest -lpthread
build: 
	mkdir build
test: test/test
	./test/test
run: build/SDES
	./build/SDES 1819 77
clean:
	rm -r build
