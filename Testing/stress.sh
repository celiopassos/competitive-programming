#!/bin/bash

generator=$1
judge=$2
solution=$3

while true;
do
    printf "Generating...\n"
    ./$generator > input.txt
    printf "\n"

    printf "Judge:\n"
    time ./$judge < input.txt > correct.txt
    retjudge=$?
    printf "\n"

    printf "Solution:\n"
    time ./$solution < input.txt > output.txt
    retsolution=$?
    printf "\n"

    if [ "$retsolution" -ne 0 ]
    then
        printf "Failed (solution): runtime error ($retsolution).\n"
        break
    elif ! cmp -s output.txt correct.txt
    then
        printf "Failed: wrong answer.\n"
        break
    fi

    printf "OK!\n"
    printf "===============================\n"
done
