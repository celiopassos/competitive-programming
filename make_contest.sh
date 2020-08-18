#!/bin/bash

mkdir $1

for X in {A..F};
do
    cp template.cpp $1/$X.cpp
done

cp -P bits $1/bits
