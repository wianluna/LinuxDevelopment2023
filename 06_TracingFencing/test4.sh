#!/bin/bash

echo "Hello world!" > input.txt
strace -e fault=close:when=4:error=EROFS ./move input.txt output.txt 2> /dev/null

test $? == 7 && test -f input.txt && echo OK || echo Test 4 failed.
