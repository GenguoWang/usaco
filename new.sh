#!/bin/bash
if [ $# -ne 1 ]
then
	echo "usage: $0 problem"
	exit 1
fi
sed -e "s/NAME/$1/" < template.cpp > "$1.cpp"
touch "$1.in" "$1.out"
