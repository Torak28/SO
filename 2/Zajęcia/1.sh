#! /bin/bash

#Przenieść wszystkie pliki regularne z A do B. W A utworzyć linki symboliczne do nowych lokalizacji przeniesionych plików.

if [ $# -eq 2 ]
then
	if [ -d $1 -a -d $2 ]
	then
		for file in `ls -a $1`; do
			if [ -f $1/$file -a ! -L $1/$file ]
			then
				mv $1/$file $2
				ln -s $(readlink -f $2/$file) $1/$file	
			fi
		done
	fi
fi
