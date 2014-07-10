./bin/main.exe:./tmp/main.o ./tmp/bubbleSort.o ./tmp/init.o ./tmp/show.o ./tmp/chooseSort.o ./tmp/insertSort.o ./tmp/quickSort.o ./tmp/swap.o
	gcc -o ./bin/main.exe ./tmp/main.o ./tmp/bubbleSort.o ./tmp/init.o ./tmp/show.o ./tmp/chooseSort.o ./tmp/insertSort.o ./tmp/quickSort.o ./tmp/swap.o  -I./include
./tmp/main.o:./src/main.c
	gcc -o ./tmp/main.o -c ./src/main.c -I./include
./tmp/bubbleSort.o: ./src/bubbleSort.c
	gcc -o ./tmp/bubbleSort.o -c ./src/bubbleSort.c -I./include
./tmp/init.o:./src/init.c
	gcc -o ./tmp/init.o -c ./src/init.c -I./include
./tmp/show.o:./src/show.c
	gcc -o ./tmp/show.o -c ./src/show.c -I./include
./tmp/chooseSort.o:./src/chooseSort.c
	gcc -o ./tmp/chooseSort.o -c ./src/chooseSort.c -I./include
./tmp/insertSort.o:./src/insertSort.c
	gcc -o ./tmp/insertSort.o -c ./src/insertSort.c -I./include
./tmp/quickSort.o:./src/quickSort.c
	gcc -o ./tmp/quickSort.o -c ./src/quickSort.c -I./include
./tmp/swap.o:./src/swap.c
	gcc -o ./tmp/swap.o -c ./src/swap.c -I./include
