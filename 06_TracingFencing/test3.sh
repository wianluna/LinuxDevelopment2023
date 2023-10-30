#!/bin/bash

echo "Hello world!" > input.txt
strace -e unlink -e fault=unlink:error=ENOENT ./move input.txt output.txt 2> /dev/null

test $? == 8 && test -f input.txt && echo OK || echo Test 3 failed.
