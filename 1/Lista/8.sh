#! /bin/bash/

#Listowanie   plików   z   zadanego   katalogu   (parametr   wywołania   skryptu),   wraz   z   jego #podkatalogami.  Zawartość  podkatalogów  ma  być  listowana  w  postaci  <ścieżkadostępu względem
#listowanego katalogu>/<nazwa pliku>.  Ograniczyć  liczbę  zagnieżdżeń  podkatalogów (np. do dwóch). 

echo Wypisywanie plików z $1 z podkatalogami

for file in `ls $1`; do
	if [ -f $1/$file ]	
	then
		echo PLIK  $file
	elif [ -d $1/$file ]
	then
		echo PODKATALOG $1/$file
		#Wypisanie zawarotsci
		for files in `ls $1/$file`;do
			if [ -f $1/$file/$files ]
			then
				echo PLIK  $1/$file/$files
			elif [ -d $1/$file/$files ]
			then
				for filess in `ls $1/$file/$files`; do
					if [ -f $1/$file/$files/$filess ]
					then
						echo PLIK $1/$file/$files/$filess
					else
						echo PODKATALOG $1/$file/$files/$filess
					fi
				done
			fi
		done
	fi
done

#Komendy:
#-d czy jest katalogiem
