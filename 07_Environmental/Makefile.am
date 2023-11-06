CFLAGS = -O0 -g

bin_PROGRAMS=rhasher

TESTS=test.sh

rhasher_SOURCES=rhasher.c

test.sh:
	echo "abcd" > input
	md5sum input | cut -d ' ' -f 1 > output
	echo 'MD5 "abcd' | ./rhasher | cut -d ' ' -f 2 | cmp output
	rm input output

	echo "abcd" > input
	sha1sum input | cut -d ' ' -f 1 > output
	echo 'SHA1 "abcd' | ./rhasher | cut -d ' ' -f 2 | cmp output
	rm input output

gitclean:
	git clean -xdf
