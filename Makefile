# General
all: bst avl rbt clean

data.o: ./src/modules/data.cpp ./src/modules/data.h
	g++ -c ./src/modules/data.cpp -Wall -o data.o

./build: 
	mkdir -p ./build

clean:
	rm -f *.o

utils.o: ./src/utils/utils.cpp ./src/utils/utils.h
	g++ -c ./src/utils/utils.cpp -Wall -o utils.o

tree_utils.o: ./src/utils/tree_utils.cpp ./src/utils/tree_utils.h
	g++ -c ./src/utils/tree_utils.cpp -Wall -o tree_utils.o

# BST
bst: main_bst.o utils.o tree_utils.o bst.o data.o ./build
	g++ main_bst.o utils.o tree_utils.o bst.o data.o -o ./build/bst

main_bst.o: ./src/main_bst.cpp
	g++ -c ./src/main_bst.cpp -Wall -o main_bst.o

bst.o: ./src/modules/bst/bst.cpp ./src/modules/bst/bst.h
	g++ -c ./src/modules/bst/bst.cpp -Wall -o bst.o

# AVL
avl: main_bst.o utils.o tree_utils.o avl.o data.o ./build
	g++ main_bst.o utils.o tree_utils.o avl.o data.o -o ./build/avl

main_avl.o: ./src/main_avl.cpp
	g++ -c ./src/main_avl.cpp -Wall -o main_avl.o

avl.o: ./src/modules/avl/avl.cpp ./src/modules/avl/avl.h
	g++ -c ./src/modules/avl/avl.cpp -Wall -o avl.o

# RBT
rbt: main_rbt.o utils.o tree_utils.o rbt.o data.o ./build
	g++ main_rbt.o utils.o tree_utils.o rbt.o data.o -o ./build/rbt

main_rbt.o: ./src/main_rbt.cpp
	g++ -c ./src/main_rbt.cpp -Wall -o main_rbt.o

rbt.o: ./src/modules/rbt/rbt.cpp ./src/modules/rbt/rbt.h
	g++ -c ./src/modules/rbt/rbt.cpp -Wall -o rbt.o
