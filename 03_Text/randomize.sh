#!/bin/sh

DELAY=0
if [[ $# != 0 ]] ;
then
    DELAY=$1
fi

TMP_FILE=./tmp_storage

i=1;
while IFS= read line; do
    for (( j=0; j<${#line}; j++ )); do
        cur=${line:$j:1}
        cur_byte=$(echo $cur | hexdump -e '16/1 "%02x " "\n"')
        if [[ $cur_byte != "20" ]] & [[ $cur_byte != "0a" ]]; then
            echo $i $j $cur >> $TMP_FILE
        fi
    done
    (( i++ ))
done

shuf $TMP_FILE > $TMP_FILE
tput clear

while read row col char; do
    tput cup $row $col
    echo "$char"
    sleep $DELAY
done <${TMP_FILE}

rm ${TMP_FILE}