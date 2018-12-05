
enc:
	gcc -Wall list.c tst.c key.c encrypt.c -o encrypt -g
	
dec:
	gcc -Wall list.c tst.c key.c decrypt.c -o decrypt -g

brute:
	gcc -Wall key.c brute.c -o brute -g

clean:
	rm -f *.o a.out encrypt gmon.out prof
