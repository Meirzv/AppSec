default: prog

get-deps:
	# Assuming Debian or Ubuntu here
	sudo apt-get install -y build-essential check

dictionary.o: dictionary.c
	gcc -Wall -c dictionary.c dictionary.h

spell.o: spell.c
	gcc -Wall -c spell.c

test.o: test_main.c
	gcc -Wall -c test_main.c

main.o: main.c
	gcc -Wall -c main.c

test: dictionary.o spell.o test_main.o
	gcc -Wall -o test_main test_main.o spell.o dictionary.o -lcheck -lm -lrt -lpthread -lsubunit
	./test_main

test1: dictionary.o spell.o test_main1.o
	gcc -Wall -o test_main1 test_main1.o spell.o dictionary.o -lcheck -lm -lrt -lpthread -lsubunit
	./test_main1

test2: dictionary.o spell.o test_main2.o
	gcc -Wall -o test_main2 test_main2.o spell.o dictionary.o -lcheck -lm -lrt -lpthread -lsubunit
	./test_main2

test3: dictionary.o spell.o test_main3.o
	gcc -Wall -o test_main3 test_main3.o spell.o dictionary.o -lcheck -lm -lrt -lpthread -lsubunit
	./test_main3

test4: dictionary.o spell.o test_main4.o
	gcc -Wall -o test_main4 test_main4.o spell.o dictionary.o -lcheck -lm -lrt -lpthread -lsubunit
	./test_main4

test5: dictionary.o spell.o test_main5.o
	gcc -Wall -o test_main5 test_main5.o spell.o dictionary.o -lcheck -lm -lrt -lpthread -lsubunit
	./test_main5

prog: dictionary.o spell.o main.o
	gcc -Wall -o spell_check dictionary.o spell.o main.o

clean:
	rm dictionary.o spell.o main.o test_main.o test_main1.o test_main2.o spell_check 

cleanall:clean
	rm spell_check