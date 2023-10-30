#!/bin/bash

echo "Hello world!" > input.txt
./move input.txt output.txt

test $? == 0 && test -f output.txt && !(test -f input.txt) && echo OK || echo Test 0 failed.
