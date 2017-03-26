#! /bin/bash/

if [ $# -eq 1 ]
then
	find $1 -uid 1000 ! -name 1.sh ! -name . -printf "Pliczki o uid 1000:" -print
fi
