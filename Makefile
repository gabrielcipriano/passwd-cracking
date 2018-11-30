
enc:
	gcc -Wall BST3.c key.c encrypt.c -lm -o encrypt -g
	
dec:
	gcc -Wall BST3.c key.c decrypt.c -lm -o decrypt -g

brute:
	gcc -Wall BST3.c key.c brute.c -lm -o brute -g

clean:
	rm -f *.o a.out encrypt gmon.out prof
