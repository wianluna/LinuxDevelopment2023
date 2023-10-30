#!/bin/bash

echo "Hello world!" > input.txt
strace -e fault=close:when=1:error=EROFS -P input.txt ./move input.txt output.txt 2> /dev/null

test $? == 6 && test -f input.txt && echo OK || echo Test 5 failed.
