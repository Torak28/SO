#! /bin/bash/

#Porównanie  zawartości  zadanego  katalogu  z  listą  plików  (nazwa  katalogu  i  pliku  z  listą
#zadawana   w   argumentach   skryptu).   Należy   wygenerować   listę   plików   brakujących w   
#katalogu i takich, które nie są na liście. 

echo Porównuje zawartośc katalogu $1 z plikiem $2. Wszystki różnice i braki wrzucam do wynik.txt

WYNIK=$1/wynik.txt
touch $WYNIK

for fileA in `ls $1`;do
	ZNALEZIONO=0
	for fileB in `cat $2`;do
		if [ -f "$1/"$fileA ]
		then
			if [ $fileA = $fileB ]
			then
				ZNALEZIONO=1
			fi
		fi
	done
	if [ $ZNALEZIONO -eq 0 -a $fileA != wynik.txt ]
	then
		echo Na liście nie ma $fileA, który jest w $1
		echo RÓŻNICA: $fileA >> $WYNIK
	fi
done

echo "" >> $WYNIK

for fileA in `cat $2`;do
	ZNALEZIONO=0
	for fileB in `ls $1`;do
		if [ -f "$1/"$fileB ]
		then
			if [ $fileA = $fileB ]
			then
				ZNALEZIONO=1
			fi
		fi
	done
	if [ $ZNALEZIONO -eq 0 ]
	then
		echo W katalogu brakuje $fileA, który jest na liście $2
		echo BRAKUJE $fileA >> $WYNIK
	fi
done

#Komendy:
# -eq - równy
