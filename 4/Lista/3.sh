#! /bin/bash/

echo "1 2 3 4 5" | while read a b c
	do
		echo "Iteracja" a=$a b=$b c=$c "Koniec iteracji"
	done
