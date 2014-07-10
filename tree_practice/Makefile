./bin/main:./tmp/main.o ./tmp/create_tree.o ./tmp/tree_struct.o ./tmp/tree_travel.o
	gcc -g -o ./bin/main ./tmp/main.o ./tmp/create_tree.o ./tmp/tree_struct.o ./tmp/tree_travel.o -I./include
./tmp/main.o:./src/main.c
	gcc -o ./tmp/main.o -c ./src/main.c -I./include
./tmp/create_tree.o:./src/create_tree.c
	gcc -o ./tmp/create_tree.o -c ./src/create_tree.c -I./include
./tmp/tree_struct.o:./src/tree_struct.c
	gcc -o ./tmp/tree_struct.o -c ./src/tree_struct.c -I./include
./tmp/tree_travel.o:./src/tree_travel.c
	gcc -o ./tmp/tree_travel.o -c ./src/tree_travel.c -I./include
