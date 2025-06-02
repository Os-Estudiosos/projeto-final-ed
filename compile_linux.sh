path=/mnt/Github/projeto-final-ed/src
g++ -c $path/modules/data.cpp -o $path/objects/data.o
g++ -c $path/modules/bst/bst.cpp -o $path/objects/bst.o
g++ -c $path/utils/tree_utils.cpp -o $path/objects/tree_utils.o
g++ -c $path/utils/utils.cpp -o $path/objects/utils.o
g++ -fsanitize=address $path/objects/data.o $path/objects/bst.o $path/objects/tree_utils.o $path/objects/utils.o $path/main_$1.cpp -o out/$1