#!/bin/bash
if [ $# -ne 1 ]
then
	echo "usage: $0 problem"
	exit 1
fi
g++ $1.cpp && ./a.out && cat $1.out
