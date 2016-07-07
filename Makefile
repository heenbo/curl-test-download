
main:main.o
	gcc $^ -o $@ -lcurl

main.o:main.c
	gcc -c $< -o $@

clean:
	-rm *.o main *.txt
