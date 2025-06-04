all: bst clean

bst: main_bst.o utils.o tree_utils.o bst.o data.o ./build
	g++ main_bst.o utils.o tree_utils.o bst.o data.o -o ./build/bst

main_bst.o: ./src/main_bst.cpp
	g++ -c ./src/main_bst.cpp -Wall -o main_bst.o

utils.o: ./src/utils/utils.cpp ./src/utils/utils.h
	g++ -c ./src/utils/utils.cpp -Wall -o utils.o

tree_utils.o: ./src/utils/tree_utils.cpp ./src/utils/tree_utils.h
	g++ -c ./src/utils/tree_utils.cpp -Wall -o tree_utils.o

bst.o: ./src/modules/bst/bst.cpp ./src/modules/bst/bst.h
	g++ -c ./src/modules/bst/bst.cpp -Wall -o bst.o

data.o: ./src/modules/data.cpp ./src/modules/data.h
	g++ -c ./src/modules/data.cpp -Wall -o data.o

./build: 
	mkdir -p ./build

clean:
	rm -f *.o
	