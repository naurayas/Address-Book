OBJ:=$(patsubst %.c,%.o,$(wildcard *.c));
addressbook:$(OBJ)
	gcc -o $@ $^
clean:
	rm -f addressbook *.o