
enc:
	gcc -Wall key.c encrypt.c -o encrypt

clean:
	rm -f *.o a.out encrypt gmon.out prof
