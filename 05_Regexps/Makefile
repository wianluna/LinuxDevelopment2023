GENERATES = esub  *.o *.out

all: esub

esub: esub.o
	cc $^ -o $@

%.o: %.c
	cc -fPIC -Wall -c $< -o $@

test: esub
	./esub 'abcd' '1234' 'asdf' >esub.out
	echo 'asdf' | sed -E 's/abcd/1234/' >sed.out
	cmp esub.out sed.out

	./esub 'qr(t)y' '12\1' '000qrty123' >esub.out
	echo '000qrty123' | sed -E 's/qr(t)y/12\1/' >sed.out
	cmp esub.out sed.out

	./esub 's(w.*i)f' '@\1#' '1sdgsw111ehif0jyj' >esub.out
	echo '1sdgsw111ehif0jyj' | sed -E 's/s(w.*i)f/@\1#/' >sed.out
	cmp esub.out sed.out

clean:
	rm -f $(GENERATES)
