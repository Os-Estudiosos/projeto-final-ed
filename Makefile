# General
all: BST testsBst AVL #testsAvl

bst: BST testsBst

avl: AVL #testsAvl

OBJ = ./build/obj
# BST
BST: $(OBJ)/main_bst.o $(OBJ)/utils.o $(OBJ)/tree_utils.o $(OBJ)/bst.o $(OBJ)/data.o
	g++ $(OBJ)/main_bst.o $(OBJ)/utils.o $(OBJ)/tree_utils.o $(OBJ)/bst.o $(OBJ)/data.o -o ./build/bst

testsBst: $(OBJ)/test_bst.o $(OBJ)/utils.o $(OBJ)/tree_utils.o $(OBJ)/bst.o $(OBJ)/data.o | ./build
	g++ $(OBJ)/test_bst.o $(OBJ)/utils.o $(OBJ)/tree_utils.o $(OBJ)/bst.o $(OBJ)/data.o -o ./build/testsBst

build/obj/test_bst.o: ./src/tests/test_bst.cpp | $(OBJ)
	g++ -c ./src/tests/test_bst.cpp -Wall -o $(OBJ)/test_bst.o

build/obj/main_bst.o: ./src/main_bst.cpp | $(OBJ)
	g++ -c ./src/main_bst.cpp -Wall -o $(OBJ)/main_bst.o

build/obj/bst.o: ./src/modules/bst/bst.cpp ./src/modules/bst/bst.h | $(OBJ)
	g++ -c ./src/modules/bst/bst.cpp -Wall -o $(OBJ)/bst.o

# AVL
AVL: $(OBJ)/main_avl.o $(OBJ)/utils.o $(OBJ)/tree_utils.o $(OBJ)/avl.o $(OBJ)/data.o
	g++ $(OBJ)/main_avl.o $(OBJ)/utils.o $(OBJ)/tree_utils.o $(OBJ)/avl.o $(OBJ)/data.o -o ./build/avl

#testsAvl: $(OBJ)/test_avl.o $(OBJ)/utils.o $(OBJ)/tree_utils.o $(OBJ)/avl.o $(OBJ)/data.o | ./build
#	g++ $(OBJ)/test_avl.o $(OBJ)/utils.o $(OBJ)/tree_utils.o $(OBJ)/avl.o $(OBJ)/data.o -o ./build/testsAvl

#build/obj/test_avl.o: ./src/tests/test_avl.cpp | $(OBJ)
#	g++ -c ./src/tests/test_avl.cpp -Wall -o $(OBJ)/test_avl.o

build/obj/main_avl.o: ./src/main_avl.cpp | $(OBJ)
	g++ -c ./src/main_avl.cpp -Wall -o $(OBJ)/main_avl.o

build/obj/avl.o: ./src/modules/avl/avl.cpp ./src/modules/avl/avl.h | $(OBJ)
	g++ -c ./src/modules/avl/avl.cpp -Wall -o $(OBJ)/avl.o

#imports
build/obj/data.o: ./src/modules/data.cpp ./src/modules/data.h | $(OBJ)
	g++ -c ./src/modules/data.cpp -Wall -o $(OBJ)/data.o

build/obj/utils.o: ./src/utils/utils.cpp ./src/utils/utils.h | $(OBJ)
	g++ -c ./src/utils/utils.cpp -Wall -o $(OBJ)/utils.o

build/obj/tree_utils.o: ./src/utils/tree_utils.cpp ./src/utils/tree_utils.h | $(OBJ)
	g++ -c ./src/utils/tree_utils.cpp -Wall -o $(OBJ)/tree_utils.o

./build/obj: 
	mkdir -p ./build
	mkdir -p ./build/obj

clean:
	rm -f *.o