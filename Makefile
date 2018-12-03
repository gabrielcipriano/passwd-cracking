
enc:
	gcc -Wall BST3.c key.c encrypt.c -o encrypt -g
	
dec:
	gcc -Wall trie.c key.c decrypt.c -o decrypt -g

brute:
	gcc -Wall trie.c key.c brute.c -o brute -g

clean:
	rm -f *.o a.out encrypt gmon.out prof
