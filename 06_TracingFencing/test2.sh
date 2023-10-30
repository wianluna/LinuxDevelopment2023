#!/bin/bash

echo "Hello world!" > input.txt
strace -e trace=openat -e fault=openat:when=1:error=ENOENT -P output.txt ./move input.txt output.txt 2> /dev/null

test $? == 3 && test -f input.txt && echo OK || echo Test 2 failed.
