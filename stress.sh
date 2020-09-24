#!/bin/bash

generator=$1
judge=$2
solution=$3

for ((int i = 1; i <= 100; i++)) do
    $generator > input.txt
    $judge < input.txt > correct.txt
    $solution < input.txt > output.txt
    if ! cmp -s output.txt correct.txt
    then
        echo "Failed: wrong answer."
        break
    elif [ $? -ne 0 ]
        echo "Failed: runtime error."
        break
    fi
    echo "OK!"
done
