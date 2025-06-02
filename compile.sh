g++ -c /mnt/Github/projeto-final-ed/src/data.cpp -o /mnt/Github/projeto-final-ed/src/data.o
g++ -c /mnt/Github/projeto-final-ed/src/bst.cpp -o /mnt/Github/projeto-final-ed/src/bst.o
g++ -c /mnt/Github/projeto-final-ed/src/tree_utils.cpp -o /mnt/Github/projeto-final-ed/src/tree_utils.o
g++ -fsanitize=address /mnt/Github/projeto-final-ed/src/data.o /mnt/Github/projeto-final-ed/src/bst.o /mnt/Github/projeto-final-ed/src/tree_utils.o $1/$2.cpp -o out/$3