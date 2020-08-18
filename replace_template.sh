#!/bin/bash

template=$1
file=$2

tempfile=$(mktemp)
temptemplate=$(mktemp)
tempend=$(mktemp)

sed 's/^.*\(\/\/ xz.*}\).*/\1/' -z $file > $tempfile
sed 's/^\(.*\)\/\/ xz.*/\1/' -z $template > $temptemplate
sed 's/^.*}\(.*\)/\1/' -z $template > $tempend

cat $temptemplate > $file
cat $tempfile >> $file
cat $tempend >> $file
