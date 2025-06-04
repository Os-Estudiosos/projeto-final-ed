all: bst clean

bst: main_bst.o utils.o tree_utils.o bst.o data.o
	g++ main_bst.o utils.o tree_utils.o bst.o data.o -o bst

main_bst.o: ./src/main_bst.cpp
	g++ -c ./src/main_bst.cpp -o main_bst.o

utils.o: ./src/utils/utils.cpp ./src/utils/utils.h
	g++ -c ./src/utils/utils.cpp -o utils.o

tree_utils.o: ./src/utils/tree_utils.cpp ./src/utils/tree_utils.h
	g++ -c ./src/utils/tree_utils.cpp -o tree_utils.o

bst.o: ./src/modules/bst/bst.cpp ./src/modules/bst/bst.h
	g++ -c ./src/modules/bst/bst.cpp -o bst.o

data.o: ./src/modules/data.cpp ./src/modules/data.h
	g++ -c ./src/modules/data.cpp -o data.o

clean:
	rm -f *.o
	