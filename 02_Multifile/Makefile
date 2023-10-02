GENERATES = prog prog-a prog-so *.a *.o *.so *.out

all: prog prog-a prog-so

prog: const.o fun.o prog.o
	cc $^ -o $@

prog-a: prog.o liboutput_static.a
	cc -L. $< -o $@ -loutput_static

prog-so: prog.o liboutput.so
	cc -L. $< -o $@ -loutput

%.o: %.c
	cc -fPIC -c $< -o $@

liboutput_static.a:	fun.o const.o
	ar -rcs $@ $^

liboutput.so: fun.o const.o
	cc -shared $^ -o $@

test: test1 test2 test3

test1: prog prog-a prog-so
	@echo Testing without params
	./prog > $@.out 2> /dev/null
	./prog-a > $@-a.out 2> /dev/null
	LD_LIBRARY_PATH=`pwd` ./prog-so > $@-so.out 2> /dev/null
	cmp $@.out $@-a.out
	cmp $@-a.out $@-so.out
	cmp $@.out $@-so.out

test2: prog prog-a prog-so
	@echo Testing with 1 param
	./prog a > $@.out 2> /dev/null
	./prog-a a > $@-a.out 2> /dev/null
	LD_LIBRARY_PATH=`pwd` ./prog-so a > $@-so.out 2> /dev/null
	cmp $@.out $@-a.out
	cmp $@-a.out $@-so.out
	cmp $@.out $@-so.out

test3: prog prog-a prog-so
	@echo Testing with 3 params
	./prog a b c > $@.out 2> /dev/null
	./prog-a a b c > $@-a.out 2> /dev/null
	LD_LIBRARY_PATH=`pwd` ./prog-so a b c > $@-so.out 2> /dev/null
	cmp $@.out $@-a.out
	cmp $@-a.out $@-so.out
	cmp $@.out $@-so.out

clean:
	rm -f $(GENERATES)
