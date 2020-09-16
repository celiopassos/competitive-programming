#!/bin/bash

for ((int i = 1; i <= 100; i++)) do
    ./generator > input.txt
    ./solution < input.txt > output.txt
    ./judge < input.txt > correct.txt
    if ! cmp -s output.txt correct.txt
    then
        echo "Failed!"
        break
    fi
    echo "OK!"
done
