echo "Hello world!" > PROTECT_input.txt
LD_PRELOAD=`pwd`/libprotect.so ./move PROTECT_input.txt output.txt 2> /dev/null
test -f PROTECT_input.txt && test -f output.txt && echo OK || echo Test PROTECT failed.
