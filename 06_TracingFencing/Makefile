GENERATES = move  *.o *.out *.txt *.so

all: move

move: move.o
	cc $^ -o $@

%.o: %.c
	cc -fPIC -Wall -c $< -o $@

libprotect.so: libprotect.c
	cc -shared -o libprotect.so libprotect.c

test: move libprotect.so
	./test0.sh
	./test1.sh
	./test2.sh
	./test3.sh
	./test4.sh
	./test5.sh
	./test_protect.sh

clean:
	rm -f $(GENERATES)
