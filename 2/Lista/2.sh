#! /bin/bash/

#Napisanie skryptu z jednym parametrem, którym był plik (np. z katalogu 1 z poprzedniego zadania). Skrypt ten miał za zadanie znalezienie wszystkich dowiązań dotego pliku w obrębie katalogu lab2.

if [ -f $1 ]
then
	for file in `ls`;do
	if [ -f $(readlink -f $file) -a -L $file -a $file != $1 ]
	then
		if [ $(readlink -f $file) = $(readlink -f $1) ]
		then
			echo Bingo: $file
		fi
		
	fi
done
fi
